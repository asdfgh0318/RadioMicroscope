// Sensor: a Seeed XIAO ESP32-C5 running the ESP-SDR firmware
// (github.com/ESPARGOS/esp-sdr, burst build), used as a tunable power
// meter. Selected with SENSOR_ESPSDR 1 in config.h. Included by brain.ino
// after its globals.
//
// The brain asks for short bursts of raw samples on one frequency and
// takes their mean power as the signal strength. That works on any signal
// in the band, an analog video carrier included, but gives no picture.
//
// Wiring is the same as for the Wi-Fi sensor firmware: C5 D6 (TX) to brain
// D2, C5 D7 (RX) to brain D3, 5 V and ground. The link runs at 2 Mbaud.
//
// Protocol as documented in papers/prior-art/esp-sdr-protocol.md: ASCII
// command lines, one reply line each; a capture reply is followed by the
// samples as signed bytes, I then minus Q.
//
// What is not known until tried on hardware: the exact reply text of GAIN,
// BANDWIDTH and FREQ (any line not starting with ERR is accepted), which
// gain index suits a nearby transmitter, and whether the C5 locks above
// 5800 MHz (its published reception table ends there).
#pragma once
#include "fpv_channels.h"

// The frequencies this receiver steps through, chosen by ESPSDR_BAND.
#if ESPSDR_BAND == 24
// 2.4 GHz: the 13 Wi-Fi channel centres.
static const int kSdrCount = 13;
static uint16_t sdrFreq(int i) { return 2412 + 5 * i; }
static void sdrName(int i, char* out, size_t n) { snprintf(out, n, "2.4 GHz ch %d  %u MHz", i + 1, sdrFreq(i)); }
// Wi-Fi comes in short packets with silence between them, so of the
// bursts taken in one report period the strongest is kept.
static const bool kSdrPeakDetect = true;
static const uint8_t kSdrBandTag = 24;
static bool sdrReceivable(int) { return true; }
#else
// 5.8 GHz: the 48 analog video channels.
static const int kSdrCount = 48;
static uint16_t sdrFreq(int i) { return kRxFreq[i]; }
static void sdrName(int i, char* out, size_t n) { snprintf(out, n, "%c%d  %u MHz", kRxBand[i / 8], i % 8 + 1, kRxFreq[i]); }
// A video carrier is always on: the middle burst of the period is kept.
static const bool kSdrPeakDetect = false;
static const uint8_t kSdrBandTag = 58;
// The C5's published reception table ends at 5800 MHz. Channels above it
// are still tuned and listed, but are left out of the noise-floor estimate.
static bool sdrReceivable(int i) { return kRxFreq[i] <= 5800; }
#endif

static void sdrReport(int channel, float dbm) {
    link::MsgStation s{};
    s.mac[5] = channel + 1;
    s.channel = channel + 1;
    s.rssi = (int8_t)lroundf(dbm);
    s.isAp = 1;
    sdrName(channel, s.ssid, sizeof(s.ssid));
    noteStation(s);
}

static const uint32_t kSdrBaud = 2000000;
static const int kSdrSamples = 1024;      // per burst: 51 microseconds at 20 MS/s
static const int kSdrRateCode = 2;        // 20 MS/s, about the width of one video channel
static const uint32_t kSdrSettleMs = 20;   // after retuning, before a burst counts
static const uint32_t kSdrTimeoutMs = 600;

enum SdrState : uint8_t { kSdrSync, kSdrLimits, kSdrGain, kSdrFreq, kSdrCapture, kSdrData };

static SdrState g_sdrState = kSdrSync;
static uint32_t g_sdrSent = 0;       // when the last command went out
static uint32_t g_sdrGood = 0;       // when the last good burst arrived
static uint32_t g_sdrTuned = 0;
static char g_sdrLine[200];
static size_t g_sdrLineLen = 0;
static uint8_t g_sdrData[kSdrSamples * 2];
static size_t g_sdrGot = 0, g_sdrNeed = 0;
static uint32_t g_sdrCrc = 0;
static int g_sdrGain = 0;
static uint8_t g_sdrMode = link::kModeIdle;
static uint8_t g_sdrChannel = 0;     // index into kRxFreq
static bool g_sdrRetune = true;
static float g_sdrFloorDb = ESPSDR_FLOOR_DB;  // burst power with no signal, in the chip's own dB
static float g_sdrPass[48];          // channel powers of the survey pass under way
static int g_sdrPassCount = 0;
static uint8_t g_sdrErrors = 0;      // error replies in a row
static uint32_t g_sdrQuietUntil = 0; // after repeated errors, no commands before this time
static float g_sdrBurst[12];         // burst powers collected for the report under way
static int g_sdrBursts = 0;
static uint32_t g_sdrReported = 0;
static uint16_t g_sdrSeq = 0;

static void sdrSend(const char* line, SdrState next) {
    Serial2.print(line);
    Serial2.print('\n');
    g_sdrSent = millis();
    g_sdrState = next;
}

