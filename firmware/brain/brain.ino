// RadioMicroscope v2 - brain
// Board: Seeed XIAO ESP32-S3 Sense (PSRAM: OPI).
//
// Points the head, commands the sensor radio, runs the scan and tracking
// modes and serves the control page over its own Wi-Fi network. Pins and
// options are in config.h; the algorithms are in lib/RMCore.
//
// The drivetrain is chosen in config.h: brushless motors behind the motor
// controller (drive_foc.h) or serial bus servos (drive_servo.h).
//
// USB serial console: free / hold release and energise the motors; any
// other line prints the commands of the selected drivetrain.

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <RMCore.h>

#include "config.h"
#include "web_ui.h"

#if RM_CAMERA
#include <esp_camera.h>
#endif

using namespace rm;

// ---------------------------------------------------------------------
// State
// ---------------------------------------------------------------------
enum Mode : uint8_t { kIdle, kSurvey, kScan, kTrack, kTurn };
static const char* const kModeNames[] = {"idle", "survey", "scan", "track", "turn"};

// Commands arrive in the web server task and are executed in loop().
struct Command {
    enum Type : uint8_t { kGoto, kJog, kSurveyCmd, kTarget, kScanCmd, kTrackCmd, kStop, kSet, kTorque, kTurnCmd, kCalMag } type;
    float a, b, c, d, e;
    bool flag;
    uint8_t mac[6];
    uint8_t channel;
};

struct StationRow {
    link::MsgStation s;
    uint32_t seen;
};

static Axis g_pan, g_tilt;
static AsyncWebServer g_server(80);
static AsyncWebSocket g_ws("/ws");
static QueueHandle_t g_commands;
static Preferences g_prefs;

static Mode g_mode = kIdle;
static AzEl g_goal;            // commanded direction, mechanical frame
static AzEl g_now;             // direction measured by the encoders
static bool g_driveOk = false;  // drivetrain answering and ready to move
static bool g_torque = false;  // the head does not move until the first command
static float g_volts = 0;
static int g_tempC = 0;

static link::Parser g_linkParser;
static bool g_sensorOk = false;
static bool g_sensor5G = false;
static uint32_t g_sensorSeen = 0;
static link::MsgSample g_sample{};
static uint32_t g_sampleCount = 0;

static bool g_haveTarget = false;
static uint8_t g_targetMac[6];
static uint8_t g_targetChannel = 1;
static uint8_t g_periodMs = 200;  // sensor report period while staring

static float g_north = 0;      // true azimuth of mechanical pan 0, set by the user
static float g_beam = 40;      // antenna half-power beamwidth, degrees

static SkyMap g_map;
static bool g_mapDirty = false;
static Scanner g_scanner;
static float g_scanWidth = 5;
static float g_scanStep = 10;
static bool g_stationsDirty = false;
static bool g_trackAfterScan = false;
// Why the scan under way was started: 0 = asked for by the user, 1 = looking
// near where a tracked source was lost, 2 = looking over the whole sky for it.
static uint8_t g_searchStage = 0;
static Tracker g_tracker;
static bool g_havePeak = false;
static AzEl g_peak;
static float g_peakDbm = 0;

static const int kMaxStations = 48;
static StationRow g_stations[kMaxStations];
static int g_stationCount = 0;

static Nmea g_gps;
static Attitude g_att;          // heading, pitch and roll of the sensor board (zero without NAV_SENSORS)
static float g_northManual = 0; // north offset typed in by the user; used when there is no compass
static uint32_t g_gpsSeen = 0;  // when the GPS last reported
static int g_turnLast = -1;     // azimuth cell of the previous turn-scan reading

// A GPS that has stopped talking keeps its last position; only a recent
// report counts as a fix.
static bool gpsFresh() { return g_gps.fix && millis() - g_gpsSeen < 3000; }
static bool g_mapWorld = false; // true when the map is in world directions (turn scan), not head angles

// Turn scan: the azimuth cells filled since the last bearing was taken.
static bool g_turnSeen[SkyMap::kAz];
static int g_turnCount = 0;
static uint32_t g_bearings = 0;  // bearings produced since power-up

// One measurement: move to a direction, let the head settle, take a reading.
enum ProbeState : uint8_t { kProbeIdle, kProbeMoving, kProbeSettling, kProbeDone };
static ProbeState g_probe = kProbeIdle;
static AzEl g_probeAt;
static uint32_t g_probeT = 0;
static uint32_t g_probeSeen = 0;    // g_sampleCount when a report was last consumed
static int g_probeReports = 0;      // reports consumed since arrival
static uint32_t g_probeFrames = 0;  // frames in the reports that counted
static float g_probeSum = 0;        // sum of median * frames
static bool g_probeValid = false;
static float g_probeDbm = 0;

