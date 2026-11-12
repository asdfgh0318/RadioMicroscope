// Attitude: which way the vehicle (or the base of the head) is facing and
// how it is tilted, from an accelerometer, a gyroscope and a compass.
//
// Frames used throughout:
//   body   x forward, y left, z up (as the sensor board sits when level)
//   world  azimuth clockwise from north, elevation up from the horizon
// Angles: heading clockwise from north; pitch positive nose up; roll
// positive right side down. All in degrees.
#pragma once
#include <math.h>
#include "rm_geom.h"

namespace rm {

struct Vec3 {
    float x = 0, y = 0, z = 0;
};

struct Attitude {
    float heading = 0;
    float pitch = 0;
    float roll = 0;
};

// Roll and pitch from the accelerometer alone. Exact when the vehicle is
// not accelerating; any acceleration tilts the answer.
inline void tiltFromAccel(Vec3 a, float& pitch, float& roll) {
    pitch = atan2f(a.x, sqrtf(a.y * a.y + a.z * a.z)) * kDegPerRad;
    roll = atan2f(a.y, a.z) * kDegPerRad;
}

// The body axes expressed in a level frame (forward, left, up) for a given
// pitch and roll. Shared by the heading and the direction conversion.
struct TiltBasis {
    Vec3 fwd, left, up;
    TiltBasis(float pitchDeg, float rollDeg) {
        const float p = pitchDeg / kDegPerRad, r = rollDeg / kDegPerRad;
        const float cp = cosf(p), sp = sinf(p), cr = cosf(r), sr = sinf(r);
        fwd = {cp, 0, sp};
        left = {-sp * sr, cr, cp * sr};
        up = {-sp * cr, -sr, cp * cr};
    }
    // Body vector -> level frame (forward, left, up).
    Vec3 level(Vec3 b) const {
        return {b.x * fwd.x + b.y * left.x + b.z * up.x,
                b.x * fwd.y + b.y * left.y + b.z * up.y,
                b.x * fwd.z + b.y * left.z + b.z * up.z};
    }
};

// Compass heading with the tilt taken out: the magnetic field is rotated
// back to level before its horizontal direction is read. Add the local
// magnetic declination for a true heading.
inline float headingFromMag(Vec3 m, float pitch, float roll, float declination = 0) {
    Vec3 h = TiltBasis(pitch, roll).level(m);
    return wrap360(atan2f(h.y, h.x) * kDegPerRad + declination);
}

// Converts a direction given relative to the vehicle (azimuth clockwise
// from its nose, elevation above its deck) into a world direction.
inline AzEl bodyToWorld(AzEl body, const Attitude& att) {
    const float az = body.az / kDegPerRad, el = body.el / kDegPerRad;
    // "left" is the negative of "right", hence the minus sign.
    Vec3 d = TiltBasis(att.pitch, att.roll).level({cosf(el) * cosf(az), -cosf(el) * sinf(az), sinf(el)});
    AzEl w;
    // In the level frame, forward is at the heading and left is 90 degrees
    // anticlockwise of it.
    w.az = wrap360(att.heading + atan2f(-d.y, d.x) * kDegPerRad);
    w.el = asinf(clampf(d.z, -1.0f, 1.0f)) * kDegPerRad;
    return w;
}

// A compass chip is rarely mounted square with the IMU. This turns its
// reading into the IMU's body axes: yawDeg is how far the chip's X arrow is
// turned clockwise (seen from above) from the IMU's X arrow, and flipY
// mirrors the chip's Y axis for boards whose Y arrow points right.
// It must be applied before the tilt is taken out, not added to the heading
// afterwards: tilt compensation needs the field in the IMU's own axes.
inline Vec3 mountToBody(Vec3 m, float yawDeg, bool flipY = false) {
    const float t = yawDeg / kDegPerRad;
    const float my = flipY ? -m.y : m.y;
    return {m.x * cosf(t) + my * sinf(t), -m.x * sinf(t) + my * cosf(t), m.z};
}

// Blends the gyroscope (smooth, but drifts) with the accelerometer (no
// drift, but disturbed by every acceleration) into a steady tilt estimate.
//
// The state is the "up" direction as seen from the body. The gyroscope
// turns it (a vector fixed in the world moves through the body axes at
// minus the body's rotation), then it is pulled gently toward what the
// accelerometer says. Tracking the vector, rather than adding gyro rates to
// pitch and roll, stays correct while a tilted vehicle turns.
class TiltFilter {
   public:
    float timeConstant = 0.5f;  // seconds; longer trusts the gyroscope more

