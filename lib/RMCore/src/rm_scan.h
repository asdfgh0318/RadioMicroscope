// Sky map (signal strength per direction) and the raster scan that fills it.
#pragma once
#include <string.h>
#include "rm_geom.h"
#include "rm_stats.h"

namespace rm {

// Signal strength on a 5-degree grid. Azimuth cell i is centred on
// -180 + 5*i degrees, elevation cell j on -15 + 5*j degrees.
class SkyMap {
   public:
    static const int kAz = 72;
    static const int kEl = 23;
    static constexpr float kCell = 5.0f;
    static constexpr float kElFirst = -15.0f;
    static const int8_t kEmpty = -128;

    int8_t cell[kEl][kAz];

    SkyMap() { clear(); }
    void clear() { memset(cell, kEmpty, sizeof(cell)); }

    static int azIndex(float az) {
        int i = (int)lroundf((wrap180(az) + 180.0f) / kCell);
        return ((i % kAz) + kAz) % kAz;
    }
    static int elIndex(float el) {
        int j = (int)lroundf((el - kElFirst) / kCell);
        return j < 0 ? 0 : (j >= kEl ? kEl - 1 : j);
    }
    static float azCentre(int i) { return -180.0f + kCell * i; }
    static float elCentre(int j) { return kElFirst + kCell * j; }

    // Store a reading. azWidth and elWidth are how many degrees the reading
    // stands for: a scan with a step wider than one cell, or the wider
    // azimuth steps taken near the zenith, make one reading fill several
    // cells so the map has no gaps.
    void put(AzEl p, float dbm, float azWidth = kCell, float elWidth = kCell) {
        int8_t v = (int8_t)lroundf(clampf(dbm, -127.0f, 0.0f));
        // Readings are not centred on cells, so round the half-width up:
        // overlapping a neighbour is harmless, leaving a gap is not.
        int halfAz = (int)ceilf((azWidth / kCell - 1.0f) / 2.0f - 0.01f);
        if (halfAz < 0) halfAz = 0;
        if (halfAz > kAz / 2) halfAz = kAz / 2;
        int halfEl = (int)ceilf((elWidth / kCell - 1.0f) / 2.0f - 0.01f);
        if (halfEl < 0) halfEl = 0;
        int c = azIndex(p.az);
        int j0 = elIndex(p.el);
        for (int e = -halfEl; e <= halfEl; e++) {
            int j = j0 + e;
            if (j < 0 || j >= kEl) continue;
            for (int d = -halfAz; d <= halfAz; d++) cell[j][((c + d) % kAz + kAz) % kAz] = v;
        }
    }

    // Strongest direction on the map. One cell is a poor estimate when the
    // beam is tens of degrees wide and the readings are noisy, so the
    // position is the centroid of every cell within 6 dB of the strongest
    // (and within 60 degrees of it, to leave other sources out), weighted
    // by power above that threshold and by the sky area the cell covers.
    // Summing unit vectors keeps this correct across the +/-180 seam and
    // at the zenith.
    bool peak(AzEl& out, float& dbm) const {
        int bi = -1, bj = -1;
        int8_t best = kEmpty;
        for (int j = 0; j < kEl; j++)
            for (int i = 0; i < kAz; i++)
                if (cell[j][i] > best) { best = cell[j][i]; bi = i; bj = j; }
        if (bi < 0) return false;
        const AzEl top{azCentre(bi), elCentre(bj)};
        const float floorMw = dbmToMw(-6.0f);
        float x = 0, y = 0, z = 0;
        for (int j = 0; j < kEl; j++) {
            float el = elCentre(j) / kDegPerRad;
            float ce = cosf(el), se = sinf(el);
            float area = ce < 0.02f ? 0.02f : ce;
            for (int i = 0; i < kAz; i++) {
                int8_t v = cell[j][i];
                if (v == kEmpty || v < best - 6) continue;
                if (separation({azCentre(i), elCentre(j)}, top) > 60.0f) continue;
                float w = (dbmToMw((float)(v - best)) - floorMw + 0.01f) * area;
                float az = azCentre(i) / kDegPerRad;
                x += w * ce * cosf(az);
                y += w * ce * sinf(az);
                z += w * se;
            }
        }
        out.az = wrap180(atan2f(y, x) * kDegPerRad);
        out.el = atan2f(z, sqrtf(x * x + y * y)) * kDegPerRad;
        dbm = best;
        return true;
    }
};

struct ScanPlan {
    float azMin = -175, azMax = 175;
    float elMin = 0, elMax = 90;
    float step = 5;  // degrees between neighbouring points on the sky
};

// A small scan around a direction, for finding a source again close to
// where it was last seen: one beamwidth to each side, in steps of a third
// of a beamwidth (the same spacing as a whole-sky scan). The azimuth span is widened with elevation so
// that it covers the same angle on the sky.
inline ScanPlan localPlan(AzEl centre, float beamwidth, float azMin, float azMax, float elMin, float elMax) {
    const float half = beamwidth;
    float c = cosf(centre.el / kDegPerRad);
    const float azHalf = half / (c < 0.2f ? 0.2f : c);
    ScanPlan p;
    p.azMin = clampf(centre.az - azHalf, azMin, azMax);
    p.azMax = clampf(centre.az + azHalf, azMin, azMax);
    p.elMin = clampf(centre.el - half, elMin, elMax);
    p.elMax = clampf(centre.el + half, elMin, elMax);
    p.step = clampf(beamwidth / 3, 3, 10);
    return p;
}

// Generates the pointing sequence of a raster scan: rows of constant
// elevation, alternating direction so the head never flies back. The
// azimuth step widens as 1/cos(el), so points stay evenly spaced on the
// sky instead of crowding near the zenith.
class Scanner {
   public:
    void begin(const ScanPlan& p) {
        plan_ = p;
        if (plan_.step < 1) plan_.step = 1;
        rows_ = (int)floorf((plan_.elMax - plan_.elMin) / plan_.step + 0.001f) + 1;
        row_ = 0;
        col_ = 0;
        done_ = 0;
        total_ = 0;
        for (int r = 0; r < rows_; r++) total_ += colsIn(r);
    }

    // Next point to visit; false when the scan is complete.
    bool next(AzEl& out) {
        if (row_ >= rows_) return false;
        int n = colsIn(row_);
        float st = azStepIn(row_);
        float span = (n - 1) * st;
        float az0 = (plan_.azMin + plan_.azMax) / 2 - span / 2;
        int k = (row_ % 2 == 0) ? col_ : (n - 1 - col_);
        out.az = az0 + k * st;
        out.el = elOf(row_);
        width_ = n == 1 ? 360.0f : st;
        done_++;
        if (++col_ >= n) { col_ = 0; row_++; }
        return true;
    }

    // Azimuth width covered by the point last returned by next().
    float lastAzWidth() const { return width_; }
    int total() const { return total_; }
    int done() const { return done_; }

   private:
    float elOf(int r) const { return plan_.elMin + r * plan_.step; }
    float azStepIn(int r) const {
        float c = cosf(elOf(r) / kDegPerRad);
        return plan_.step / (c < 0.1f ? 0.1f : c);
    }
    int colsIn(int r) const {
        if (elOf(r) > 87.5f) return 1;  // the zenith is one point
        int n = (int)floorf((plan_.azMax - plan_.azMin) / azStepIn(r) + 0.001f) + 1;
        return n < 1 ? 1 : n;
    }

    ScanPlan plan_;
    int rows_ = 0, row_ = 0, col_ = 0, done_ = 0, total_ = 0;
    float width_ = 5;
};

}  // namespace rm