// ---------------------------------------------------------------------
// Motion
// ---------------------------------------------------------------------
#if DRIVE_FIXED
#include "drive_fixed.h"
#elif DRIVE_BRUSHLESS
#include "drive_foc.h"
#else
#include "drive_servo.h"
#endif

// Directions here are in the mechanical frame and are clamped to the
// travel limits, never wrapped: asking for 180 at a +175 stop must go to
// +175, not round to -175.
static void pointAt(AzEl p) {
    g_goal.az = g_pan.clampDeg(p.az);
    g_goal.el = g_tilt.clampDeg(p.el);
    driveGoal(g_goal);
    g_torque = true;
}

static void setTorque(bool on) {
    if (on) {
        // Hold where the head is now, not at some earlier goal.
        if (g_driveOk) pointAt(g_now);
        return;
    }
    driveFree();
    g_torque = false;
}

static bool arrived() {
    return fabsf(g_now.az - g_goal.az) < 1.5f && fabsf(g_now.el - g_goal.el) < 1.5f;
}

static void pollDrive() {
    drivePoll();
    // While the motors are free the head can be turned by hand, so the
    // goal follows it; the next jog then starts from where the head is.
    if (g_driveOk && !g_torque) g_goal = g_now;
}

// ---------------------------------------------------------------------
// Sensor link
// ---------------------------------------------------------------------
static void noteStation(const link::MsgStation& s) {
    StationRow* row = nullptr;
    for (int i = 0; i < g_stationCount; i++) {
        if (memcmp(g_stations[i].s.mac, s.mac, 6) == 0) { row = &g_stations[i]; break; }
    }
    if (!row) {
        if (g_stationCount < kMaxStations) {
            row = &g_stations[g_stationCount++];
        } else {
            row = &g_stations[0];  // table full: replace the one not heard for longest
            for (int i = 1; i < kMaxStations; i++)
                if (g_stations[i].seen < row->seen) row = &g_stations[i];
        }
    }
    row->s = s;
    row->s.ssid[sizeof(row->s.ssid) - 1] = 0;
    // Network names are arbitrary bytes chosen by strangers. Anything that
    // is not plain printable ASCII would make the JSON sent to the page
    // invalid UTF-8, and browsers close the connection on that.
    for (char* p = row->s.ssid; *p; p++)
        if (*p < 0x20 || *p > 0x7E) *p = '?';
    row->seen = millis();
    g_stationsDirty = true;
}

#if SENSOR_RX5808
#include "sensor_rx5808.h"
#elif SENSOR_ESPSDR
#include "sensor_espsdr.h"
#else
static void sensorBegin() {
    if (g_prefs.getUChar("tgtBand", 0) != 0) g_haveTarget = false;  // saved by a build with another receiver
    Serial2.setRxBufferSize(4096);  // a survey report arrives as one 2.3 kB burst
    Serial2.begin(link::kBaud, SERIAL_8N1, LINK_RX_PIN, LINK_TX_PIN);
}

static void sendToSensor(uint8_t type, const void* payload, size_t n) {
    uint8_t buf[link::kMaxFrame];
    size_t len = link::encode(buf, type, payload, n);
    if (len) Serial2.write(buf, len);
}

static void sensorMode(uint8_t mode) {
    link::CmdMode c{};
    c.mode = mode;
    c.channel = g_targetChannel;
    memcpy(c.mac, g_targetMac, 6);
    c.periodMs = g_periodMs;
    sendToSensor(link::kCmdMode, &c, sizeof(c));
}

static void pollSensor() {
    link::Frame f;
    while (Serial2.available()) {
        if (!g_linkParser.feed((uint8_t)Serial2.read(), f)) continue;
        const bool wasOk = g_sensorOk;
        g_sensorSeen = millis();
        g_sensorOk = true;
        if (f.type == link::kMsgSample) {
            if (f.as(g_sample)) g_sampleCount++;
        } else if (f.type == link::kMsgStation) {
            link::MsgStation s;
            if (f.as(s)) noteStation(s);
        } else if (f.type == link::kMsgHello) {
            link::MsgHello h;
            if (!f.as(h)) continue;
            g_sensor5G = h.caps & link::kCap5GHz;
            // Hellos also arrive every second as a heartbeat. Only when the
            // sensor has just started, or the link has just come back, is it
            // put into the mode we expect.
            if (h.boot || !wasOk) {
                if (g_mode == kSurvey) sensorMode(link::kModeSurvey);
                else if (g_haveTarget) sensorMode(link::kModeStare);
            }
        }
    }
    if (g_sensorOk && millis() - g_sensorSeen > 3000) g_sensorOk = false;
}
#endif

