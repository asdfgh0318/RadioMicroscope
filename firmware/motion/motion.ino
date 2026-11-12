// RadioMicroscope v2 - motor controller (brushless drivetrain)
// Board: classic ESP32 DevKit. Library: Simple FOC 2.4 or newer.
//
// Runs two gimbal motors in closed-loop angle control and takes pointing
// commands from the brain over a serial link. Pins and limits: config.h.
//
// First start, on the USB serial console (115200 baud):
//   cal    align each motor with its encoder. THE HEAD MOVES: each axis
//          swings about 30 degrees and back. Set the tilt near the middle
//          of its travel first. Done once; the result is stored and later
//          starts are motionless.
//   zero   store the present position as pan 0 / tilt 0. Point the head
//          straight ahead and level by hand first (motors free). Works
//          before or after cal.
//   free / hold   release / energise the motors
//   status        print angles and state

#include <Arduino.h>
#include <SPI.h>
#include <Preferences.h>
#include <SimpleFOC.h>
#include <RMCore.h>

#include "config.h"

using namespace rm;

struct AxisDrive {
    const char* name;
    BLDCMotor motor;
    BLDCDriver3PWM driver;
    MagneticSensorSPI sensor;
    float voltLimit;
    float minDeg, maxDeg;
    int dir;
    float zeroRaw = 0;    // encoder angle (radians, as the sensor counts) at 0 degrees, stored by "zero"
    float turnsDeg = 0;   // whole turns removed at start so the angle begins in [-180, 180)
    float targetDeg = 0;
    bool driverOk = false;

    AxisDrive(const char* n, int polePairs, int a, int b, int c, int en, int cs, float volts,
              float lo, float hi, int direction)
        : name(n), motor(polePairs), driver(a, b, c, en), sensor(AS5048_SPI, cs), voltLimit(volts),
          minDeg(lo), maxDeg(hi), dir(direction) {}

    // Head angle in degrees, straight from the encoder. It does not depend
    // on the motor alignment, so it is valid before "cal" and a stored zero
    // stays right whichever way alignment finds the motor to be wired.
    float angleDeg() { return dir * (sensor.getAngle() - zeroRaw) * kDegPerRad - turnsDeg; }

    // The motor library's shaft angle for a head angle: the encoder angle
    // with the sign that alignment found.
    float toShaftRad(float deg) {
        const float encoder = zeroRaw + dir * (deg + turnsDeg) / kDegPerRad;
        return (float)motor.sensor_direction * encoder - motor.sensor_offset;
    }

    void setTarget(float deg) { targetDeg = clampf(deg, minDeg, maxDeg); }
};

static AxisDrive g_pan("pan", PAN_POLE_PAIRS, PAN_PWM_A, PAN_PWM_B, PAN_PWM_C, PAN_ENABLE, PAN_ENCODER_CS,
                       PAN_VOLT_LIMIT, PAN_MIN, PAN_MAX, PAN_DIR);
static AxisDrive g_tilt("tilt", TILT_POLE_PAIRS, TILT_PWM_A, TILT_PWM_B, TILT_PWM_C, TILT_ENABLE,
                        TILT_ENCODER_CS, TILT_VOLT_LIMIT, TILT_MIN, TILT_MAX, TILT_DIR);
static AxisDrive* const g_axes[] = {&g_pan, &g_tilt};

static Preferences g_prefs;
static link::Parser g_parser;
static bool g_calibrated = false;
static bool g_torque = false;
static uint32_t g_lastPose = 0;

static String key(const AxisDrive& a, const char* what) { return String(a.name) + what; }

// Removes whole turns so that the angle reported at start lies in [-180, 180).
static void normaliseTurns(AxisDrive& a) {
    a.turnsDeg = 0;
    float d = a.angleDeg();
    a.turnsDeg = d - wrap180(d);
}

static void setTorque(bool on) {
    if (on && !g_calibrated) return;
    if (on && g_torque) return;  // already holding: enabling again would reset the control loop
    for (AxisDrive* a : g_axes) {
        if (!a->driverOk) continue;  // never touch a driver that failed to start
        if (on) {
            if (!g_torque) a->setTarget(a->angleDeg());  // hold where the head is now
            a->motor.enable();
        } else {
            a->motor.disable();
        }
    }
    g_torque = on;
}

// Starts encoder, driver and control loop for one axis. Called once, at
// power-up: the driver's PWM channels cannot be claimed twice. The motor is
// left disabled, so nothing moves.
static void beginAxis(AxisDrive& a) {
    a.sensor.init();
    a.motor.linkSensor(&a.sensor);
    a.zeroRaw = g_prefs.getFloat(key(a, "Zero").c_str(), 0);

    a.driver.voltage_power_supply = SUPPLY_VOLTS;
    // The driver centres its three outputs at half its own limit, so it
    // needs twice the motor limit of headroom or the waveform is clipped.
    a.driver.voltage_limit = fminf(2 * a.voltLimit, SUPPLY_VOLTS);
    a.driverOk = a.driver.init();
    if (!a.driverOk) {
        Serial.printf("%s: driver failed to start (check the PWM pins)\n", a.name);
        return;
    }
    a.motor.linkDriver(&a.driver);

    a.motor.controller = MotionControlType::angle;
    a.motor.torque_controller = TorqueControlType::voltage;
    a.motor.voltage_limit = a.voltLimit;
    a.motor.voltage_sensor_align = ALIGN_VOLTS;
    a.motor.velocity_limit = MAX_SPEED_DEG_S / kDegPerRad;
    a.motor.P_angle.P = 12;
    a.motor.PID_velocity.P = 0.15f;
    a.motor.PID_velocity.I = 4;
    a.motor.PID_velocity.output_ramp = 400;
    a.motor.LPF_velocity.Tf = 0.02f;
    a.motor.init();
    a.motor.disable();
}

