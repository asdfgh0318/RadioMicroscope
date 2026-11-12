// RadioMicroscope v2 - sensor radio
// Board: Seeed XIAO ESP32-C5 (2.4 + 5 GHz) with the directional antenna on
// its U.FL socket. Also builds for other ESP32 boards (2.4 GHz only).
//
// This radio never joins or serves a network. It listens in monitor mode
// and reports signal strength to the brain over a serial link:
//   survey: hop across every channel and list each transmitter heard
//   stare:  stay on one channel and report one transmitter's level
//           every few tens of milliseconds
//
// Wiring: D6 (TX) -> brain RX, D7 (RX) <- brain TX, GND, 5V.

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <RMCore.h>

using namespace rm;

#define LINK_TX_PIN D6
#define LINK_RX_PIN D7

static const uint8_t kVersion = 2;
static const uint32_t kSurveyDwellMs = 130;  // longer than the usual 102 ms beacon interval
static const int kMaxStations = 48;

static const uint8_t kChannels24[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
#if SOC_WIFI_SUPPORT_5G
static const uint8_t kChannels5[] = {36,  40,  44,  48,  52,  56,  60,  64,  100, 104, 108, 112, 116,
                                     120, 124, 128, 132, 136, 140, 144, 149, 153, 157, 161, 165};
#endif

struct Station {
    uint8_t mac[6];
    uint8_t channel;
    int8_t rssi;
    bool isAp;
    char ssid[33];
};

// Shared between the Wi-Fi receive callback and loop(); guarded by g_lock.
static portMUX_TYPE g_lock = portMUX_INITIALIZER_UNLOCKED;
static RssiWindow g_window;
static int8_t g_noise = -127;
static Station g_stations[kMaxStations];
static int g_stationCount = 0;

static volatile uint8_t g_mode = link::kModeIdle;
static volatile uint8_t g_channel = 1;
static uint8_t g_target[6];
static uint8_t g_periodMs = 50;

static link::Parser g_parser;
static uint16_t g_seq = 0;
static uint32_t g_lastReport = 0;
static uint32_t g_lastHop = 0;
static uint32_t g_lastHello = 0;
static link::CmdMode g_current{};  // the command now in force
static int g_hopIndex = 0;

static void sendFrame(uint8_t type, const void* payload, size_t n) {
    uint8_t buf[link::kMaxFrame];
    size_t len = link::encode(buf, type, payload, n);
    if (len) Serial1.write(buf, len);
}

// The hello doubles as a heartbeat: the brain treats three seconds of
// silence as a dead sensor, and a survey sweep alone is longer than that.
static void sendHello(bool boot) {
    link::MsgHello h{};
    h.version = kVersion;
    h.boot = boot ? 1 : 0;
    g_lastHello = millis();
#if SOC_WIFI_SUPPORT_5G
    h.caps = link::kCap5GHz;
#endif
    sendFrame(link::kMsgHello, &h, sizeof(h));
}

static int channelCount() {
#if SOC_WIFI_SUPPORT_5G
    return sizeof(kChannels24) + sizeof(kChannels5);
#else
    return sizeof(kChannels24);
#endif
}

static uint8_t channelAt(int i) {
#if SOC_WIFI_SUPPORT_5G
    if (i >= (int)sizeof(kChannels24)) return kChannels5[i - sizeof(kChannels24)];
#endif
    return kChannels24[i];
}

// Returns false when the radio refuses the channel (not allowed in the
// configured country); the radio then stays where it was.
static bool tune(uint8_t channel) {
    if (esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE) != ESP_OK) return false;
    g_channel = channel;
    return true;
}

// Records a transmitter in the survey table. Called with g_lock held.
static void noteStation(const uint8_t* mac, int8_t rssi, bool beacon, const uint8_t* ssid, uint8_t ssidLen) {
    Station* s = nullptr;
    for (int i = 0; i < g_stationCount; i++) {
        if (memcmp(g_stations[i].mac, mac, 6) == 0) { s = &g_stations[i]; break; }
    }
    if (!s) {
        if (g_stationCount < kMaxStations) {
            s = &g_stations[g_stationCount++];
        } else {
            // Table full: replace the weakest entry if this one is stronger.
            Station* weakest = &g_stations[0];
            for (int i = 1; i < kMaxStations; i++)
                if (g_stations[i].rssi < weakest->rssi) weakest = &g_stations[i];
            if (rssi <= weakest->rssi) return;
            s = weakest;
        }
        memcpy(s->mac, mac, 6);
        s->rssi = -127;
        s->isAp = false;
        s->ssid[0] = 0;
        s->channel = g_channel;
    }
    if (rssi > s->rssi) {
        s->rssi = rssi;
        s->channel = g_channel;  // a transmitter leaks into neighbouring channels; keep the loudest
    }
    if (beacon) {
        s->isAp = true;
        if (ssidLen > 32) ssidLen = 32;
        memcpy(s->ssid, ssid, ssidLen);
        s->ssid[ssidLen] = 0;
    }
}

// Runs in the Wi-Fi task for every frame received.
static void onFrame(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT && type != WIFI_PKT_DATA) return;
    const wifi_promiscuous_pkt_t* pkt = (const wifi_promiscuous_pkt_t*)buf;
#if CONFIG_SOC_WIFI_HE_SUPPORT
    const uint16_t len = pkt->rx_ctrl.dump_len;  // bytes actually present in payload
#else
    const uint16_t len = pkt->rx_ctrl.sig_len;