// ---------------------------------------------------------------------
// Probe, scan and track
// ---------------------------------------------------------------------
static void probeStart(AzEl p) {
    g_probeAt = p;
    pointAt(p);
    g_probe = kProbeMoving;
    g_probeT = millis();
}

static void probeUpdate() {
    const uint32_t now = millis();
    if (g_probe == kProbeMoving) {
        // Moving on after 4 s without arriving keeps a stalled axis from
        // hanging the scan; the reading is then taken where the head is.
        if (arrived() || now - g_probeT > 4000) {
            g_probe = kProbeSettling;
            g_probeT = now;
            g_probeSeen = g_sampleCount;
            g_probeReports = 0;
            g_probeFrames = 0;
            g_probeSum = 0;
        }
    } else if (g_probe == kProbeSettling) {
        if (g_sampleCount != g_probeSeen) {
            g_probeSeen = g_sampleCount;
            // The first report after arrival still contains frames received
            // on the way, so it is skipped. After that, reports are added up
            // until at least three frames have been heard: an access point
            // that only beacons sends about ten a second, so one report
            // often holds one frame or none.
            if (++g_probeReports >= 2 && g_sample.frames > 0) {
                g_probeFrames += g_sample.frames;
                g_probeSum += (float)g_sample.median * g_sample.frames;
            }
        }
        const bool enough = g_probeFrames >= 3;
        const bool waitedOut = g_probeReports >= 5 || now - g_probeT > 5u * g_periodMs + 500;
        if (enough || waitedOut) {
            g_probeValid = g_probeFrames > 0;
            if (g_probeValid) g_probeDbm = g_probeSum / g_probeFrames;
            g_probe = kProbeDone;
        }
    }
}

// ---- navigation sensors and logging (optional) ---------------------------
#if NAV_SENSORS
#include "nav.h"
#else
static void navBegin() {}
static void navPoll() {}
static void navStartCalibration() {}
static bool navOk() { return false; }
static const bool g_magCalibrating = false;
// Without a compass, world azimuth is the head angle plus the north offset
// entered by hand.
static AzEl navWorldDir() { return {wrap360(g_now.az + g_north), g_now.el}; }
static float navNorthOffset() { return g_northManual; }
#endif

#if LOG_SD
#include "log_sd.h"
#else
static void logBegin() {}
static void logPoll() {}
static void logRow(char, AzEl, float, int) {}
static const bool g_logOk = false;
static const uint32_t g_logRows = 0;
#endif

static void setMode(Mode m) {
    g_mode = m;
    g_probe = kProbeIdle;
}

static void startScan(const ScanPlan& plan, bool trackAfter) {
    if (!g_haveTarget) return;
    g_map.clear();
    g_mapWorld = false;
    g_mapDirty = true;
    g_havePeak = false;
    g_scanner.begin(plan);
    g_scanStep = plan.step;
    g_trackAfterScan = trackAfter;
    sensorMode(link::kModeStare);
    setMode(kScan);
}

static void startTrack(AzEl at) {
    if (!g_haveTarget) return;
    g_tracker.cfg.beamwidth = g_beam;
    g_tracker.cfg.elMin = TILT_MIN;
    g_tracker.cfg.elMax = TILT_MAX;
    g_tracker.cfg.azMin = PAN_MIN;
    g_tracker.cfg.azMax = PAN_MAX;
    g_tracker.start(at);
    sensorMode(link::kModeStare);
    setMode(kTrack);
}

static ScanPlan defaultPlan() {
    ScanPlan p;
    p.azMin = PAN_MIN;
    p.azMax = PAN_MAX;
    p.elMin = 0;
    p.elMax = 90;
    // A third of the beamwidth, so a narrow long-range beam cannot fall
    // between two points; never coarser than 10 degrees.
    p.step = clampf(g_beam / 3, 3, 10);
    return p;
}

// Turn scan: the head stays put and the vehicle (or the whole instrument)
// is turned through a circle. Readings are filed by the world direction
// the antenna had at that moment; once most of the circle is covered the
// strongest direction becomes one bearing.
static void startTurn() {
    if (!g_haveTarget || !navOk()) return;
    g_map.clear();
    g_mapWorld = true;
    g_mapDirty = true;
    g_havePeak = false;
    memset(g_turnSeen, 0, sizeof(g_turnSeen));
    g_turnCount = 0;
    g_turnLast = -1;
    sensorMode(link::kModeStare);
    setMode(kTurn);
}

