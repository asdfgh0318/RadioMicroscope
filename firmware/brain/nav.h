// Navigation sensors: IMU (MPU-6050) and compass (HMC5883L as on the
// BN-880, or QMC5883L as on the GY-271) on the I2C pins. Selected with
// NAV_SENSORS 1 in config.h. Included by brain.ino after its globals.
//
// Mount the IMU with its X arrow toward the antenna's zero direction and
// its top side up. The compass chip may sit turned or mirrored relative to
// the IMU: MAG_MOUNT_YAW and MAG_FLIP_Y in config.h take that out.
//
// First check after wiring: turn the unit clockwise seen from above and the
// heading must rise. If it falls, flip MAG_FLIP_Y.
//
// Keep the compass away from the gimbal motors: their magnets move relative
// to it and no calibration can remove that.
//
// Register addresses and scale factors below are from the parts'
// datasheets as commonly used; they have not been checked on hardware.
#pragma once
#include <Wire.h>

static TiltFilter g_tiltFilter;
static MagCalibration g_magCal;
static bool g_imuOk = false;
static bool g_magOk = false;
static bool g_magCalibrated = false;
static bool g_magCalibrating = false;
static uint32_t g_magCalStart = 0;
static uint8_t g_magAddr = 0;   // 0x1E = HMC5883L, 0x0D = QMC5883L
static float g_headSin = 0, g_headCos = 1;  // smoothed heading, kept as a vector so 359 -> 0 is smooth
static Vec3 g_gyroBias;         // gyroscope reading at rest, measured at start
static float g_yawRate = 0;     // degrees per second, clockwise positive

static const uint8_t kMpuAddr = 0x68;
static const uint32_t kMagCalMs = 30000;  // how long "calibrate compass" collects readings

static bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t value) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

static bool i2cRead(uint8_t addr, uint8_t reg, uint8_t* buf, uint8_t n) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom(addr, n) != n) return false;
    for (uint8_t i = 0; i < n; i++) buf[i] = Wire.read();
    return true;
}

static void navSaveCal() {
    g_prefs.putBytes("magOff", &g_magCal.offset, sizeof(Vec3));
    g_prefs.putBytes("magScl", &g_magCal.scale, sizeof(Vec3));
    g_prefs.putBool("magCal", true);
}

static void navBegin() {
    Wire.begin();
    Wire.setClock(400000);
    Wire.setTimeOut(20);

    // MPU-6050: wake up, 44 Hz filter; ranges stay at +/-2 g and +/-250 deg/s.
    g_imuOk = i2cWrite(kMpuAddr, 0x6B, 0x00) && i2cWrite(kMpuAddr, 0x1A, 0x03);
    if (g_imuOk) {
        // On combined boards (GY-87) the compass sits behind the MPU-6050 and
        // is reachable only with its pass-through switched on.
        i2cWrite(kMpuAddr, 0x6A, 0x00);
        i2cWrite(kMpuAddr, 0x37, 0x02);
        // The gyroscope reads a few degrees per second when perfectly still.
        // Measure that over half a second and subtract it from then on; the
        // unit must not be moved while it starts.
        delay(100);  // the chip needs a moment after waking
        float sum[3] = {0, 0, 0}, lo[3] = {1e9f, 1e9f, 1e9f}, hi[3] = {-1e9f, -1e9f, -1e9f};
        int n = 0;
        for (int i = 0; i < 50; i++) {
            uint8_t b[6];
            if (i2cRead(kMpuAddr, 0x43, b, 6)) {
                for (int k = 0; k < 3; k++) {
                    const float v = (int16_t)((b[2 * k] << 8) | b[2 * k + 1]) / 131.0f;
                    sum[k] += v;
                    lo[k] = fminf(lo[k], v);
                    hi[k] = fmaxf(hi[k], v);
                }
                n++;
            }
            delay(10);
        }
        // Readings that wander by more than 2 degrees per second mean the
        // unit was being moved: better no correction than a wrong one.
        const bool still = n > 0 && hi[0] - lo[0] < 2 && hi[1] - lo[1] < 2 && hi[2] - lo[2] < 2;
        if (still) g_gyroBias = {sum[0] / n, sum[1] / n, sum[2] / n};
        else Serial.println("gyroscope not still at start: no bias correction");
    }

    // Compass: try the HMC5883L, then the QMC5883L.
    uint8_t id[3];
    if (i2cRead(0x1E, 0x0A, id, 3) && id[0] == 'H' && id[1] == '4' && id[2] == '3') {
        g_magAddr = 0x1E;
        // 8-sample average at 15 Hz, +/-1.3 gauss, continuous measurement
        g_magOk = i2cWrite(0x1E, 0x00, 0x70) && i2cWrite(0x1E, 0x01, 0x20) && i2cWrite(0x1E, 0x02, 0x00);
    } else if (i2cWrite(0x0D, 0x0B, 0x01)) {
        g_magAddr = 0x0D;
        // continuous, 200 Hz, +/-2 gauss, 512x oversampling
        g_magOk = i2cWrite(0x0D, 0x09, 0x0D);
    }

    if (g_prefs.getBool("magCal", false)) {
        g_prefs.getBytes("magOff", &g_magCal.offset, sizeof(Vec3));
        g_prefs.getBytes("magScl", &g_magCal.scale, sizeof(Vec3));
        g_magCalibrated = true;
    }
    Serial.printf("IMU %s, compass %s\n", g_imuOk ? "found" : "missing",
                  !g_magOk ? "missing" : (g_magAddr == 0x1E ? "HMC5883L" : "QMC5883L"));
}

