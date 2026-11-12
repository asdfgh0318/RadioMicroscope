// Locating a transmitter from several bearings taken at different places.
#pragma once
#include <math.h>
#include "rm_geom.h"

namespace rm {

// A position on a flat local map, metres east and north of a reference.
struct LocalPoint {
    float east = 0, north = 0;
};

// Latitude and longitude to the local map around (lat0, lon0). Good to a
// fraction of a percent over the few kilometres this is used for.
inline LocalPoint toLocal(double lat, double lon, double lat0, double lon0) {
    const double kEarth = 6371000.0, kRad = 3.14159265358979 / 180.0;
    LocalPoint p;
    p.north = (float)((lat - lat0) * kRad * kEarth);
    p.east = (float)((lon - lon0) * kRad * kEarth * cos(lat0 * kRad));
    return p;
}

inline void fromLocal(LocalPoint p, double lat0, double lon0, double& lat, double& lon) {
    const double kEarth = 6371000.0, kRad = 3.14159265358979 / 180.0;
    lat = lat0 + p.north / kEarth / kRad;
    lon = lon0 + p.east / (kEarth * cos(lat0 * kRad)) / kRad;
}

// Collects bearing lines and finds the point closest to all of them (least
// squares on the perpendicular distance to each line).
class BearingFix {
   public:
    void clear() { sxx_ = sxy_ = syy_ = bx_ = by_ = 0; n_ = 0; }

    // A bearing (degrees clockwise from north) observed from `from`.
    // weight lets stronger or cleaner observations count for more.
    void add(LocalPoint from, float bearingDeg, float weight = 1) {
        const float b = bearingDeg / kDegPerRad;
        // Unit normal of the line; a point p lies on it when n.(p - from) = 0.
        const float nx = cosf(b), ny = -sinf(b);
        const float d = nx * from.east + ny * from.north;
        sxx_ += weight * nx * nx;
        sxy_ += weight * nx * ny;
        syy_ += weight * ny * ny;
        bx_ += weight * nx * d;
        by_ += weight * ny * d;
        if (n_ < kMax) {
            from_[n_] = from;
            bearing_[n_] = bearingDeg;
        }
        n_++;
    }

    int count() const { return n_; }

    // Solves for the transmitter. Fails with fewer than two bearings or
    // when they are close to parallel (the lines never cross cleanly).
    // rmsMetres is the typical miss distance of the lines from the result;
    // behind counts bearings that point away from it, a sign of a reflection
    // or a wrong peak.
    bool solve(LocalPoint& out, float& rmsMetres, int& behind) const {
        if (n_ < 2) return false;
        const float det = sxx_ * syy_ - sxy_ * sxy_;
        // sxx + syy is the total weight; det is small against its square
        // when all normals point nearly the same way.
        const float total = sxx_ + syy_;
        if (det < 0.01f * total * total) return false;
        out.east = (syy_ * bx_ - sxy_ * by_) / det;
        out.north = (sxx_ * by_ - sxy_ * bx_) / det;
        float sum = 0;
        behind = 0;
        const int m = n_ < kMax ? n_ : kMax;
        for (int i = 0; i < m; i++) {
            const float b = bearing_[i] / kDegPerRad;
            const float de = out.east - from_[i].east, dn = out.north - from_[i].north;
            const float miss = cosf(b) * de - sinf(b) * dn;
            sum += miss * miss;
            if (sinf(b) * de + cosf(b) * dn < 0) behind++;
        }
        rmsMetres = sqrtf(sum / m);
        return true;
    }

   private:
    static const int kMax = 32;  // bearings kept for the miss-distance check
    float sxx_ = 0, sxy_ = 0, syy_ = 0, bx_ = 0, by_ = 0;
    LocalPoint from_[kMax];
    float bearing_[kMax] = {};
    int n_ = 0;
};

}  // namespace rm
