# Research report: esp-radio-sensing (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

## 1. Verdict table

| Option | What it adds | Cheapest verified price in Poland | Maturity (ESP32/Arduino hobby build) | Evidence |
|---|---|---|---|---|
| **ESP-SDR firmware (the "new ESP SDR")**: raw I/Q from the ESP32's own receiver | Real spectrum and waterfall with 256–2048-bin on-chip FFT. Up to 80 MS/s in snapshots. Tunes ~2.2–2.65 GHz and 5180–5800 MHz on the C5. Works with no Wi-Fi frame present. | 0 PLN on the planned XIAO ESP32-C5 (30.90 PLN, Botland, in stock) or on the S3 you already own | Works today with public code, but it is ESP-IDF firmware, not Arduino. Community project, partly AI-generated, uses an undocumented hardware path. Gain is not in dB. | [V] |
| Wi-Fi CSI (C5 / C6 / S3) | Amplitude and phase on each subcarrier, per received frame, tagged with the source MAC. Up to 242 usable subcarriers (HE20); the C5 also does 5 GHz. | 0 PLN (built into the C5) | Works today (esp-csi examples, ESP-IDF API). Phase from a single chip is not stable, so use amplitude only. | [V] |
| Per-frame noise floor + RSSI | Noise floor in dBm with every received frame | 0 PLN | Works today | [V] |
| 802.15.4 energy detect, promiscuous mode, RSSI/LQI (C5, C6, H2) | Zigbee/Thread channel power in dBm without decoding, plus per-packet RSSI and LQI | 0 PLN on the C5 (C6: 29.69 PLN) | Works today (ESP-IDF `ieee802154_cli`). Arduino needs the IDF API. | [V] |
| BLE 5 coded PHY (125 kbps, −106 dBm) + extended advertising | Longer-range BLE target detection | 0 PLN on the C5 | Works today | [V] |
| BLE AoA/AoD (CTE) on C5, C61, H2, H4, S31 | Direction finding from IQ samples, but it needs a switched antenna array and a tag that sends CTE | 0 PLN for the chip; the antenna array is extra | Needs significant work. Not on the C6 or S3. | [V] |
| Wi-Fi FTM ranging (S2, S3, C3, C5, C6, C61, S31) | Distance by round-trip time, but only to a cooperating FTM responder | 0 PLN, plus a second ESP as responder (~30 PLN) | Works today (IDF example). Indoors at short range it is poor: errors of 1–3 m. | [V] |
| Antenna-switch control (up to 16 antennas, 2 active) | Electronic switching between antennas alongside the mechanical pan | Cost of an RF switch (not priced) | Needs significant work | [V] |
| Bluetooth Channel Sounding | Not available on any Espressif chip | — | Unsupported | [V] |
| ESP32-S31 | Continuous I/Q streaming to Gqrx/GNU Radio (20 MS/s USB, 40 MS/s Ethernet) plus BLE direction finding | No Polish listing found | Research-grade; datasheet still "Pre-release v0.5" | [V] chip / [S] boards |
| ESP32-C61 | Wi-Fi 6 + BLE direction finding, the ESPARGOS reference chip | Kamami page "No product available" | Arduino needs a rebuild | [S] |
| ESP32-E22 (tri-band Wi-Fi 6E), ESP32-H4 | 6 GHz band (E22), BLE 5.4 (H4) | Engineering samples / samples on request only | Not buyable | [V] |

## 2. Key facts
1. **ESP-SDR supports the C5 on 5 GHz.** The README's chip table says "80 … 4 | also receives 5 GHz". The repo description calls the tool "(low-duty-cycle) Software Defined Radios". The rx-controls doc says "manual gain indices are not absolute gain in dB", and in AGC mode every chip clipped on a strong continuous tone, so use manual gain. The C5 only does snapshot FFTs; continuous capture exists on the C6, C61, S3 and S31. Sources: `esp-sdr_README.md` (Supported chips), `esp-sdr_docs_rx-controls.md`, `esp-sdr_docs_spectrum.md`.
2. **CSI contents and sniffer use.** Each subcarrier is stored as two signed bytes (imaginary, real). Each record carries the source MAC. Espressif suggests enabling `esp_wifi_set_promiscuous()` to get more CSI. Sources: `idf_c5_vendor_features.txt` (Wi-Fi Channel State Information), `idf_esp_wifi_types_native.h` (`wifi_csi_info_t`).
3. **Single-chip CSI phase is unreliable.** ESPARGOS measured that "the initial phase changes after a chip reset and after modifying the LO frequency". Phase-coherent arrays need a shared clock plus a phase reference signal. Source: `arxiv_2502.09405_espargos.txt` §II-A.
4. **BLE direction finding vs Channel Sounding.** Espressif's support tables mark AoA/AoD "supported" on the C5, C61, H2, H4 and S31, and "unsupported" on the C6 and S3. Channel Sounding is "unsupported" on every chip checked. Source: `idf_*_ble_feature_status.txt`.
5. **FTM needs a cooperating responder** ("Station as Initiator and SoftAP as Responder … or an external AP that supports FTM in Responder mode"). On the ESP32-S2 at HT20, indoor error was "≈1m at a distance of 0.5m, and an error of 2-3m at … 1.0m and 1.5m". Sources: `idf_example_wifi_ftm_README.md`, `arxiv_2303.03766_ftm.txt` §3.
6. **802.15.4 energy detect reports in dBm.** The callback is `esp_ieee802154_energy_detect_done(int8_t power)` and the duration is set in 16 µs symbols. Source: `idf_esp_ieee802154.h`.

## 3. Recommendation
Keep the XIAO ESP32-C5 (30.90 PLN) as the only radio. In the cheapest build, use what it already does at no extra cost: RSSI plus noise floor, CSI amplitude per source MAC, 802.15.4 energy detect, and BLE coded-PHY scanning. Offer ESP-SDR as a firmware mode you can reflash to: it turns the same board into a 2.4/5 GHz spectrum mapper that sees non-Wi-Fi emitters, which is the most capability per zloty here. Hold its manual gain fixed during a scan, because its gain is not calibrated in dB. The XIAO S3 you already own can also run ESP-SDR's gap-free I/Q stream for testing. Optional add-ons: a second XIAO C6 (29.69 PLN) as an FTM responder or CSI beacon. Skip CSI phase and AoA, which need coherent multi-receiver hardware. Also skip Channel Sounding (unsupported), and the S31, C61, E22 and H4, which are not buyable in Poland or are samples only.

## 4. Could not retrieve / unverified
- ESP32-C61-DevKitC-1 at Kamami (HTTP 403, snippet only); no C61 dev board found at Botland.
- ESP32-S31 board prices (the US$59 ESP-Mosaico pre-order and Mouser backorder are snippets only).
- ESP32-H4 and ESP32-E22 datasheets (the URLs returned HTML).
- ESP32-C5 errata (revision fixes).
- Zubow 2023 FTM paper (download failed).
- ESP-SDR on Zephyr TX project and the esp-sdr-bridge / SoapyESPSDR repos (snippets only, not opened).
- No accuracy figure for FTM published by Espressif itself.

Files are in `/home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/esp-radio-sensing/`; the quotes behind every claim are in `/home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/esp-radio-sensing/EXTRACTS.md`.
