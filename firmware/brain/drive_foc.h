// Drivetrain: brushless gimbal motors run by the motor controller
// (firmware/motion) over a serial link. Selected with DRIVE_BRUSHLESS 1 in
// config.h. Included by brain.ino after its globals, so it uses them
// directly.
#pragma once

static link::Parser g_driveParser;
static uint32_t g_poseSeen = 0;
static bool g_driveCalibrated = false;
static uint32_t g_goalSent = 0;   // when the last pointing command went out

static const char* const kDriveHelp =
    "commands: free | hold\n"
    "  Motor alignment and the zero position are set on the motor\n"
    "  controller's own USB console (cal, zero).";

static void driveSend(uint8_t type, const void* payload, size_t n) {
    uint8_t buf[link::kMaxFrame];
    size_t len = link::encode(buf, type, payload, n);
    if (len) Serial1.write(buf, len);
}

static void driveBegin() {
    Serial1.setRxBufferSize(512);
    Serial1.begin(link::kBaud, SERIAL_8N1, DRIVE_RX_PIN, DRIVE_TX_PIN);
}

static void driveGoal(AzEl mech) {
    link::CmdGoto c{};
    c.az = mech.az;
    c.el = mech.el;
    driveSend(link::kCmdGoto, &c, sizeof(c));
    g_goalSent = millis();
}

static void driveFree() {
    link::CmdTorque c{};
    c.on = 0;
    driveSend(link::kCmdTorque, &c, sizeof(c));
}

// Called every pass of loop(): takes in the pose reports. The drivetrain
// counts as working while reports keep arriving and the controller says
// its motors are aligned.
static void drivePoll() {
    link::Frame f;
    while (Serial1.available()) {
        if (!g_driveParser.feed((uint8_t)Serial1.read(), f) || f.type != link::kMsgPose) continue;
        link::MsgPose p;
        if (!f.as(p)) continue;
        g_now.az = p.az;
        g_now.el = p.el;
        g_driveCalibrated = p.flags & link::kPoseCalibrated;
        // The controller can drop torque on its own (its console, a restart).
        // Reports sent before it saw our last command still say "free": give
        // it a moment before believing them.
        if (!(p.flags & link::kPoseTorque) && millis() - g_goalSent > 300) g_torque = false;
        g_poseSeen = millis();
    }
    g_driveOk = g_driveCalibrated && g_poseSeen != 0 && millis() - g_poseSeen < 500;
}

static bool driveConsole(const char*) { return false; }
