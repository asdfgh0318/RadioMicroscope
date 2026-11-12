// Serial links of the brain (ESP32-S3): one to the sensor radio (ESP32-C5)
// and, with the brushless drivetrain, one to the motor controller (ESP32).
// Both use the same framing.
//
// Frame:  0xA5 0x5A  LEN  TYPE  PAYLOAD[LEN]  CRC16(lo, hi)
// The CRC (CCITT, init 0xFFFF) covers LEN, TYPE and the payload.
#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string.h>

namespace rm {
namespace link {

const uint32_t kBaud = 460800;
const size_t kMaxPayload = 48;
const size_t kMaxFrame = kMaxPayload + 6;

enum Type : uint8_t {
    // brain -> sensor
    kCmdMode = 0x01,     // CmdMode
    kCmdPing = 0x02,     // empty
    // brain -> motor controller
    kCmdGoto = 0x10,     // CmdGoto
    kCmdTorque = 0x11,   // CmdTorque
    // sensor -> brain
    kMsgHello = 0x81,    // MsgHello: at boot, every second after, and in answer to a ping
    kMsgSample = 0x82,   // MsgSample, every report period while staring
    kMsgStation = 0x83,  // MsgStation, one per transmitter while surveying
    // motor controller -> brain
    kMsgPose = 0x90,     // MsgPose, 25 times a second
};

enum Mode : uint8_t {
    kModeIdle = 0,
    kModeSurvey = 1,  // hop over all channels, list every transmitter heard
    kModeStare = 2,   // sit on one channel, report one transmitter's level
};

enum Caps : uint8_t { kCap5GHz = 0x01 };

#pragma pack(push, 1)
struct CmdMode {
    uint8_t mode;       // Mode
    uint8_t channel;    // stare: Wi-Fi channel (1-14 or 36-177)
    uint8_t mac[6];     // stare: transmitter address to follow
    uint8_t periodMs;   // stare: report period, milliseconds
};

struct MsgHello {
    uint8_t version;
    uint8_t caps;  // Caps bits
    uint8_t boot;  // 1 in the first hello after the sensor starts, else 0
};

struct MsgSample {
    uint16_t seq;
    uint16_t frames;  // frames heard from the target this period
    int8_t median;    // dBm, valid when frames > 0
    int8_t max;       // dBm
    int8_t noise;     // dBm noise floor reported by the radio
    uint8_t channel;
};

struct MsgStation {
    uint8_t mac[6];
    uint8_t channel;
    int8_t rssi;       // strongest frame heard, dBm
    uint8_t isAp;      // 1 when a beacon was seen from it
    char ssid[33];     // zero-terminated; empty for stations and hidden APs
};
// Angles on the motor link are mechanical degrees: pan 0 = straight ahead,
// tilt 0 = horizon.
struct CmdGoto {
    float az;
    float el;
};

struct CmdTorque {
    uint8_t on;  // 0 = motors free, 1 = hold the present position
};

enum PoseFlags : uint8_t {
    kPoseTorque = 0x01,      // motors energised
    kPoseCalibrated = 0x02,  // motor/encoder alignment known; moves are accepted
};

struct MsgPose {
    float az;       // measured by the encoders
    float el;
    uint8_t flags;  // PoseFlags
};
#pragma pack(pop)

inline uint16_t crc16(const uint8_t* p, size_t n) {
    uint16_t c = 0xFFFF;
    for (size_t i = 0; i < n; i++) {
        c ^= (uint16_t)p[i] << 8;
        for (int b = 0; b < 8; b++) c = (c & 0x8000) ? (uint16_t)((c << 1) ^ 0x1021) : (uint16_t)(c << 1);
    }
    return c;
}

// Builds a frame into out (at least kMaxFrame bytes); returns its length,
// or 0 when the payload is too long.
inline size_t encode(uint8_t* out, uint8_t type, const void* payload, size_t n) {
    if (n > kMaxPayload) return 0;
    out[0] = 0xA5;
    out[1] = 0x5A;
    out[2] = (uint8_t)n;
    out[3] = type;
    if (n) memcpy(out + 4, payload, n);
    uint16_t c = crc16(out + 2, n + 2);
    out[4 + n] = (uint8_t)(c & 0xFF);
    out[5 + n] = (uint8_t)(c >> 8);
    return n + 6;
}

struct Frame {
    uint8_t type = 0;
    uint8_t len = 0;
    uint8_t payload[kMaxPayload] = {};

    // Copies the payload into a message struct; false on a size mismatch.
    template <typename T>
    bool as(T& msg) const {
        if (len != sizeof(T)) return false;
        memcpy(&msg, payload, sizeof(T));
        return true;
    }
};

// Feeds received bytes one at a time; feed() returns true when a complete
// frame with a good CRC has been assembled.
class Parser {
   public:
    bool feed(uint8_t b, Frame& out) {
        switch (state_) {
            case 0:
                if (b == 0xA5) state_ = 1;
                return false;
            case 1:
                state_ = (b == 0x5A) ? 2 : (b == 0xA5 ? 1 : 0);
                return false;
            case 2:
                if (b > kMaxPayload) { state_ = 0; return false; }
                buf_[0] = b;
                state_ = 3;
                return false;
            case 3:
                buf_[1] = b;
                got_ = 0;
                state_ = 4;
                return false;
            default:
                buf_[2 + got_++] = b;
                if (got_ < (size_t)buf_[0] + 2) return false;
                state_ = 0;
                {
                    size_t n = buf_[0];
                    uint16_t c = (uint16_t)(buf_[2 + n] | (buf_[3 + n] << 8));
                    if (crc16(buf_, n + 2) != c) return false;
                    out.len = (uint8_t)n;
                    out.type = buf_[1];
                    memcpy(out.payload, buf_ + 2, n);
                }
                return true;
        }
    }

   private:
    uint8_t buf_[kMaxPayload + 4] = {};
    uint8_t state_ = 0;
    size_t got_ = 0;
};

}  // namespace link
}  // namespace rm