static bool navReadMag(Vec3& m) {
    uint8_t b[6];
    if (g_magAddr == 0x1E) {
        if (!i2cRead(0x1E, 0x03, b, 6)) return false;  // order X, Z, Y, high byte first
        m.x = (int16_t)((b[0] << 8) | b[1]);
        m.z = (int16_t)((b[2] << 8) | b[3]);
        m.y = (int16_t)((b[4] << 8) | b[5]);
        // -4096 marks a reading beyond the chip's range (a magnet nearby).
        if (m.x == -4096 || m.y == -4096 || m.z == -4096) return false;
    } else {
        uint8_t q[7];
        if (!i2cRead(0x0D, 0x00, q, 7)) return false;  // X, Y, Z low byte first, then status
        if (q[6] & 0x02) return false;                 // a reading beyond the chip's range
        memcpy(b, q, 6);
        m.x = (int16_t)(b[0] | (b[1] << 8));
        m.y = (int16_t)(b[2] | (b[3] << 8));
        m.z = (int16_t)(b[4] | (b[5] << 8));
    }
    return true;
}

static void navStartCalibration() {
    if (!g_magOk) return;
    g_magCal.begin();
    g_magCalibrating = true;
    g_magCalStart = millis();
}

// Called every pass of loop().
static void navPoll() {
    static uint32_t tImu = 0, tMag = 0;
    const uint32_t now = millis();

    if (g_imuOk && now - tImu >= 20) {
        const float dt = (now - tImu) / 1000.0f;
        tImu = now;
        uint8_t b[14];
        if (i2cRead(kMpuAddr, 0x3B, b, 14)) {
            Vec3 acc{(int16_t)((b[0] << 8) | b[1]) / 16384.0f, (int16_t)((b[2] << 8) | b[3]) / 16384.0f,
                     (int16_t)((b[4] << 8) | b[5]) / 16384.0f};
            Vec3 gyro{(int16_t)((b[8] << 8) | b[9]) / 131.0f - g_gyroBias.x,
                      (int16_t)((b[10] << 8) | b[11]) / 131.0f - g_gyroBias.y,
                      (int16_t)((b[12] << 8) | b[13]) / 131.0f - g_gyroBias.z};
            g_tiltFilter.update(acc, gyro, dt > 0.2f ? 0.2f : dt);
            g_att.pitch = g_tiltFilter.pitch();
            g_att.roll = g_tiltFilter.roll();
            g_yawRate = -gyro.z;  // clockwise positive; close to the turn rate while near level
        }
    }

    if (g_magOk && now - tMag >= 70) {
        tMag = now;
        Vec3 raw;
        if (navReadMag(raw)) {
            if (g_magCalibrating) {
                g_magCal.add(raw);
                if (now - g_magCalStart >= kMagCalMs) {
                    g_magCalibrating = false;
                    // Smallest sweep accepted: about a third of the horizontal field's swing.
                    const float minRange = g_magAddr == 0x1E ? 150 : 1500;
                    if (g_magCal.finish(minRange)) {
                        g_magCalibrated = true;
                        navSaveCal();
                        Serial.println("compass calibrated");
                    } else {
                        Serial.println("compass calibration failed: turn through a full circle");
                    }
                }
            } else if (g_magCalibrated) {
                // Without an IMU the heading is only right while level.
                const Vec3 body = mountToBody(g_magCal.apply(raw), MAG_MOUNT_YAW, MAG_FLIP_Y);
                const float h = headingFromMag(body, g_att.pitch, g_att.roll, MAG_DECLINATION);
                g_headSin += 0.5f * (sinf(h / kDegPerRad) - g_headSin);
                g_headCos += 0.5f * (cosf(h / kDegPerRad) - g_headCos);
                g_att.heading = wrap360(atan2f(g_headSin, g_headCos) * kDegPerRad);
            }
        }
    }
}

static bool navOk() { return g_magOk && g_magCalibrated && !g_magCalibrating; }

// Where the antenna points in the world, from the head angles and the
// attitude. When the sensors turn with the pan axis the compass already
// includes the pan angle. A fixed antenna has no pan axis: its direction
// on the vehicle (ANT_AZ, ANT_EL) always counts.
static AzEl navWorldDir() {
    // The smoothed heading lags a turning vehicle by about a tenth of a
    // second; lead it with the gyroscope's turn rate.
    Attitude att = g_att;
    att.heading = wrap360(att.heading + g_yawRate * 0.1f);
#if NAV_TURNS_WITH_PAN && !DRIVE_FIXED
    return bodyToWorld({0, g_now.el}, att);
#else
    return bodyToWorld(g_now, att);
#endif
}

// World azimuth of head angle zero. Taken at the horizon on purpose: at
// the antenna's own elevation the azimuth is ill-defined near the zenith
// and flips by 180 degrees beyond it.
static float navNorthOffset() {
#if NAV_TURNS_WITH_PAN && !DRIVE_FIXED
    return wrap180(bodyToWorld({0, 0}, g_att).az - g_now.az);
#else
    return wrap180(bodyToWorld({0, 0}, g_att).az);
#endif
}