// Links motor and encoder. With align = false the stored alignment is used
// and the motor does not move; with align = true the motor swings to find
// it and the result is stored.
static bool alignAxis(AxisDrive& a, bool align) {
    if (!a.driverOk) return false;
    if (align) {
        a.motor.zero_electric_angle = NOT_SET;
        a.motor.sensor_direction = Direction::UNKNOWN;
    } else {
        a.motor.zero_electric_angle = g_prefs.getFloat(key(a, "Zea").c_str(), 0);
        a.motor.sensor_direction = (Direction)g_prefs.getChar(key(a, "Dir").c_str(), 1);
    }
    a.motor.enable();
    bool ok = a.motor.initFOC();
    // During alignment the library compares the swing it commanded with what
    // the encoder saw. A mismatch means the pole-pair setting is wrong, and
    // the motor would run roughly or not at all.
    if (ok && align && !a.motor.pp_check_result) {
        Serial.printf("%s: pole-pair check failed: correct PAN/TILT_POLE_PAIRS in config.h\n", a.name);
        ok = false;
    }
    a.motor.disable();
    if (ok && align) {
        g_prefs.putFloat(key(a, "Zea").c_str(), a.motor.zero_electric_angle);
        g_prefs.putChar(key(a, "Dir").c_str(), (int8_t)a.motor.sensor_direction);
    }
    return ok;
}

static void alignAll(bool align) {
    g_torque = false;
    bool ok = true;
    for (AxisDrive* a : g_axes) {
        const bool one = alignAxis(*a, align);
        Serial.printf("%s: %s\n", a->name, one ? "ready" : "FAILED (check wiring and pole pairs)");
        ok = ok && one;
    }
    g_calibrated = ok;
    // A failed attempt leaves an earlier good alignment in place for the
    // next start.
    if (align && ok) g_prefs.putBool("cal", true);
}

static void sendPose() {
    link::MsgPose p{};
    p.az = g_pan.angleDeg();
    p.el = g_tilt.angleDeg();
    p.flags = (g_torque ? link::kPoseTorque : 0) | (g_calibrated ? link::kPoseCalibrated : 0);
    uint8_t buf[link::kMaxFrame];
    size_t n = link::encode(buf, link::kMsgPose, &p, sizeof(p));
    Serial2.write(buf, n);
}

static void pollLink() {
    link::Frame f;
    while (Serial2.available()) {
        if (!g_parser.feed((uint8_t)Serial2.read(), f)) continue;
        if (f.type == link::kCmdGoto) {
            link::CmdGoto c;
            if (!f.as(c) || !g_calibrated || !isfinite(c.az) || !isfinite(c.el)) continue;
            if (!g_torque) setTorque(true);
            g_pan.setTarget(c.az);
            g_tilt.setTarget(c.el);
        } else if (f.type == link::kCmdTorque) {
            link::CmdTorque c;
            if (f.as(c)) setTorque(c.on != 0);
        }
    }
}

static void consoleLine(const char* line) {
    if (!strcmp(line, "cal")) {
        Serial.println("aligning: each axis swings about 30 degrees and back");
        alignAll(true);
    } else if (!strcmp(line, "zero")) {
        setTorque(false);
        for (AxisDrive* a : g_axes) {
            a->sensor.update();
            a->zeroRaw = a->sensor.getAngle();
            a->turnsDeg = 0;
            g_prefs.putFloat(key(*a, "Zero").c_str(), a->zeroRaw);
        }
        Serial.println("zero stored: this position is now pan 0, tilt 0");
    } else if (!strcmp(line, "free")) {
        setTorque(false);
        Serial.println("motors free");
    } else if (!strcmp(line, "hold")) {
        setTorque(true);
        Serial.println(g_torque ? "motors holding" : "not aligned yet: run cal");
    } else if (!strcmp(line, "status")) {
        Serial.printf("pan %.1f  tilt %.1f  %s  %s\n", g_pan.angleDeg(), g_tilt.angleDeg(),
                      g_calibrated ? "aligned" : "NOT aligned (run cal)", g_torque ? "holding" : "free");
    } else if (*line) {
        Serial.println("commands: cal | zero | free | hold | status");
    }
}

static void pollConsole() {
    static char line[24];
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

void setup() {
    Serial.begin(115200);
    Serial2.begin(link::kBaud, SERIAL_8N1, LINK_RX_PIN, LINK_TX_PIN);
    g_prefs.begin("rm-motion", false);
    SPI.begin();

    for (AxisDrive* a : g_axes) {
        beginAxis(*a);
        a->sensor.update();
        normaliseTurns(*a);
    }
    if (g_prefs.getBool("cal", false)) alignAll(false);
    else Serial.println("not aligned yet: set the tilt mid-travel and type cal (each axis swings about 30 degrees)");
    Serial.println("RadioMicroscope motor controller ready");
}

void loop() {
    for (AxisDrive* a : g_axes) {
        if (g_torque) {
            a->motor.loopFOC();  // reads the encoder and sets the phase voltages
            a->motor.move(a->toShaftRad(a->targetDeg));
        } else {
            a->sensor.update();  // keep counting turns while the head is moved by hand
        }
    }
    pollLink();
    pollConsole();

    const uint32_t now = millis();
    if (now - g_lastPose >= 40) {
        g_lastPose = now;
        sendPose();
    }
}
