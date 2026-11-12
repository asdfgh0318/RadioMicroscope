// Drivetrain: two Waveshare ST3215 / Feetech STS serial bus servos.
// Selected with DRIVE_BRUSHLESS 0 in config.h. Included by brain.ino after
// its globals, so it uses them directly.
#pragma once

class ServoBus {
   public:
    void begin() {
        Serial1.setRxBufferSize(256);
        Serial1.begin(SERVO_BAUD, SERIAL_8N1, DRIVE_RX_PIN, DRIVE_TX_PIN);
    }

    bool ping(uint8_t id) {
        uint8_t b[sts::kMaxPacket];
        send(b, sts::buildPing(b, id));
        sts::Reply r;
        return await(id, r);
    }

    bool writeByte(uint8_t id, uint8_t addr, uint8_t value) {
        uint8_t b[sts::kMaxPacket];
        send(b, sts::buildWriteByte(b, id, addr, value));
        sts::Reply r;
        return await(id, r);
    }

    bool goal(uint8_t id, int16_t position) {
        uint8_t b[sts::kMaxPacket];
        send(b, sts::buildGoal(b, id, position, SERVO_SPEED, SERVO_ACC));
        sts::Reply r;
        return await(id, r);
    }

    bool read(uint8_t id, uint8_t addr, uint8_t count, sts::Reply& r) {
        uint8_t b[sts::kMaxPacket];
        send(b, sts::buildRead(b, id, addr, count));
        return await(id, r) && r.len == count;
    }

   private:
    void send(const uint8_t* p, size_t n) {
        while (Serial1.available()) Serial1.read();
        parser_.reset();
        memcpy(sent_, p, n);
        sentLen_ = n;
        echoed_ = 0;
        echoing_ = true;
        Serial1.write(p, n);
        Serial1.flush();
    }

    // When TX and RX share one wire, every byte sent comes back first. An
    // echoed packet has a valid checksum and the right address, so it would
    // pass for the servo's answer. Bytes are therefore held back while they
    // match what was sent, and dropped if the whole packet matches.
    bool await(uint8_t id, sts::Reply& r) {
        uint32_t t0 = millis();
        while (millis() - t0 < 8) {
            while (Serial1.available()) {
                uint8_t b = (uint8_t)Serial1.read();
                if (echoing_) {
                    if (b == sent_[echoed_]) {
                        if (++echoed_ == sentLen_) echoing_ = false;  // full echo: discard it
                        continue;
                    }
                    echoing_ = false;  // not an echo after all: hand over what was held back
                    for (size_t i = 0; i < echoed_; i++)
                        if (parser_.feed(sent_[i], r) && r.id == id) return true;
                }
                if (parser_.feed(b, r) && r.id == id) return true;
            }
        }
        return false;
    }

    sts::Parser parser_;
    uint8_t sent_[sts::kMaxPacket] = {};
    size_t sentLen_ = 0, echoed_ = 0;
    bool echoing_ = false;
};

static ServoBus g_bus;

static const char* const kDriveHelp =
    "commands: free | hold | ping | id <old> <new> | mid <id>\n"
    "  ping            list the servos that answer\n"
    "  id <old> <new>  change a servo's bus address (connect one servo at a time)\n"
    "  mid <id>        make the servo's present position its centre";

static void driveBegin() { g_bus.begin(); }

static void driveGoal(AzEl mech) {
    if (!g_torque) {
        g_bus.writeByte(PAN_ID, sts::kRegTorqueEnable, 1);
        g_bus.writeByte(TILT_ID, sts::kRegTorqueEnable, 1);
    }
    g_bus.goal(PAN_ID, g_pan.toCounts(mech.az));
    g_bus.goal(TILT_ID, g_tilt.toCounts(mech.el));
}

static void driveFree() {
    g_bus.writeByte(PAN_ID, sts::kRegTorqueEnable, 0);
    g_bus.writeByte(TILT_ID, sts::kRegTorqueEnable, 0);
}

// Called every pass of loop(): reads the encoders 25 times a second and
// the supply voltage and temperature every two seconds.
static void drivePoll() {
    static uint32_t tPos = 0, tHealth = 0;
    const uint32_t now = millis();
    sts::Reply r;
    if (now - tPos >= 40) {
        tPos = now;
        bool ok = true;
        if (g_bus.read(PAN_ID, sts::kRegPresentPosition, 2, r)) g_now.az = g_pan.toDeg(sts::decodeSigned(r.u16(0)));
        else ok = false;
        if (g_bus.read(TILT_ID, sts::kRegPresentPosition, 2, r)) g_now.el = g_tilt.toDeg(sts::decodeSigned(r.u16(0)));
        else ok = false;
        g_driveOk = ok;
    }
    if (now - tHealth >= 2000) {
        tHealth = now;
        if (g_bus.read(PAN_ID, sts::kRegPresentVoltage, 2, r)) {
            g_volts = r.data[0] / 10.0f;
            g_tempC = r.data[1];
        }
    }
}

static bool driveConsole(const char* line) {
    int a = 0, b = 0;
    if (!strcmp(line, "ping")) {
        for (int id = 1; id <= 10; id++)
            if (g_bus.ping(id)) Serial.printf("servo %d answers\n", id);
        Serial.println("ping done");
    } else if (sscanf(line, "id %d %d", &a, &b) == 2 && a > 0 && a < 254 && b > 0 && b < 254) {
        bool ok = g_bus.writeByte(a, sts::kRegLock, 0) && g_bus.writeByte(a, sts::kRegId, b);
        ok = g_bus.writeByte(b, sts::kRegLock, 1) && ok;
        Serial.printf("id %d -> %d: %s\n", a, b, ok ? "ok" : "FAILED");
    } else if (sscanf(line, "mid %d", &a) == 1 && a > 0 && a < 254) {
        bool ok = g_bus.writeByte(a, sts::kRegTorqueEnable, 128);
        Serial.printf("servo %d centre set: %s\n", a, ok ? "ok" : "FAILED");
    } else {
        return false;
    }
    return true;
}