#endif
    if (len < 24) return;
    const uint8_t* f = pkt->payload;
    const uint8_t* transmitter = f + 10;  // address 2 of the 802.11 header
    const int8_t rssi = pkt->rx_ctrl.rssi;
    const uint8_t mode = g_mode;

    if (mode == link::kModeStare) {
        if (memcmp(transmitter, g_target, 6) != 0) return;
        portENTER_CRITICAL(&g_lock);
        g_window.add(rssi);
        g_noise = pkt->rx_ctrl.noise_floor;
        portEXIT_CRITICAL(&g_lock);
    } else if (mode == link::kModeSurvey) {
        // Beacon (0x80) or probe response (0x50): the SSID is the first tagged
        // field, after the 24-byte header and 12 bytes of fixed fields.
        bool beacon = type == WIFI_PKT_MGMT && (f[0] == 0x80 || f[0] == 0x50);
        const uint8_t* ssid = nullptr;
        uint8_t ssidLen = 0;
        if (beacon && len >= 38 && f[36] == 0 && 38 + f[37] <= len) {
            ssid = f + 38;
            ssidLen = f[37];
        }
        portENTER_CRITICAL(&g_lock);
        noteStation(transmitter, rssi, beacon, ssid, ssidLen);
        portEXIT_CRITICAL(&g_lock);
    }
}

static void setMode(const link::CmdMode& c) {
    // A repeated command must not restart a survey sweep or empty the window.
    if (memcmp(&c, &g_current, sizeof(c)) == 0) return;
    g_current = c;
    g_mode = link::kModeIdle;  // stop the callback touching state while it changes
    portENTER_CRITICAL(&g_lock);
    g_window.clear();
    g_stationCount = 0;
    memcpy(g_target, c.mac, 6);
    portEXIT_CRITICAL(&g_lock);
    g_periodMs = c.periodMs < 10 ? 10 : c.periodMs;
    g_lastReport = millis();
    if (c.mode == link::kModeStare) {
        if (!tune(c.channel)) Serial.printf("channel %u refused by the radio\n", c.channel);
    } else if (c.mode == link::kModeSurvey) {
        g_hopIndex = 0;
        g_lastHop = millis();
        tune(channelAt(0));
    }
    g_mode = c.mode;
    Serial.printf("mode %u channel %u\n", c.mode, c.channel);
}

static void reportSample() {
    link::MsgSample m{};
    portENTER_CRITICAL(&g_lock);
    m.frames = (uint16_t)min<uint32_t>(g_window.count(), 0xFFFF);
    m.median = (int8_t)g_window.median();
    m.max = (int8_t)g_window.max();
    m.noise = g_noise;
    g_window.clear();
    portEXIT_CRITICAL(&g_lock);
    m.seq = g_seq++;
    m.channel = g_channel;
    sendFrame(link::kMsgSample, &m, sizeof(m));
}

// End of a survey sweep: send the table to the brain and start again.
static void reportStations() {
    static Station copy[kMaxStations];
    portENTER_CRITICAL(&g_lock);
    int n = g_stationCount;
    memcpy(copy, g_stations, sizeof(Station) * n);
    g_stationCount = 0;
    portEXIT_CRITICAL(&g_lock);
    for (int i = 0; i < n; i++) {
        link::MsgStation m{};
        memcpy(m.mac, copy[i].mac, 6);
        m.channel = copy[i].channel;
        m.rssi = copy[i].rssi;
        m.isAp = copy[i].isAp;
        memcpy(m.ssid, copy[i].ssid, sizeof(m.ssid));
        sendFrame(link::kMsgStation, &m, sizeof(m));
    }
    Serial.printf("survey sweep: %d transmitters\n", n);
}

void setup() {
    Serial.begin(115200);
    Serial1.setRxBufferSize(512);
    Serial1.begin(link::kBaud, SERIAL_8N1, LINK_RX_PIN, LINK_TX_PIN);

    g_window.clear();
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // Without a country the radio allows channels 1-11 only; Poland also
    // uses 12 and 13 and the 5 GHz channels listed above.
    esp_wifi_set_country_code("PL", false);
#if SOC_WIFI_SUPPORT_5G
    esp_wifi_set_band_mode(WIFI_BAND_MODE_AUTO);
#endif
    wifi_promiscuous_filter_t filter = {};
    filter.filter_mask = WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA;
    esp_wifi_set_promiscuous_filter(&filter);
    esp_wifi_set_promiscuous_rx_cb(onFrame);
    esp_wifi_set_promiscuous(true);
    tune(1);

    sendHello(true);
    Serial.println("RadioMicroscope sensor ready");
}

void loop() {
    link::Frame frame;
    while (Serial1.available()) {
        if (!g_parser.feed((uint8_t)Serial1.read(), frame)) continue;
        if (frame.type == link::kCmdPing) {
            sendHello(false);
        } else if (frame.type == link::kCmdMode) {
            link::CmdMode c;
            if (frame.as(c)) setMode(c);
        }
    }

    const uint32_t now = millis();
    if (g_mode == link::kModeStare) {
        if (now - g_lastReport >= g_periodMs) {
            g_lastReport = now;
            reportSample();
        }
    } else if (g_mode == link::kModeSurvey) {
        if (now - g_lastHop >= kSurveyDwellMs) {
            g_lastHop = now;
            if (++g_hopIndex >= channelCount()) {
                g_hopIndex = 0;
                reportStations();
            }
            tune(channelAt(g_hopIndex));
        }
    }
    if (now - g_lastHello >= 1000) sendHello(false);
    delay(1);
}
