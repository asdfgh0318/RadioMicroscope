// The 48 analog FPV video channels on 5.8 GHz, shared by the receivers
// that tune by channel.
#pragma once

static const uint16_t kRxFreq[48] = {
    5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725,  // A
    5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866,  // B
    5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945,  // E
    5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880,  // F
    5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917,  // R (race band)
    5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621,  // L
};
static const char kRxBand[] = "ABEFRL";

// Lists one channel in the survey table as a "transmitter" named by its
// band, number and frequency; picking it makes that channel the target.
static void rxReportChannel(uint8_t channel, float dbm) {
    link::MsgStation s{};
    s.mac[5] = channel + 1;
    s.channel = channel + 1;
    s.rssi = (int8_t)lroundf(dbm);
    s.isAp = 1;
    snprintf(s.ssid, sizeof(s.ssid), "%c%d  %u MHz", kRxBand[channel / 8], channel % 8 + 1, kRxFreq[channel]);
    noteStation(s);
}
