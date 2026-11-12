// Step tracker: keeps the antenna on a source by probing around it.
#pragma once
#include "rm_geom.h"

namespace rm {

// One tracking cycle measures the signal at five points: the current best
// direction and one dither step to each side in azimuth and elevation.
//
// Near its peak an antenna's gain in dB falls off as a parabola,
//   G(x) = G0 - 12 * (x / beamwidth)^2      (-3 dB at half the beamwidth),
// so the difference between the two side readings of an axis is
// proportional to how far the centre is from the peak:
//   offset = (plus - minus) * beamwidth^2 / (48 * dither).
// The centre moves by a fraction of that offset each cycle, which averages
// the measurement noise. The curvature is taken from the configured
// beamwidth rather than measured, because with a wide beam the measured
// curvature is smaller than the noise.
//
// Usage: point at nextPoint(), measure, call report(); repeat.
class Tracker {
   public:
    struct Config {
        float beamwidth = 40;       // antenna half-power beamwidth, degrees
        float ditherFraction = 0.5; // probe offset as a fraction of the beamwidth
        float gain = 0.5;           // fraction of the estimated offset applied per cycle
        float lostDbm = -92;        // a cycle with every reading below this is a miss
        int lostCycles = 3;         // misses in a row before giving up
        float elMin = -15, elMax = 95;
        // Azimuth travel. A full 360 degrees means the axis can turn freely and
        // azimuth wraps; anything less is a head with end stops, where probes
        // are clipped at the stops instead of sent round the long way.
        float azMin = -180, azMax = 180;
    };

    Config cfg;

    void start(AzEl at) {
        centre_ = at;
        idx_ = 0;
        missed_ = 0;
        lost_ = false;
        peak_ = -127;
    }

    AzEl centre() const { return centre_; }

    // The base the head stands on has turned by this many degrees (as when
    // it is carried in the hand): move the remembered direction with it so
    // the antenna keeps facing the same way in the world.
    void shiftAz(float deg) { centre_.az = limitAz(centre_.az + deg); }
    float peakDbm() const { return peak_; }
    float dither() const { return cfg.beamwidth * cfg.ditherFraction; }
    bool lost() const { return lost_; }

    // Direction to measure next.
    AzEl nextPoint() const {
        AzEl p = centre_;
        const float d = dither();
        switch (idx_) {
            case 1: p.az = limitAz(p.az + d * azScale()); break;
            case 2: p.az = limitAz(p.az - d * azScale()); break;
            case 3: p.el += d; break;
            case 4: p.el -= d; break;
            default: break;
        }
        p.el = clampf(p.el, cfg.elMin, cfg.elMax);
        return p;
    }

    // Result for the direction last returned by nextPoint(). valid=false
    // means no frames from the source were heard there.
    void report(bool valid, float dbm) {
        r_[idx_] = valid ? dbm : kFloor;
        if (++idx_ < 5) return;
        idx_ = 0;

        bool heard = false;
        for (float r : r_) heard = heard || r >= cfg.lostDbm;
        if (!heard) {
            if (++missed_ >= cfg.lostCycles) lost_ = true;
            return;
        }
        missed_ = 0;

        const float d = dither();
        // Probes are clipped at the travel limits, so their real distances
        // from the centre can differ from the dither.
        const float up = clampf(centre_.el + d, cfg.elMin, cfg.elMax) - centre_.el;
        const float down = centre_.el - clampf(centre_.el - d, cfg.elMin, cfg.elMax);
        float right = d, left = d;
        if (!azWraps()) {
            right = (limitAz(centre_.az + d * azScale()) - centre_.az) / azScale();
            left = (centre_.az - limitAz(centre_.az - d * azScale())) / azScale();
        }
        centre_.az = limitAz(centre_.az + cfg.gain * peakOffset(r_[2], r_[1], left, right) * azScale());
        centre_.el = clampf(centre_.el + cfg.gain * peakOffset(r_[4], r_[3], down, up), cfg.elMin, cfg.elMax);
        peak_ = r_[0];
    }

   private:
    static constexpr float kFloor = -100.0f;

    bool azWraps() const { return cfg.azMax - cfg.azMin >= 360.0f; }
    float limitAz(float az) const { return azWraps() ? wrap180(az) : clampf(az, cfg.azMin, cfg.azMax); }

    // An azimuth change of x degrees moves the beam x*cos(el) degrees on the
    // sky; this is the factor that undoes it (limited near the zenith).
    float azScale() const {
        float c = cosf(centre_.el / kDegPerRad);
        return 1.0f / (c < 0.2f ? 0.2f : c);
    }

    // Distance from the centre to the peak along one axis, in degrees on the
    // sky, from readings taken `below` degrees to one side and `above`
    // degrees to the other. With G(x) = G0 - k*(x - peak)^2 and
    // k = 12 / beamwidth^2:
    //   plus - minus = k*(below^2 - above^2) + 2*k*peak*(above + below).
    // For equal distances d this is (plus - minus) * beamwidth^2 / (48 * d).
    float peakOffset(float minus, float plus, float below, float above) const {
        if (above + below < 1.0f) return 0;
        const float k = 12.0f / (cfg.beamwidth * cfg.beamwidth);
        float off = ((plus - minus) / k - (below * below - above * above)) / (2.0f * (above + below));
        const float lim = 1.5f * dither();
        return clampf(off, -lim, lim);
    }

    AzEl centre_;
    float r_[5] = {};
    float peak_ = -127;
    int idx_ = 0;
    int missed_ = 0;
    bool lost_ = false;
};

}  // namespace rm