// Called once for every new reading from the sensor.
static void onSample() {
    const bool heard = g_sample.frames > 0;
    const AzEl world = navWorldDir();
    if (heard) logRow('S', world, g_sample.median, g_sample.frames);
    if (g_mode != kTurn || !navOk()) return;

    const AzEl cell{wrap180(world.az), world.el};
    if (heard) {
        g_map.put(cell, g_sample.median);
        g_mapDirty = true;
    }
    // A direction counts as visited whether or not anything was heard
    // there. A quick turn steps over cells between two readings; those in
    // between count as visited too, as long as the step is under a quarter
    // turn (a bigger jump is not a turn in progress).
    const int i = SkyMap::azIndex(cell.az);
    int from = i, steps = 0;
    if (g_turnLast >= 0) {
        int d = ((i - g_turnLast) % SkyMap::kAz + SkyMap::kAz) % SkyMap::kAz;  // 0 .. 71, clockwise
        if (d > SkyMap::kAz / 2) d -= SkyMap::kAz;                              // shortest way round
        if (abs(d) <= SkyMap::kAz / 4) { from = g_turnLast; steps = d; }
    }
    for (int k = 0; k <= abs(steps); k++) {
        const int c = ((from + (steps < 0 ? -k : k)) % SkyMap::kAz + SkyMap::kAz) % SkyMap::kAz;
        if (!g_turnSeen[c]) {
            g_turnSeen[c] = true;
            g_turnCount++;
        }
    }
    g_turnLast = i;
    if (g_turnCount >= SkyMap::kAz * 5 / 6) {
        g_havePeak = g_map.peak(g_peak, g_peakDbm);
        if (g_havePeak) {
            logRow('B', {wrap360(g_peak.az), g_peak.el}, g_peakDbm, 0);
            g_bearings++;
        }
        memset(g_turnSeen, 0, sizeof(g_turnSeen));
        g_turnCount = 0;
        g_turnLast = -1;
        g_map.clear();  // the next turn starts a fresh map; the peak stays on screen
        g_mapDirty = true;
    }
}

static void runMode() {
    probeUpdate();
    if (g_mode == kScan) {
        if (g_probe == kProbeDone) {
            if (g_probeValid) {
                g_map.put(g_probeAt, g_probeDbm, g_scanWidth, g_scanStep);
                g_mapDirty = true;
            }
            g_probe = kProbeIdle;
        }
        if (g_probe == kProbeIdle) {
            AzEl p;
            if (g_scanner.next(p)) {
                g_scanWidth = g_scanner.lastAzWidth();
                probeStart(p);
            } else {
                g_havePeak = g_map.peak(g_peak, g_peakDbm);
                // A peak too weak for the tracker to hold is not worth locking
                // onto: it would be declared lost at once and searched for again.
                const bool usable = g_havePeak && (!g_trackAfterScan || g_peakDbm >= g_tracker.cfg.lostDbm);
                if (usable) {
                    pointAt(g_peak);
                    if (g_trackAfterScan) startTrack(g_peak);
                    else setMode(kIdle);
                } else if (g_searchStage == 1) {
                    // Not near where it was lost: now look over the whole sky.
                    startScan(defaultPlan(), true);
                    g_searchStage = 2;
                } else {
                    setMode(kIdle);  // nothing heard anywhere: stop rather than scan forever
                }
            }
        }
    } else if (g_mode == kTrack) {
        if (g_probe == kProbeDone) {
            g_tracker.report(g_probeValid, g_probeDbm);
            g_probe = kProbeIdle;
            g_peak = g_tracker.centre();
            g_peakDbm = g_tracker.peakDbm();
            g_havePeak = true;
            if (g_tracker.lost()) {
                // Lost: look first around where it was last seen, which takes a
                // fraction of the time of a whole-sky scan.
                startScan(localPlan(g_tracker.centre(), g_beam, PAN_MIN, PAN_MAX, TILT_MIN, TILT_MAX), true);
                g_searchStage = 1;
                return;
            }
        }
        if (g_probe == kProbeIdle) probeStart(g_tracker.nextPoint());
    }
}

// ---------------------------------------------------------------------
// Commands
// ---------------------------------------------------------------------
static void saveSettings() {
    g_prefs.putFloat("north", g_northManual);
    g_prefs.putFloat("beam", g_beam);
    g_prefs.putUChar("period", g_periodMs);
    g_prefs.putBool("haveTgt", g_haveTarget);
    g_prefs.putBytes("tgtMac", g_targetMac, 6);
    g_prefs.putUChar("tgtCh", g_targetChannel);
}