static void sdrResync() {
    // After several errors in a row (a setting the firmware refuses), wait
    // before trying again instead of flooding the link.
    if (g_sdrErrors >= 3) {
        g_sdrErrors = 0;
        g_sdrQuietUntil = millis() + 3000;
        g_sdrSent = g_sdrQuietUntil;  // the timeout in pollSensor() starts the next attempt
        g_sdrState = kSdrSync;
        g_sdrLineLen = 0;
        g_sdrRetune = true;
        return;
    }
    while (Serial2.available()) Serial2.read();
    g_sdrLineLen = 0;
    g_sdrRetune = true;
    sdrSend("SYNC 4242", kSdrSync);
}

// Between two commands: retune if asked, otherwise take the next burst.
static void sdrNext() {
    char cmd[32];
    if (g_sdrRetune) {
        g_sdrRetune = false;
        snprintf(cmd, sizeof(cmd), "FREQ %u", sdrFreq(g_sdrChannel));
        sdrSend(cmd, kSdrFreq);
    } else {
        snprintf(cmd, sizeof(cmd), "CAP16 %d %d", kSdrSamples, kSdrRateCode);
        sdrSend(cmd, kSdrCapture);
    }
}

// CRC-32 as used by zlib, over the sample bytes.
static uint32_t sdrCrc32(const uint8_t* p, size_t n) {
    uint32_t c = 0xFFFFFFFF;
    for (size_t i = 0; i < n; i++) {
        c ^= p[i];
        for (int b = 0; b < 8; b++) c = (c >> 1) ^ (0xEDB88320 & (0 - (c & 1)));
    }
    return ~c;
}

// Burst power on the instrument's dBm-like scale. The chip's gain is not
// calibrated, so this is a level relative to the no-signal floor, pinned
// at -95: good for finding and following a peak, not an absolute power.
static float sdrToDbm(float db) { return clampf(-95.0f + (db - g_sdrFloorDb), -95.0f, -20.0f); }

static void sdrBurstDone() {
    if (sdrCrc32(g_sdrData, g_sdrNeed) != g_sdrCrc) return;  // damaged in transit: drop it
    g_sdrGood = millis();
    if (g_sdrGood - g_sdrTuned < kSdrSettleMs) return;
    uint32_t sum = 0;
    for (size_t i = 0; i < g_sdrNeed; i++) {
        const int8_t v = (int8_t)g_sdrData[i];
        sum += (uint32_t)(v * v);
    }
    const float db = 10.0f * log10f((float)sum / kSdrSamples + 0.01f);

    if (g_sdrMode == link::kModeSurvey) {
        sdrReport(g_sdrChannel, sdrToDbm(db));
        if (sdrReceivable(g_sdrChannel) && g_sdrPassCount < 48) g_sdrPass[g_sdrPassCount++] = db;
        g_sdrChannel = (g_sdrChannel + 1) % kSdrCount;
        if (g_sdrChannel == 0 && g_sdrPassCount >= 4) {
            // A full pass. The floor is taken as the third-quietest channel:
            // quiet enough to be noise, but not the single lowest reading,
            // which can be a dip in the receiver's own response. It is stored
            // only when it has moved, to spare the flash memory.
            for (int i = 1; i < g_sdrPassCount; i++)
                for (int j = i; j > 0 && g_sdrPass[j] < g_sdrPass[j - 1]; j--) {
                    const float t = g_sdrPass[j];
                    g_sdrPass[j] = g_sdrPass[j - 1];
                    g_sdrPass[j - 1] = t;
                }
            const float floor = g_sdrPass[2];
            if (fabsf(floor - g_sdrFloorDb) > 0.5f) {
                g_sdrFloorDb = floor;
                g_prefs.putFloat("sdrFloor", g_sdrFloorDb);
            }
        }
        if (g_sdrChannel == 0) g_sdrPassCount = 0;
        g_sdrRetune = true;
    } else if (g_sdrMode == link::kModeStare) {
        if (g_sdrBursts < (int)(sizeof(g_sdrBurst) / sizeof(g_sdrBurst[0]))) g_sdrBurst[g_sdrBursts++] = db;
    }
}

