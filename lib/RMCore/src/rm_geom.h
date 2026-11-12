// Angles, pointing directions and servo-count conversion.
#pragma once
#include <math.h>
#include <stdint.h>

namespace rm {

constexpr float kDegPerRad = 57.29577951f;

inline float clampf(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }

// Wrap to [-180, 180).
inline float wrap180(float d) {
    d = fmodf(d + 180.0f, 360.0f);
    if (d < 0) d += 360.0f;
    return d - 180.0f;
}

// Wrap to [0, 360).
inline float wrap360(float d) {
    d = fmodf(d, 360.0f);
    if (d < 0) d += 360.0f;
    return d;
}

// A pointing direction in degrees. az grows clockwise seen from above,
// el is 0 at the horizon and 90 at the zenith.
struct AzEl {
    float az = 0;
    float el = 0;
};

// Great-circle angle between two directions, degrees.
inline float separation(AzEl a, AzEl b) {
    const float e1 = a.el / kDegPerRad, e2 = b.el / kDegPerRad;
    const float dAz = (a.az - b.az) / kDegPerRad;
    float c = sinf(e1) * sinf(e2) + cosf(e1) * cosf(e2) * cosf(dAz);
    return acosf(clampf(c, -1.0f, 1.0f)) * kDegPerRad;
}

// One servo axis: maps mechanical degrees to 12-bit encoder counts
// (4096 counts per turn) and enforces the travel limits.
struct Axis {
    int16_t zeroCount = 2048;  // encoder count at 0 degrees
    int8_t dir = 1;            // +1 or -1: sign of counts per degree
    float minDeg = -178;
    float maxDeg = 178;

    static constexpr float kCountsPerDeg = 4096.0f / 360.0f;

    float clampDeg(float d) const { return clampf(d, minDeg, maxDeg); }

    int16_t toCounts(float deg) const {
        long c = zeroCount + dir * lroundf(clampDeg(deg) * kCountsPerDeg);
        if (c < 0) c = 0;
        if (c > 4095) c = 4095;
        return (int16_t)c;
    }

    float toDeg(int16_t counts) const { return dir * (counts - zeroCount) / kCountsPerDeg; }
};

}  // namespace rm