static void execute(const Command& c) {
#if DRIVE_FIXED
    // No motors: anything that would move the head is refused.
    if (c.type == Command::kGoto || c.type == Command::kJog || c.type == Command::kScanCmd ||
        c.type == Command::kTrackCmd || c.type == Command::kTorque) return;
#endif
    switch (c.type) {
        case Command::kGoto:
            if (g_mode == kScan || g_mode == kTrack) setMode(kIdle);
            pointAt({c.a, c.b});
            break;
        case Command::kJog: {
            if (g_mode == kScan || g_mode == kTrack) setMode(kIdle);
            // Start from the measured position unless the head is already
            // holding a goal (then successive taps add up exactly).
            const AzEl base = g_torque ? g_goal : g_now;
            pointAt({base.az + c.a, base.el + c.b});
            break;
        }
        case Command::kSurveyCmd:
            g_stationCount = 0;
            sensorMode(link::kModeSurvey);
            setMode(kSurvey);
            break;
        case Command::kTarget:
            memcpy(g_targetMac, c.mac, 6);
            g_targetChannel = c.channel;
            g_haveTarget = true;
            saveSettings();
#if !SENSOR_RX5808 && !SENSOR_ESPSDR
            g_prefs.putUChar("tgtBand", 0);  // a Wi-Fi target; the other receivers will not reuse it
#endif
            sensorMode(link::kModeStare);
            setMode(kIdle);
            g_stationsDirty = true;  // the page marks the chosen row
            break;
        case Command::kScanCmd: {
            ScanPlan p;
            p.azMin = clampf(c.a, PAN_MIN, PAN_MAX);
            p.azMax = clampf(c.b, p.azMin, PAN_MAX);
            p.elMin = clampf(c.c, TILT_MIN, TILT_MAX);
            p.elMax = clampf(c.d, p.elMin, TILT_MAX);
            p.step = clampf(c.e, 2, 30);
            startScan(p, c.flag);
            g_searchStage = 0;
            break;
        }
        case Command::kTurnCmd:
            startTurn();
            break;
        case Command::kCalMag:
            if (g_mode == kTurn) setMode(kIdle);
            navStartCalibration();
            break;
        case Command::kTrackCmd:
            // A peak from a turn scan is a world direction; the head wants its own angles.
            if (g_havePeak && g_mapWorld) {
                const AzEl head{wrap180(g_peak.az - g_north), g_peak.el};
                // From here on the peak is the tracker's, in head angles: drop
                // the world-direction map so the two are not drawn together.
                g_map.clear();
                g_mapWorld = false;
                g_mapDirty = true;
                g_peak = head;
                startTrack(head);
            } else {
                startTrack(g_havePeak ? g_peak : g_goal);
            }
            break;
        case Command::kStop:
            if (g_mode == kSurvey) sensorMode(g_haveTarget ? link::kModeStare : link::kModeIdle);
            setMode(kIdle);
            pointAt(g_now);  // hold where the head is now
            break;
        case Command::kSet:
            // With a working compass the north offset is measured; a typed
            // value is kept only for when there is none.
            if (!navOk()) g_northManual = wrap180(c.a);
            g_beam = clampf(c.b, 5, 120);
            g_periodMs = (uint8_t)clampf(c.c, 20, 250);
            saveSettings();
            if (g_haveTarget && g_mode != kSurvey) sensorMode(link::kModeStare);
            break;
        case Command::kTorque:
            if (g_mode == kScan || g_mode == kTrack) setMode(kIdle);
            setTorque(c.flag);
            break;
    }
}

static bool parseMac(const char* s, uint8_t* mac) {
    unsigned v[6];
    if (!s || sscanf(s, "%x:%x:%x:%x:%x:%x", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]) != 6) return false;
    for (int i = 0; i < 6; i++) mac[i] = (uint8_t)v[i];
    return true;
}