    // gyro in degrees per second about the body axes, dt in seconds.
    void update(Vec3 accel, Vec3 gyro, float dt) {
        const float an = sqrtf(accel.x * accel.x + accel.y * accel.y + accel.z * accel.z);
        if (an < 1e-6f) return;
        const Vec3 a{accel.x / an, accel.y / an, accel.z / an};
        if (!started_) {
            up_ = a;
            started_ = true;
            return;
        }
        const float wx = gyro.x / kDegPerRad, wy = gyro.y / kDegPerRad, wz = gyro.z / kDegPerRad;
        // up' = up - (w x up) * dt
        Vec3 v{up_.x - (wy * up_.z - wz * up_.y) * dt,
               up_.y - (wz * up_.x - wx * up_.z) * dt,
               up_.z - (wx * up_.y - wy * up_.x) * dt};
        const float k = timeConstant / (timeConstant + dt);
        v = {k * v.x + (1 - k) * a.x, k * v.y + (1 - k) * a.y, k * v.z + (1 - k) * a.z};
        const float n = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        up_ = {v.x / n, v.y / n, v.z / n};
    }
    float pitch() const { float p, r; tiltFromAccel(up_, p, r); return p; }
    float roll() const { float p, r; tiltFromAccel(up_, p, r); return r; }

   private:
    Vec3 up_{0, 0, 1};
    bool started_ = false;
};

// Compass calibration. Iron near the sensor shifts and stretches its
// readings; turning the vehicle through a full circle (and tilting it, if
// possible) while feeding add() finds the shift and stretch of each axis.
class MagCalibration {
   public:
    Vec3 offset;
    Vec3 scale{1, 1, 1};

    void begin() {
        lo_ = {1e9f, 1e9f, 1e9f};
        hi_ = {-1e9f, -1e9f, -1e9f};
    }
    void add(Vec3 raw) {
        lo_.x = fminf(lo_.x, raw.x); hi_.x = fmaxf(hi_.x, raw.x);
        lo_.y = fminf(lo_.y, raw.y); hi_.y = fmaxf(hi_.y, raw.y);
        lo_.z = fminf(lo_.z, raw.z); hi_.z = fmaxf(hi_.z, raw.z);
    }
    // Returns false when the two horizontal axes were not swept through
    // enough range to trust the result (minRange in sensor units).
    bool finish(float minRange) {
        const float rx = hi_.x - lo_.x, ry = hi_.y - lo_.y, rz = hi_.z - lo_.z;
        if (rx < minRange || ry < minRange) return false;
        offset.x = (hi_.x + lo_.x) / 2;
        offset.y = (hi_.y + lo_.y) / 2;
        const float mean = (rx + ry) / 2;
        scale.x = mean / rx;
        scale.y = mean / ry;
        // A level turn does not exercise the vertical axis: leave it alone
        // unless it was swept too.
        if (rz >= minRange) {
            offset.z = (hi_.z + lo_.z) / 2;
            scale.z = mean / rz;
        } else {
            offset.z = 0;
            scale.z = 1;
        }
        return true;
    }
    Vec3 apply(Vec3 raw) const {
        return {(raw.x - offset.x) * scale.x, (raw.y - offset.y) * scale.y, (raw.z - offset.z) * scale.z};
    }

   private:
    Vec3 lo_, hi_;
};

}  // namespace rm
