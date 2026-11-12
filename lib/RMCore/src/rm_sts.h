// Feetech STS / Waveshare ST serial bus servo packets (ST3215 and family).
//
// Wire format, both directions:
//   0xFF 0xFF  ID  LEN  INSTR|ERR  PARAM...  CHK
// LEN counts the bytes after it (params + 2) and CHK is the inverted low
// byte of the sum of everything from ID to the last param. Multi-byte
// registers are little-endian; position and speed carry their sign in
// bit 15 (sign-magnitude, not two's complement).
//
// Register addresses follow Feetech's SMS_STS memory table.
#pragma once
#include <stddef.h>
#include <stdint.h>

namespace rm {
namespace sts {

enum Instr : uint8_t { kPing = 0x01, kRead = 0x02, kWrite = 0x03 };

enum Reg : uint8_t {
    kRegId = 5,               // stored in EEPROM: unlock with kRegLock first
    kRegMinAngle = 9,         // 2 bytes
    kRegMaxAngle = 11,        // 2 bytes
    kRegMode = 33,            // 0 = position servo
    kRegTorqueEnable = 40,    // 0 = free, 1 = hold, 128 = make the current position 2048
    kRegAcc = 41,             // units of 100 steps/s^2
    kRegGoalPosition = 42,    // 2 bytes, 0..4095
    kRegGoalTime = 44,        // 2 bytes
    kRegGoalSpeed = 46,       // 2 bytes, steps/s
    kRegLock = 55,            // 0 = EEPROM writable, 1 = locked
    kRegPresentPosition = 56, // 2 bytes
    kRegPresentSpeed = 58,    // 2 bytes
    kRegPresentLoad = 60,     // 2 bytes, 0.1 %, sign in bit 10
    kRegPresentVoltage = 62,  // 0.1 V
    kRegPresentTemp = 63,     // deg C
    kRegMoving = 66,
};

const size_t kMaxPacket = 24;

inline uint8_t checksum(const uint8_t* fromId, size_t n) {
    uint8_t s = 0;
    for (size_t i = 0; i < n; i++) s += fromId[i];
    return (uint8_t)~s;
}

// Builds a packet into out (at least kMaxPacket bytes); returns its length.
inline size_t build(uint8_t* out, uint8_t id, uint8_t instr, const uint8_t* params, uint8_t n) {
    out[0] = 0xFF;
    out[1] = 0xFF;
    out[2] = id;
    out[3] = n + 2;
    out[4] = instr;
    for (uint8_t i = 0; i < n; i++) out[5 + i] = params[i];
    out[5 + n] = checksum(out + 2, n + 3);
    return n + 6;
}

inline size_t buildPing(uint8_t* out, uint8_t id) { return build(out, id, kPing, nullptr, 0); }

inline size_t buildRead(uint8_t* out, uint8_t id, uint8_t addr, uint8_t count) {
    uint8_t p[2] = {addr, count};
    return build(out, id, kRead, p, 2);
}

inline size_t buildWriteByte(uint8_t* out, uint8_t id, uint8_t addr, uint8_t value) {
    uint8_t p[2] = {addr, value};
    return build(out, id, kWrite, p, 2);
}

inline uint16_t encodeSigned(int16_t v) { return v < 0 ? (uint16_t)(-v) | 0x8000 : (uint16_t)v; }

inline int16_t decodeSigned(uint16_t v, uint8_t signBit = 15) {
    uint16_t mask = (uint16_t)1 << signBit;
    return (v & mask) ? -(int16_t)(v & (mask - 1)) : (int16_t)v;
}

// Move to a position with a speed limit (steps/s) and acceleration
// (units of 100 steps/s^2). One write covers registers 41..47.
inline size_t buildGoal(uint8_t* out, uint8_t id, int16_t position, uint16_t speed, uint8_t acc) {
    uint16_t pos = encodeSigned(position);
    uint8_t p[8] = {kRegAcc, acc, (uint8_t)(pos & 0xFF), (uint8_t)(pos >> 8), 0, 0,
                    (uint8_t)(speed & 0xFF), (uint8_t)(speed >> 8)};
    return build(out, id, kWrite, p, 8);
}

struct Reply {
    uint8_t id = 0;
    uint8_t error = 0;  // servo status bits, 0 = healthy
    uint8_t len = 0;    // number of data bytes
    uint8_t data[16] = {};

    uint16_t u16(uint8_t at) const { return (uint16_t)(data[at] | (data[at + 1] << 8)); }
};

// Feeds received bytes one at a time; feed() returns true when a complete
// reply with a good checksum has been assembled.
class Parser {
   public:
    bool feed(uint8_t b, Reply& out) {
        switch (state_) {
            case 0:
                if (b == 0xFF) state_ = 1;
                return false;
            case 1:
                state_ = (b == 0xFF) ? 2 : 0;
                return false;
            case 2:
                if (b == 0xFF) return false;  // still in the preamble
                buf_[0] = b;
                state_ = 3;
                return false;
            case 3:
                if (b < 2 || b > sizeof(out.data) + 2) { state_ = 0; return false; }
                buf_[1] = b;
                need_ = b;
                got_ = 0;
                state_ = 4;
                return false;
            default:
                buf_[2 + got_++] = b;
                if (got_ < need_) return false;
                state_ = 0;
                if (checksum(buf_, need_ + 1) != buf_[need_ + 1]) return false;
                out.id = buf_[0];
                out.error = buf_[2];
                out.len = need_ - 2;
                for (uint8_t i = 0; i < out.len; i++) out.data[i] = buf_[3 + i];
                return true;
        }
    }
    void reset() { state_ = 0; }

   private:
    uint8_t buf_[kMaxPacket] = {};
    uint8_t state_ = 0, need_ = 0, got_ = 0;
};

}  // namespace sts
}  // namespace rm