// Runs in the web server task: decode and queue, nothing else.
static void onWsEvent(AsyncWebSocket*, AsyncWebSocketClient*, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        g_mapDirty = true;  // a new viewer needs the map and the station list
        g_stationsDirty = true;
        return;
    }
    if (type != WS_EVT_DATA) return;
    AwsFrameInfo* info = (AwsFrameInfo*)arg;
    if (info->opcode != WS_TEXT || !info->final || info->index != 0 || info->len != len) return;

    JsonDocument doc;
    if (deserializeJson(doc, data, len)) return;
    const char* cmd = doc["cmd"] | "";
    Command c{};
    if (!strcmp(cmd, "goto")) {
        c.type = Command::kGoto;
        c.a = doc["az"] | 0.0f;
        c.b = doc["el"] | 0.0f;
    } else if (!strcmp(cmd, "jog")) {
        c.type = Command::kJog;
        c.a = doc["daz"] | 0.0f;
        c.b = doc["del"] | 0.0f;
    } else if (!strcmp(cmd, "survey")) {
        c.type = Command::kSurveyCmd;
    } else if (!strcmp(cmd, "target")) {
        c.type = Command::kTarget;
        if (!parseMac(doc["mac"] | "", c.mac)) return;
        c.channel = doc["ch"] | 1;
    } else if (!strcmp(cmd, "scan")) {
        c.type = Command::kScanCmd;
        c.a = doc["azMin"] | PAN_MIN;
        c.b = doc["azMax"] | PAN_MAX;
        c.c = doc["elMin"] | 0.0f;
        c.d = doc["elMax"] | 90.0f;
        c.e = doc["step"] | 10.0f;
        c.flag = doc["track"] | false;
    } else if (!strcmp(cmd, "turn")) {
        c.type = Command::kTurnCmd;
    } else if (!strcmp(cmd, "calmag")) {
        c.type = Command::kCalMag;
    } else if (!strcmp(cmd, "track")) {
        c.type = Command::kTrackCmd;
    } else if (!strcmp(cmd, "stop")) {
        c.type = Command::kStop;
    } else if (!strcmp(cmd, "set")) {
        c.type = Command::kSet;
        c.a = doc["north"] | g_north;
        c.b = doc["beam"] | g_beam;
        c.c = doc["period"] | (float)g_periodMs;
    } else if (!strcmp(cmd, "torque")) {
        c.type = Command::kTorque;
        c.flag = doc["on"] | false;
    } else {
        return;
    }
    xQueueSend(g_commands, &c, 0);
}

// ---------------------------------------------------------------------
// Reports to the page
// ---------------------------------------------------------------------
static void macToText(const uint8_t* m, char* out) {
    sprintf(out, "%02x:%02x:%02x:%02x:%02x:%02x", m[0], m[1], m[2], m[3], m[4], m[5]);
}

static void pushStatus() {
    JsonDocument doc;
    doc["t"] = "s";
    doc["mode"] = kModeNames[g_mode];
    doc["az"] = roundf(g_now.az * 10) / 10;
    doc["el"] = roundf(g_now.el * 10) / 10;
    doc["north"] = g_north;
    doc["beam"] = g_beam;
    doc["period"] = g_periodMs;
    doc["servo"] = g_driveOk;
    doc["torque"] = g_torque;
    doc["sensor"] = g_sensorOk;
    doc["g5"] = g_sensor5G;
#if SENSOR_RX5808
    doc["rx"] = "5.8 GHz video receiver";
#elif SENSOR_ESPSDR
    doc["rx"] = ESPSDR_BAND == 24 ? "ESP-SDR, 2.4 GHz" : "ESP-SDR, 5.8 GHz";
#endif
    // The map and the peak are drawn with this offset: the north offset for
    // a scan (head angles), zero for a turn scan (already world directions).
    doc["mapNorth"] = g_mapWorld ? 0 : g_north;
    if (NAV_SENSORS) {
        doc["nav"] = navOk();
        doc["cal"] = g_magCalibrating;
        doc["hdg"] = roundf(g_att.heading);
        doc["pitch"] = roundf(g_att.pitch);
        doc["roll"] = roundf(g_att.roll);
    }
    if (g_logOk) doc["rows"] = g_logRows;
    if (g_mode == kTurn) {
        doc["turn"] = g_turnCount * 100 / SkyMap::kAz;
        doc["bearings"] = g_bearings;
    }
    doc["volt"] = g_volts;
    doc["temp"] = g_tempC;
    if (g_haveTarget) {
        char mac[18];
        macToText(g_targetMac, mac);
        doc["tgt"] = mac;
        doc["ch"] = g_targetChannel;
        if (g_sensorOk && g_mode != kSurvey) {
            doc["frames"] = g_sample.frames;
            if (g_sample.frames) doc["rssi"] = g_sample.median;
            doc["noise"] = g_sample.noise;
        }
    }
    if (g_havePeak) {
        doc["pAz"] = roundf(g_peak.az * 10) / 10;
        doc["pEl"] = roundf(g_peak.el * 10) / 10;
        doc["pDbm"] = g_peakDbm;
    }
    if (g_mode == kScan) {
        doc["search"] = g_searchStage;
        doc["done"] = g_scanner.done();
        doc["total"] = g_scanner.total();
    }
    if (gpsFresh()) {
        doc["lat"] = g_gps.lat;
        doc["lon"] = g_gps.lon;
        doc["sats"] = g_gps.sats;
    }
    String out;
    serializeJson(doc, out);
    g_ws.textAll(out);
}

