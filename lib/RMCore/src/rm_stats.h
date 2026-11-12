// Signal-strength helpers.
#pragma once
#include <math.h>
#include <stdint.h>
#include <string.h>

namespace rm {

inline float dbmToMw(float dbm) { return powf(10.0f, dbm / 10.0f); }
inline float mwToDbm(float mw) { return 10.0f * log10f(mw); }

// Collects RSSI readings between two reports and returns their median.
// A histogram keeps insertion O(1), so it is cheap enough for the Wi-Fi
// receive callback. The median is used because single frames swing by
// several dB with multipath and a mean would chase the outliers.
class RssiWindow {
   public:
    static const int kMin = -110;  // readings below this land in the first bin
    static const int kBins = 111;  // -110 .. 0 dBm

    void clear() {
        memset(bins_, 0, sizeof(bins_));
        count_ = 0;
        max_ = kMin;
    }

    void add(int rssi) {
        if (rssi < kMin) rssi = kMin;
        if (rssi > 0) rssi = 0;
        if (bins_[rssi - kMin] < 0xFFFF) bins_[rssi - kMin]++;
        count_++;
        if (rssi > max_) max_ = rssi;
    }

    uint32_t count() const { return count_; }
    int max() const { return max_; }

    // Median of the readings; kMin when the window is empty.
    int median() const {
        if (count_ == 0) return kMin;
        uint32_t seen = 0, half = (count_ + 1) / 2;
        for (int i = 0; i < kBins; i++) {
            seen += bins_[i];
            if (seen >= half) return i + kMin;
        }
        return max_;
    }

   private:
    uint16_t bins_[kBins] = {};
    uint32_t count_ = 0;
    int max_ = kMin;
};

}  // namespace rm
