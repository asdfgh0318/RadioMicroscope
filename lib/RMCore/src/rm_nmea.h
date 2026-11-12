// Minimal GPS reader: position from NMEA GGA sentences.
#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace rm {

class Nmea {
   public:
    bool fix = false;   // true when the receiver reports a position fix
    uint8_t sats = 0;
    double lat = 0;     // degrees, north positive
    double lon = 0;     // degrees, east positive
    float alt = 0;      // metres above mean sea level

    // Feeds one received character. Returns true when a GGA sentence with a
    // good checksum has just updated the fields above.
    bool feed(char c) {
        if (c == '$') {
            len_ = 0;
            return false;
        }
        if (c != '\n' && c != '\r') {
            if (len_ < sizeof(buf_) - 1) buf_[len_++] = c;
            return false;
        }
        if (len_ == 0) return false;
        buf_[len_] = 0;
        size_t n = len_;
        len_ = 0;
        return parse(buf_, n);
    }

   private:
    // "ddmm.mmmm" -> degrees
    static double toDegrees(const char* s) {
        double v = atof(s);
        int d = (int)(v / 100);
        return d + (v - d * 100) / 60.0;
    }

    bool parse(char* s, size_t n) {
        // s is the sentence without '$': "GPGGA,...*hh"
        char* star = strrchr(s, '*');
        if (!star || (size_t)(star - s) + 3 > n) return false;
        uint8_t sum = 0;
        for (char* p = s; p < star; p++) sum ^= (uint8_t)*p;
        if (sum != (uint8_t)strtol(star + 1, nullptr, 16)) return false;
        *star = 0;
        if (strlen(s) < 6 || strncmp(s + 2, "GGA,", 4) != 0) return false;

        // Split on commas; empty fields are kept.
        const char* f[15] = {};
        int nf = 0;
        f[nf++] = s;
        for (char* p = s; *p && nf < 15; p++) {
            if (*p == ',') {
                *p = 0;
                f[nf++] = p + 1;
            }
        }
        if (nf < 10) return false;
        // 1 time, 2 lat, 3 N/S, 4 lon, 5 E/W, 6 fix quality, 7 satellites, 8 hdop, 9 altitude
        if (*f[2] && *f[4]) {
            lat = toDegrees(f[2]) * (f[3][0] == 'S' ? -1 : 1);
            lon = toDegrees(f[4]) * (f[5][0] == 'W' ? -1 : 1);
        }
        fix = atoi(f[6]) > 0;
        sats = (uint8_t)atoi(f[7]);
        if (*f[9]) alt = (float)atof(f[9]);
        return true;
    }

    char buf_[100] = {};
    size_t len_ = 0;
};

}  // namespace rm