static void pushStations() {
    JsonDocument doc;
    doc["t"] = "st";
    JsonArray list = doc["list"].to<JsonArray>();
    for (int i = 0; i < g_stationCount; i++) {
        const link::MsgStation& s = g_stations[i].s;
        char mac[18];
        macToText(s.mac, mac);
        JsonObject o = list.add<JsonObject>();
        o["mac"] = mac;
        o["ssid"] = s.ssid;
        o["ch"] = s.channel;
        o["rssi"] = s.rssi;
        o["ap"] = s.isAp != 0;
    }
    String out;
    serializeJson(doc, out);
    g_ws.textAll(out);
}

// Binary message: 'M', columns, rows, then one signed byte per cell (dBm,
// -128 = no reading), row by row from the lowest elevation.
static void pushMap() {
    static uint8_t buf[3 + SkyMap::kAz * SkyMap::kEl];
    buf[0] = 'M';
    buf[1] = SkyMap::kAz;
    buf[2] = SkyMap::kEl;
    memcpy(buf + 3, g_map.cell, SkyMap::kAz * SkyMap::kEl);
    g_ws.binaryAll(buf, sizeof(buf));
}

// ---------------------------------------------------------------------
// Camera
// ---------------------------------------------------------------------
#if RM_CAMERA
static bool g_cameraOk = false;

static void cameraBegin() {
    // OV2640 / OV3660 connector of the XIAO ESP32-S3 Sense.
    camera_config_t c = {};
    c.ledc_channel = LEDC_CHANNEL_0;
    c.ledc_timer = LEDC_TIMER_0;
    c.pin_d0 = 15;
    c.pin_d1 = 17;
    c.pin_d2 = 18;
    c.pin_d3 = 16;
    c.pin_d4 = 14;
    c.pin_d5 = 12;
    c.pin_d6 = 11;
    c.pin_d7 = 48;
    c.pin_xclk = 10;
    c.pin_pclk = 13;
    c.pin_vsync = 38;
    c.pin_href = 47;
    c.pin_sccb_sda = 40;
    c.pin_sccb_scl = 39;
    c.pin_pwdn = -1;
    c.pin_reset = -1;
    c.xclk_freq_hz = 20000000;
    c.pixel_format = PIXFORMAT_JPEG;
    c.frame_size = FRAMESIZE_VGA;
    c.jpeg_quality = 14;
    // "Latest" needs two buffers; with one, a snapshot taken after a pause
    // would show the scene as it was when the previous one was served.
    c.fb_count = psramFound() ? 2 : 1;
    c.fb_location = psramFound() ? CAMERA_FB_IN_PSRAM : CAMERA_FB_IN_DRAM;
    c.grab_mode = psramFound() ? CAMERA_GRAB_LATEST : CAMERA_GRAB_WHEN_EMPTY;
    if (!psramFound()) c.frame_size = FRAMESIZE_QVGA;
    g_cameraOk = esp_camera_init(&c) == ESP_OK;
    Serial.println(g_cameraOk ? "camera ready" : "camera not found");
}

static void handleSnapshot(AsyncWebServerRequest* request) {
    camera_fb_t* fb = g_cameraOk ? esp_camera_fb_get() : nullptr;
    if (!fb) {
        request->send(503, "text/plain", "no camera");
        return;
    }
    // Sent straight from the camera's buffer, which is handed back when the
    // connection closes. (Copying it into a stream response would cost
    // seconds of CPU per picture in the web server task.)
    AsyncWebServerResponse* response = request->beginResponse(200, "image/jpeg", fb->buf, fb->len);
    response->addHeader("Cache-Control", "no-store");
    response->addHeader("Connection", "close");
    request->onDisconnect([fb]() { esp_camera_fb_return(fb); });
    request->send(response);
}
#endif

// ---------------------------------------------------------------------
// USB console
// ---------------------------------------------------------------------
static void consoleLine(char* line) {
    if (!strcmp(line, "free")) {
        setMode(kIdle);
        setTorque(false);
        Serial.println("motors free");
    } else if (!strcmp(line, "hold")) {
        setTorque(true);
        Serial.println(g_torque ? "motors holding" : "drivetrain not ready");
    } else if (!driveConsole(line) && *line) {
        Serial.println(kDriveHelp);
    }
}

static void pollConsole() {
    static char line[32];
    static size_t n = 0;
    while (Serial.available()) {
        char c = (char)Serial.read();
        if (c == '\n' || c == '\r') {
            line[n] = 0;
            n = 0;
            consoleLine(line);
        } else if (n < sizeof(line) - 1) {
            line[n++] = c;
        }
    }
}