static void sdrLine(char* line) {
    if (!strncmp(line, "ERR", 3) && g_sdrState != kSdrSync) {
        g_sdrErrors++;
        sdrResync();
        return;
    }
    if (g_sdrState != kSdrSync) g_sdrErrors = 0;
    switch (g_sdrState) {
        case kSdrSync:
            // Anything before the echoed nonce is left over from earlier.
            // Bytes left over from an interrupted transfer may share the line
            // with the echo, so match its end.
            {
                const size_t n = strlen(line);
                if (n >= 9 && !strcmp(line + n - 9, "SYNC 4242")) sdrSend("LIMITS?", kSdrLimits);
            }
            break;
        case kSdrLimits: {
            int lo = 0, hi = 0;
            const char* g = strstr(line, "\"gain\":[");
            if (g && sscanf(g, "\"gain\":[%d,%d", &lo, &hi) == 2) g_sdrGain = (lo + hi) / 2;
            if (ESPSDR_GAIN >= 0) g_sdrGain = ESPSDR_GAIN;
            char cmd[32];
            // Manual gain: with automatic gain the level would not follow the signal.
            snprintf(cmd, sizeof(cmd), "GAIN MANUAL %d", g_sdrGain);
            sdrSend(cmd, kSdrGain);
            break;
        }
        case kSdrGain:
            g_sdrRetune = true;
            sdrNext();
            break;
        case kSdrFreq:
            g_sdrTuned = millis();
            sdrNext();
            break;
        case kSdrCapture: {
            unsigned n = 0;
            unsigned long crc = 0;
            if (sscanf(line, "DATA %u %lx", &n, &crc) == 2 && n == (unsigned)kSdrSamples) {
                g_sdrNeed = n * 2;
                g_sdrGot = 0;
                g_sdrCrc = (uint32_t)crc;
                g_sdrState = kSdrData;
            } else {
                sdrResync();
            }
            break;
        }
        default:
            break;
    }
}

static void sensorBegin() {
    Serial2.setRxBufferSize(8192);
    Serial2.begin(kSdrBaud, SERIAL_8N1, LINK_RX_PIN, LINK_TX_PIN);
    g_sdrFloorDb = g_prefs.getFloat("sdrFloor", ESPSDR_FLOOR_DB);
    // A target saved by a build for another band or receiver is not ours.
    if (g_prefs.getUChar("tgtBand", 0) != kSdrBandTag || g_targetChannel < 1 || g_targetChannel > kSdrCount) g_haveTarget = false;
    if (g_haveTarget) {
        g_sdrChannel = g_targetChannel - 1;
        g_sdrMode = link::kModeStare;
    }
    sdrResync();
}

static void sendToSensor(uint8_t, const void*, size_t) {}

static void sensorMode(uint8_t mode) {
    g_sdrMode = mode;
    if (mode == link::kModeStare) {
        g_sdrChannel = g_targetChannel - 1;
        if (g_prefs.getUChar("tgtBand", 0) != kSdrBandTag) g_prefs.putUChar("tgtBand", kSdrBandTag);
    }
    else if (mode == link::kModeSurvey) { g_sdrChannel = 0; g_sdrPassCount = 0; }
    g_sdrRetune = true;  // applied before the next burst
    g_sdrBursts = 0;
    g_sdrReported = millis();
}

static void pollSensor() {
    while (Serial2.available()) {
        if (g_sdrState == kSdrData) {
            // Sample bytes are taken in blocks: one at a time would not keep
            // up with 2 Mbaud.
            const size_t want = g_sdrNeed - g_sdrGot;
            const size_t have = (size_t)Serial2.available();
            g_sdrGot += Serial2.read(g_sdrData + g_sdrGot, have < want ? have : want);
            if (g_sdrGot >= g_sdrNeed) {
                sdrBurstDone();
                sdrNext();
            }
            continue;
        }
        const int c = Serial2.read();
        if (c == '\n') {
            g_sdrLine[g_sdrLineLen] = 0;
            g_sdrLineLen = 0;
            sdrLine(g_sdrLine);
        } else if (c != '\r' && g_sdrLineLen < sizeof(g_sdrLine) - 1) {
            g_sdrLine[g_sdrLineLen++] = (char)c;
        }
    }
    // The clock is read afresh here: commands sent while reading above carry
    // a later time than one taken at the top of this function.
    const uint32_t now = millis();
    if ((int32_t)(now - g_sdrQuietUntil) >= 0 && now - g_sdrSent > kSdrTimeoutMs) sdrResync();  // no answer: start over
    g_sensorOk = g_sdrGood != 0 && now - g_sdrGood < 2000;

    if (g_sdrMode == link::kModeStare && now - g_sdrReported >= g_periodMs) {
        g_sdrReported = now;
        if (g_sdrBursts > 0) {
            // Sort the bursts of this period, then take the middle one (a burst
            // that landed on a gap or a spike does not move the reading) or,
            // for packet signals, the strongest.
            for (int i = 1; i < g_sdrBursts; i++)
                for (int j = i; j > 0 && g_sdrBurst[j] < g_sdrBurst[j - 1]; j--) {
                    const float t = g_sdrBurst[j];
                    g_sdrBurst[j] = g_sdrBurst[j - 1];
                    g_sdrBurst[j - 1] = t;
                }
            const float dbm = sdrToDbm(g_sdrBurst[kSdrPeakDetect ? g_sdrBursts - 1 : g_sdrBursts / 2]);
            g_sdrBursts = 0;
            g_sample.seq = g_sdrSeq++;
            // Within 3 dB of the floor is "nothing heard".
            g_sample.frames = dbm > -92.0f ? 3 : 0;
            g_sample.median = (int8_t)lroundf(dbm);
            g_sample.max = g_sample.median;
            g_sample.noise = -95;
            g_sample.channel = g_sdrChannel + 1;
            g_sampleCount++;
        }
    }
}
