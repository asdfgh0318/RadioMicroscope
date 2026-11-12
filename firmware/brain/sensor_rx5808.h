// Sensor: RX5808 5.8 GHz analog video receiver module, wired straight to
// the brain. Selected with SENSOR_RX5808 1 in config.h; it replaces the
// ESP32-C5 sensor radio. Included by brain.ino after its globals.
//
// The module is tuned over its three-wire serial port (the "SPI mod") and
// reports signal strength as a voltage on its RSSI pin. Its video output
// goes to the goggles or monitor and does not touch this board.
//
// Tuning format and synthesiser formula follow the FENIX / rx5808-pro
// diversity firmware (papers/vrx-5g8/D_fenix_receiver_spi.cpp):
// 25 bits, least significant first: 4 address, 1 write flag, 20 data.
#pragma once

#include "fpv_channels.h"

static const uint32_t kRxSettleMs = 35;  // after retuning, before the RSSI reading is valid

static uint8_t g_rxMode = link::kModeIdle;
static uint8_t g_rxChannel = 0;  // index into kRxFreq
static uint32_t g_rxTuned = 0;   // when the module was last retuned
static uint32_t g_rxLast = 0;    // when the last reading was reported
static uint16_t g_rxSeq = 0;

static void rxBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        digitalWrite(RX5808_CLK_PIN, LOW);
        delayMicroseconds(1);
        digitalWrite(RX5808_DATA_PIN, bits & 1);
        delayMicroseconds(1);
        digitalWrite(RX5808_CLK_PIN, HIGH);
        delayMicroseconds(1);
        bits >>= 1;
    }
    digitalWrite(RX5808_CLK_PIN, LOW);
}

static void rxTune(uint8_t channel) {
    if (channel >= 48) channel = 0;
    const uint16_t f = kRxFreq[channel];
    const uint32_t reg = ((((f - 479) / 2) / 32) << 7) | (((f - 479) / 2) % 32);
    digitalWrite(RX5808_CS_PIN, LOW);
    delayMicroseconds(1);
    rxBits(0x01, 4);  // synthesiser register B
    rxBits(1, 1);     // write
    rxBits(reg, 20);
    digitalWrite(RX5808_CS_PIN, HIGH);
    digitalWrite(RX5808_DATA_PIN, LOW);
    g_rxChannel = channel;
    g_rxTuned = millis();
}

// The RSSI pin's voltage rises with signal strength. No datasheet figure
// for its slope could be retrieved, so the two end points are set in
// config.h from a measurement on the actual module (transmitter off, and
// transmitter a metre away). Between them the reading is treated as linear
// in decibels over 60 dB. The result is a relative level, good for finding
// and following a peak, not a calibrated power.
static float rxReadDbm() {
    uint32_t sum = 0;
    for (int i = 0; i < 8; i++) sum += analogReadMilliVolts(RX5808_RSSI_PIN);
    const float mv = sum / 8.0f;
    const float t = (mv - RX5808_RSSI_MIN_MV) / (float)(RX5808_RSSI_MAX_MV - RX5808_RSSI_MIN_MV);
    return -95.0f + 60.0f * clampf(t, 0, 1);
}

static void sensorBegin() {
    pinMode(RX5808_CS_PIN, OUTPUT);
    pinMode(RX5808_CLK_PIN, OUTPUT);
    pinMode(RX5808_DATA_PIN, OUTPUT);
    digitalWrite(RX5808_CS_PIN, HIGH);
    digitalWrite(RX5808_CLK_PIN, LOW);
    analogReadResolution(12);
    g_sensorOk = true;  // there is no way to ask the module whether it is there
    // A target saved by a Wi-Fi build is not one of the 48 video channels.
    if (g_prefs.getUChar("tgtBand", 0) != 58 || g_targetChannel < 1 || g_targetChannel > 48) g_haveTarget = false;
    rxTune(g_haveTarget ? g_targetChannel - 1 : 0);
    if (g_haveTarget) g_rxMode = link::kModeStare;
}

static void sendToSensor(uint8_t, const void*, size_t) {}

static void sensorMode(uint8_t mode) {
    g_rxMode = mode;
    if (mode == link::kModeStare) {
        rxTune(g_targetChannel - 1);
        if (g_prefs.getUChar("tgtBand", 0) != 58) g_prefs.putUChar("tgtBand", 58);
    }
    else if (mode == link::kModeSurvey) rxTune(0);
    g_rxLast = millis();
}

static void pollSensor() {
    const uint32_t now = millis();
    if (now - g_rxTuned < kRxSettleMs) return;
    if (g_rxMode == link::kModeSurvey) {
        rxReportChannel(g_rxChannel, rxReadDbm());
        rxTune((g_rxChannel + 1) % 48);
    } else if (g_rxMode == link::kModeStare && now - g_rxLast >= g_periodMs) {
        g_rxLast = now;
        const float dbm = rxReadDbm();
        g_sample.seq = g_rxSeq++;
        // An analog video carrier is always on, so one reading is as good as
        // several frames: three lets one report satisfy a scan or tracking
        // probe. A level within 3 dB of the floor is "nothing heard", so that
        // scans and bearings are not made from noise.
        g_sample.frames = dbm > -92.0f ? 3 : 0;
        g_sample.median = (int8_t)lroundf(dbm);
        g_sample.max = g_sample.median;
        g_sample.noise = -95;
        g_sample.channel = g_rxChannel + 1;
        g_sampleCount++;
    }
}