// ---------------------------------------------------------------------
// Setup and loop
// ---------------------------------------------------------------------
void setup() {
    Serial.begin(115200);

    g_pan.minDeg = PAN_MIN;
    g_pan.maxDeg = PAN_MAX;
    g_pan.dir = PAN_DIR;
    g_tilt.minDeg = TILT_MIN;
    g_tilt.maxDeg = TILT_MAX;
    g_tilt.dir = TILT_DIR;

    g_prefs.begin("rm", false);
    g_northManual = g_prefs.getFloat("north", 0);
    g_north = g_northManual;
    g_beam = g_prefs.getFloat("beam", 40);
    g_periodMs = g_prefs.getUChar("period", 200);
    g_haveTarget = g_prefs.getBool("haveTgt", false);
    g_prefs.getBytes("tgtMac", g_targetMac, 6);
    g_targetChannel = g_prefs.getUChar("tgtCh", 1);

    g_commands = xQueueCreate(8, sizeof(Command));

    driveBegin();
    sensorBegin();
    navBegin();
    logBegin();
#if ARDUINO_USB_CDC_ON_BOOT
    Serial0.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, -1);
#endif

    // Nothing moves at start: no goal is sent until the first command, and
    // until then the goal simply follows the measured position.
    sendToSensor(link::kCmdPing, nullptr, 0);

#if RM_CAMERA
    cameraBegin();
#endif

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD, AP_CHANNEL);
    g_ws.onEvent(onWsEvent);
    g_server.addHandler(&g_ws);
    g_server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        AsyncWebServerResponse* response = request->beginResponse(200, "text/html", WEB_UI_GZ, WEB_UI_GZ_LEN);
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });
#if RM_CAMERA
    g_server.on("/snap.jpg", HTTP_GET, handleSnapshot);
#endif
    g_server.begin();
    Serial.printf("RadioMicroscope brain ready, http://%s\n", WiFi.softAPIP().toString().c_str());
}

void loop() {
    static uint32_t tStatus = 0, tSlow = 0, tMap = 0;
    const uint32_t now = millis();

    pollConsole();
    pollSensor();
#if ARDUINO_USB_CDC_ON_BOOT
    while (Serial0.available())
        if (g_gps.feed((char)Serial0.read())) g_gpsSeen = millis();
#endif

    Command c;
    while (xQueueReceive(g_commands, &c, 0) == pdTRUE) execute(c);

    pollDrive();
    navPoll();
    logPoll();
    static uint32_t seenSamples = 0;
    if (g_sampleCount != seenSamples) {
        seenSamples = g_sampleCount;
        onSample();
    }
    // With a working compass the north offset is measured, not typed in.
    const float northBefore = g_north;
    g_north = navOk() ? navNorthOffset() : g_northManual;
#if HOLD_WORLD && NAV_SENSORS && !NAV_TURNS_WITH_PAN && !DRIVE_FIXED
    // Carried in the hand, the base turns under the head. Whatever the head
    // was told to face, it should keep facing in the world: turn the goal,
    // the tracker's remembered direction and any probe in progress the
    // opposite way. A scan is left alone: it needs the base held still.
    static uint32_t tHold = 0;
    static float owed = 0;  // base rotation not yet passed on to the motors
    static bool hadNav = false;
    // Not during a scan (it needs the base held still) or a turn scan (there
    // the turning is the measurement).
    const bool holding = navOk() && g_torque && g_mode != kScan && g_mode != kTurn;
    if (holding && hadNav) {
        owed += wrap180(g_north - northBefore);
        if (fabsf(owed) >= 0.5f && now - tHold >= 50) {
            tHold = now;
            // At most 10 degrees per step: a glitch in the compass then costs
            // a twitch, not a swing, and a real turn is caught up in a few steps.
            const float step = clampf(owed, -10.0f, 10.0f);
            owed -= step;
            g_tracker.shiftAz(-step);
            g_probeAt.az -= step;
            if (g_havePeak && !g_mapWorld) g_peak.az = wrap180(g_peak.az - step);
            pointAt({g_goal.az - step, g_goal.el});
        }
    } else {
        owed = 0;
    }
    // The first pass after the compass becomes valid only records the new
    // north: the jump from the typed offset to the measured one is not a turn.
    hadNav = navOk();
#endif
    runMode();

    if (now - tStatus >= 200) {
        tStatus = now;
        g_ws.cleanupClients();
        if (g_ws.count()) pushStatus();
    }
    if (now - tSlow >= 2000) {
        tSlow = now;
        if (!g_sensorOk) sendToSensor(link::kCmdPing, nullptr, 0);
        if (g_ws.count() && g_stationsDirty) {
            g_stationsDirty = false;
            pushStations();
        }
    }
    if (g_mapDirty && now - tMap >= 1000 && g_ws.count()) {
        tMap = now;
        g_mapDirty = false;
        pushMap();
    }
    delay(1);
}
