# EXTRACTS: what an Espressif chip can measure beyond RSSI

Retrieved 2026-11-11. Every quote below is verbatim from the local file named. HTML pages were saved as `.html` and dumped to `.txt` with w3m; PDFs were converted with `pdftotext -layout`. GitHub files are from the default branch (`master`/`main`) on 2026-11-11, so they may change.

Evidence tags: [V] = read at source (file in this folder). [S] = search snippet only, no file.

---

## 1. ESP-SDR (ESPARGOS): raw I/Q capture from the ESP32's own receiver [V]

The "new ESP SDR" the user asked about. It is **community firmware, not an Espressif feature**.

- Source: https://raw.githubusercontent.com/ESPARGOS/esp-sdr/main/README.md -> `esp-sdr_README.md`
  - "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver and sends them to your computer over USB or UART. No extra SDR hardware is needed."
  - "With the help of LLMs, we found an undocumented debug path that lets the CPU read those samples instead." / "Parts of the firmware are AI-generated: we understand the capture mechanism well on the ESP32-C61 used in our ESPARGOS One array"
  - Supported-chips table: "| ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 … 4 | also receives 5 GHz |"; "| ESP32-C6 | ✅ | ... | 80, 40, 16 | continuous capture¹ (256 bins) |"; "| ESP32-S3 | ✅ | Serial/JTAG | GPIO43 / GPIO44 | 80, 40, 16 | continuous capture¹ and I/Q over USB |"; "| ESP32-H4 | 🚧 |"
  - "All chips accept tuning from 100 to 6000 MHz, but the PLL only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)."
  - "Snapshots are bursts of up to 16,380 samples ... so there are gaps between them. Gain is not calibrated in dB."
  - "**On-chip spectra** (all chips): the firmware computes 256–2048-bin FFTs and sends compact spectra instead of raw samples."
  - "**Continuous I/Q on the ESP32-S3**: the second core filters and decimates the 16 MS/s stream to 15.625–250 kS/s, sent gap-free over native USB."
  - "**ESP32-S31 streaming** (separate `esp32s31-stream` firmware, experimental): continuous 8-bit I/Q at up to 20 MS/s over high-speed USB or 40 MS/s over Gigabit Ethernet"
  - "ESP-SDR is licensed under the GNU General Public License, version 3 or later"
- Source: GitHub API https://api.github.com/repos/ESPARGOS/esp-sdr -> `esp-sdr_repo_api.json`
  - "description":"ESP-SDR uses the undocumented raw I/Q capture functionality of ESP32 family chips to turn them into (low-duty-cycle) Software Defined Radios"; "created_at":"2026-09-28T08:50:16Z"; "pushed_at":"2026-11-09T09:55:06Z"; "stargazers_count":1251
- Source: `docs/how-it-works.md` -> `esp-sdr_docs_how-it-works.md`
  - "Espressif doesn't document any of this. Everything below comes from reading the RF test library that ships with ESP-IDF (`librftest.a`, function `adctrig`), from disassembly, and from trying things on real boards."
- Source: `docs/rx-controls.md` -> `esp-sdr_docs_rx-controls.md`
  - "Hardware AGC is the default; manual gain indices are not absolute gain in dB."
  - "with a test tone a few centimetres from the antenna, every Wi-Fi chip clipped in AGC mode (peak at full scale), and clipping products buried the tone. Use manual gain for strong signals."
  - Bandwidth table: "| C5 | 11–48 MHz | 6/7, two PHY modes | 6 bits |"
  - Measured reception (section "Measured reception range", one board per chip, October 2026): "| C5 | – | – | – | ✓ | ✓ | – | – | – | ✓ |" (columns 1850 … 2950, 5180–5800 MHz); "✓ means the tone was at least 15 dB above the noise inside the analog filter"
- Source: `docs/spectrum.md` -> `esp-sdr_docs_spectrum.md`
  - "| ESP32-C5 | — | 256–2048 bins; 4/8/10/20/40/80 MS/s |" (no continuous mode on the C5, snapshot FFT only)
  - "| ESP32-S3 | 256–2048 bins; 16/40/80 MS/s; native USB | — |"
- Source: CNX Software, 2026-10-04, https://www.cnx-software.com/2026/10/04/esp-sdr-firmware-turns-esp32-into-a-2-4-5-ghz-software-defined-radio-sdr/ -> `cnx_esp-sdr.txt`
  - "Tuning range – Nominally 2.4 GHz ISM (2.2–2.7 GHz on some chips) and 5 GHz (4.8–6.0 GHz on ESP32-C5)"
  - "USB and UART cannot handle the full data rate, so ESP-WebSDR captures short I/Q snapshots to build the spectrum and waterfall. This means it can miss signals that arrive between capture windows."
  - "Update: ESP-SDR now has experimental transmit support through community projects. The original ESPARGOS firmware remains receive-only."

## 2. Wi-Fi CSI (ESP-IDF, Espressif) [V]

- Source: ESP-IDF latest, ESP32-C5 "Wi-Fi Vendor Features", https://docs.espressif.com/projects/esp-idf/en/latest/esp32c5/api-guides/wifi-driver/wifi-vendor-features.html -> `idf_c5_vendor_features.txt`
  - "In ESP32-C5, this information consists of channel frequency responses of sub-carriers and is estimated when packets are received from the transmitter. Each channel frequency response of sub-carrier is recorded by two bytes of signed characters. The first one is imaginary part and the second one is real part."
  - Sub-carrier table: "802.11n, 40 MHz -58 to +58 -1, 0, 1 117 total, 114 usable"; "802.11ax, 20 MHz (SU) -122 to + 122 -1, 0, 1 245 total, 242 usable"
  - "If first_word_invalid of wifi_csi_info_t is true, it means that the first four bytes of CSI data is invalid due to a hardware limitation in ESP32-C5."
  - "More information like RSSI, noise floor of RF, receiving time and antenna is in the rx_ctrl field."
  - "Because station does not receive any packet when it is disconnected and only receives packets from AP when it is connected, it is suggested to enable sniffer mode to receive more CSI data by calling esp_wifi_set_promiscuous()."
- Source: `idf_s3_vendor_features.txt`, `idf_c6_vendor_features.txt` (same page for S3, C6): same CSI configure section ("it is suggested to enable sniffer mode to receive more CSI data by calling esp_wifi_set_promiscuous()").
- Source: ESP-IDF header `components/esp_wifi/include/local/esp_wifi_types_native.h` -> `idf_esp_wifi_types_native.h`
  - "uint8_t mac[6];            /**< source MAC address of the CSI data */"
  - "signed noise_floor: 8;        /**< noise floor of Radio Frequency Module(RF). unit: dBm*/"
- Source: `components/esp_wifi/include/esp_wifi_he_types.h` -> `idf_esp_wifi_he_types.h`
  - "signed noise_floor: 8;                        /**< the noise floor of the reception frame */"
  - "uint32_t lltf_bit_mode           : 1;   /**< LLTF bit width mode for I/Q components, 0 : 12-bit, 1 : 8-bit, default : 12-bit */"
- Source: ESP32-C5 Wi-Fi overview -> `idf_c5_wifi_overview.txt`: feature list "• Sniffer", "• Multiple antennas", "• Channel state information"; "5 GHz band: Supports 802.11a, 802.11an, 802.11anac, and 802.11anacax."
- Source: https://raw.githubusercontent.com/espressif/esp-csi/master/README.md -> `esp-csi_README.md`
  - "**Full series support:** All ESP32 series support CSI, including ESP32 / ESP32-S2 / ESP32-C3 / ESP32-S3 / ESP32-C5 / ESP32-C6 / ESP32-C61."
  - "[csi_recv_router](./examples/get-started/csi_recv_router) demonstrates using a router as the sender, with the ESP32 triggering the router to send CSI packets via Ping."
  - "[wifi_sensing_demo] demonstrates motion and human presence detection on top of the `esp_wifi_sensing` component"
  - "The effect of external IPEX antenna is better than PCB antenna, PCB antenna has directivity."
- Source: Euchner et al., "ESPARGOS: An Ultra Low-Cost, Realtime-Capable Multi-Antenna WiFi Channel Sounder", arXiv:2502.09405, https://arxiv.org/pdf/2502.09405 -> `arxiv_2502.09405_espargos.pdf/.txt`
  - Sec. I: "Simply using multiple WiFi cards or microcontrollers without taking additional precautions does not produce phase-coherent CSI due to lack of synchronization – data acquired this way would be unusable for many JCaS algorithms, including e.g. angle of arrival (AoA) estimation."
  - Sec. II-A: "By measurement it was determined that, indeed, the initial phase changes after a chip reset and after modifying the LO frequency (WiFi channel), likely every time the PLL has to acquire a new frequency lock."
  - Sec. II: "all microcontrollers are clocked by a daisy-chained 40 MHz reference oscillator, ensuring frequency synchronization."

## 3. Multi-antenna switching (ESP-IDF PHY guide) [V]

- Source: https://docs.espressif.com/projects/esp-idf/en/latest/esp32c5/api-guides/phy.html -> `idf_c5_phy.txt`
  - "controlling external antenna switches through IO pins to select designated antennas, supporting up to 16 antennas."
  - "Despite supporting up to 16 antennas, only a maximum of two antennas can be enabled simultaneously for sending and receiving data."

## 4. Wi-Fi FTM (802.11mc) [V]

- Source: ESP-IDF `components/soc/<chip>/include/soc/soc_caps.h` (master) -> `soc_caps_esp32{s2,s3,c3,c5,c6,c61,s31}.h`
  - Each contains: "#define SOC_WIFI_FTM_SUPPORT                (1)    /*!< Support FTM */"
  - `soc_caps_esp32c5.h`: "#define SOC_WIFI_SUPPORT_5G                 (1)    /*!< Support 5G */"
- Source: https://raw.githubusercontent.com/espressif/esp-idf/master/examples/wifi/ftm/README.md -> `idf_example_wifi_ftm_README.md`
  - "| Supported Targets | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-S2 | ESP32-S3 | ESP32-S31 |"
  - "Currently FTM is only supported in below configuration - 1. Station as Initiator and SoftAP as Responder on supported ESP devices 2. Station as Initiator and an external AP that supports FTM in Responder mode"
  - "If external FTM Initiators get a large error in distance readings with the SoftAP, note down the reading at zero distance in centimeters, say `cm0`."
- Source: ESP-IDF v5.5 ESP32-S3 Wi-Fi guide, https://docs.espressif.com/projects/esp-idf/en/release-v5.5/esp32s3/api-guides/wifi.html -> `idf_v55_s3_wifi.txt`, section "Wi-Fi Location"
  - "ESP32-S3 supports FTM in below configuration: • ESP32-S3 as FTM Initiator in station mode. • ESP32-S3 as FTM Responder in AP mode."
  - (No accuracy figure is stated in this Espressif section.)
- Datasheets: `ds_esp32-c5.txt` p.3 "– 802.11mc FTM"; `ds_esp32-c6.txt`, `ds_esp32-c61.txt`, `ds_esp32-s3.txt`, `ds_esp32-s31.txt` each list "802.11mc FTM".
- Source: Singh et al., "Benchmarking and Security Considerations of Wi-Fi FTM for Ranging in IoT Devices", arXiv:2303.03766, https://arxiv.org/pdf/2303.03766 -> `arxiv_2303.03766_ftm.pdf/.txt`
  - Abstract: "while Wi-Fi FTM supports localization accuracy to within one to two meters in ideal conditions during outdoor line-of-sight experiments, for indoor environments at short ranges similar accuracy was only achievable on chipsets supporting Wi-Fi FTM on wider (VHT80) channel bandwidths rather than narrower (HT20) channel bandwidths."
  - Sec. 3 (results): "however Wi-Fi FTM ranging is only supported on HT20¹" (ESP32-S2; the "1" is a footnote marker in the PDF) ... "at short distances indoors (Figure 3c) it performs exceptionally poorly – with an error of ≈1m at a distance of 0.5m, and an error of 2-3m at a true distance of 1.0m and 1.5m."

## 5. IEEE 802.15.4 (Zigbee/Thread) radio APIs [V]

- Source: https://raw.githubusercontent.com/espressif/esp-idf/master/components/ieee802154/include/esp_ieee802154.h -> `idf_esp_ieee802154.h`
  - "esp_err_t esp_ieee802154_set_promiscuous(bool enable);"
  - "@brief  Perform energy detection. @param[in]  duration  The duration of energy detection, in symbol unit (16 us)."
  - "extern void esp_ieee802154_energy_detect_done(int8_t power);" with "@param[in]  power  The detected power level, in dBm."
  - "Please note that the FCS field is replaced by RSSI and LQI value of the received frame."
  - "int8_t esp_ieee802154_get_recent_rssi(void);" / "uint8_t esp_ieee802154_get_recent_lqi(void);"
- Source: `examples/ieee802154/ieee802154_cli/README.md` -> `idf_example_ieee802154_cli_README.md`
  - "| Supported Targets | ESP32-C5 | ESP32-C6 | ESP32-H2 | ESP32-H21 | ESP32-H4 | ESP32-S31 |"
  - "> ed -d 2 ... I (668548) i154cmd: ed_scan_rss_value: -98 dB"
  - "promisc [-edg] ... e: Enable the promiscuous mode."
- Datasheet `ds_esp32-c5.txt` p.4: "IEEE 802.15.4 • Compliant with IEEE 802.15.4-2015 protocol • OQPSK PHY in 2.4 GHz band • Data rate: 250 Kbps • Thread 1.4 • Zigbee 3.0"
- `soc_caps_esp32c5.h` / `soc_caps_esp32c6.h`: "#define SOC_IEEE802154_SUPPORTED        1"; `soc_caps_esp32c61.h` has no SOC_IEEE802154 line.

## 6. Bluetooth LE: coded PHY, direction finding, Channel Sounding [V]

- Source: ESP-IDF latest "Major Feature Support Status" per chip, https://docs.espressif.com/projects/esp-idf/en/latest/<chip>/api-guides/ble/ble-feature-support-status.html -> `idf_<chip>_ble_feature_status.txt`
  - ESP32-C5: "LE Long Range (Coded PHY S=2/S=8) supported supported supported"; "LE Advertising Extensions supported ..."; "5.1 Angle of Arrival (AoA)/Angle of Departure (AoD) supported supported supported"; "6.0 Channel Sounding unsupported unsupported unsupported"
  - ESP32-C6: "5.1 Angle of Arrival (AoA)/Angle of Departure (AoD) unsupported unsupported unsupported"
  - ESP32-S3: "5.1 Angle of Arrival (AoA)/Angle of Departure (AoD) unsupported unsupported unsupported"
  - ESP32-C61, ESP32-H2, ESP32-H4, ESP32-S31: AoA/AoD "supported"; all seven chips: "Channel Sounding unsupported"
- `soc_caps_esp32c5.h`: "#define SOC_BLE_CTE_SUPPORTED               (1)    /*!< Support Bluetooth LE Constant Tone Extension (CTE) */" (also in c61, h2, h4, s31; absent in c6, s3)
- Datasheet `ds_esp32-c5.txt` p.4: "• Bluetooth LE: Bluetooth Core 6.0 certified", "• Direction finding (AoA/AoD)", "• Speed: 125 Kbps, 500 Kbps, 1 Mbps, 2 Mbps"; p.6: "Up to -106 dBm of sensitivity for Bluetooth LE receiver (125 Kbps)"

## 7. "Spectrum analyser" style APIs [V]

- Espressif official: no raw-spectrum API was found in the downloaded docs. What exists is per-frame `noise_floor` in `rx_ctrl` (see 2), 802.15.4 energy detect in dBm (see 5), and the PHY certification-test console:
- Source: `examples/phy/cert_test/README.md` -> `idf_example_phy_cert_test_README.md`
  - "| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-S2 | ESP32-S3 |"
  - "phy> esp_rx -n 1 -r 0 ... I (58800) phy: rx_num: 166 rx_rssi: -527" (packet-counting RX test, not a spectrum)
- Unofficial raw-spectrum path: ESP-SDR (section 1).

## 8. ESP32-C5 radio specs and revisions [V]

- Source: ESP32-C5 Series Datasheet v1.5, https://www.espressif.com/sites/default/files/documentation/esp32-c5_datasheet_en.pdf -> `ds_esp32-c5.pdf/.txt`
  - p.3: "• 1T1R in 2.4 and 5 GHz dual band • Operating frequency: 2412 ~ 2484 MHz, 5180 ~ 5885 MHz"; "IEEE 802.11ax-compliant – 20 MHz only"; "– Antenna diversity"
  - Table 6-10 "5 GHz RX Sensitivity": "802.11a, 6 Mbps, OFDM — –94.0 —"
  - Table 1-1: "ESP32-C5HR8 ... v1.0/v1.2"; "ESP32-C5HR2 ... v1.2"; Sec 1.3: "ESP32-C5 now has multiple chip revisions available on the market using the same part number."

## 9. New parts 2025–2026 [V]

- ESP32-S31 — Espressif news, 2026-07-27, https://www.espressif.com/en/news/ESP32_S31_Mass_Production -> `espressif_news_S31_mass_production.txt`
  - "ESP32-S31 Now in Mass Production and Available for Purchase"; "ESP32-S31 integrates Wi-Fi 6 (2.4 GHz), Bluetooth 5.4 (including LE Audio and Classic BR/EDR), IEEE 802.15.4 (Zigbee and Thread), and a Gigabit Ethernet MAC."; "ESP32-S31 is now available from the Espressif Official AliExpress Store."
  - Datasheet `ds_esp32-s31.txt`: "Datasheet Pre-release v0.5"; "• Operating frequency: 2412 ~ 2484 MHz"; "• Direction Finding (AoA/AoD)"
- ESP32-E22 — Espressif news, 2026-01-19, https://www.espressif.com/en/news/ESP32_E22_Announcement -> `espressif_news_E22.txt`
  - "It supports Wi-Fi 6E across the 2.4 GHz, 5 GHz, and 6 GHz bands, combining 160 MHz channel bandwidth, 2×2 MU-MIMO, Beamforming"
  - "As a Radio Co-Processor (RCP) ... pair ESP32-E22 with Espressif's own SoCs or third-party processors through high-speed interfaces such as PCIe 2.1, and SDIO 3.0"
  - "Engineering samples of ESP32-E22 are now available. For inquiries, please contact Espressif's customer support team."
- ESP32-H4 — Espressif news, 2026-03-27, https://www.espressif.com/en/news/ESP32_H4_Sample -> `espressif_news_H4_sample.txt`
  - "Samples are now available upon request"; "ESP32-H4 fully supports all features defined in the Bluetooth 5.4 (LE) Core Specification and has passed Bluetooth 6.0 certification"
- ESP32-C61 — datasheet `ds_esp32-c61.txt`: "2.4 GHz Wi-Fi 6 (IEEE 802.11ax)"; "• Direction finding (AoA/AoD)"; "– 802.11mc FTM"

## 10. Arduino support [V]

- Source: https://raw.githubusercontent.com/espressif/arduino-esp32/master/README.md -> `arduino-esp32_README.md`
  - "| ESP32-C5 |     Yes    |       Yes       |"; "| ESP32-C6 |     Yes    |       Yes       |"
  - "ESP32-C2 and ESP32-C61 are also supported by Arduino-ESP32 but require using Arduino as an ESP-IDF component or rebuilding the static libraries."

## 11. Prices (Botland, PLN gross, read from the page's schema.org data on 2026-11-11) [V]

| Board | Price | Stock | URL | File |
|---|---|---|---|---|
| Seeed XIAO ESP32-C6 | 29.69 | InStock | https://botland.com.pl/xiao/24783-seeed-xiao-esp32-c6-wifibluetooth-seeedstudio-113991254-5904422385705.html | botland_xiao_c6.html |
| Seeed XIAO ESP32-C5 | 30.90 | InStock | https://botland.com.pl/xiao/28890-seeed-xiao-esp32-c5-wifibluetoothzigbeethreadmatter-seeedstudio-100010048-5902186335752.html | botland_xiao_c5.html |
| M5Stack NanoH2 (ESP32-H2) | 34.90 | InStock | https://botland.com.pl/kontrolery-m5stack/28457-nanoh2-dev-kit-esp32-h2-zestaw-deweloperski-m5stack-c149-6972934171962.html | botland_nanoh2.html |
| Seeed XIAO ESP32-S3 | 37.90 | InStock | https://botland.com.pl/xiao/22878-seeed-xiao-esp32-s3-wifibluetooth-seeedstudio-113991114.html | botland_xiao_s3.html |
| ESP32-C6-DevKitM-1 N4 | 65.90 | InStock | https://botland.com.pl/moduly-esp32/24607-...-5904422385651.html | botland_c6_devkitm.html |
| ESP32-H2-DevKitM-1 N4 | 83.90 | InStock | https://botland.com.pl/moduly-bluetooth/23718-...-espressif-systems.html | botland_h2_devkitm.html |

Quoted page data: `"price":"30.90"`, `"priceCurrency":"PLN"`, `"availability":"https://schema.org/InStock"` (XIAO C5), and the same pattern for the others.

---

## Could not retrieve / snippet only

- ESP32-C61-DevKitC-1 N8R2 at Kamami: https://kamami.pl/en/esp32/1206207-esp32-c61-devkitc-1-n8r2-development-board-with-esp32-c61-wroom-1-module-5902186338098.html returned HTTP 403. Search snippet says "No product available!" [S]. No Botland listing for a C61 dev board turned up in a site search (only an M5Stack CardKB2 keyboard with a C61 inside).
- ESP32-S31 boards: no Polish shop listing found. Snippets mention an ESP-Mosaico kit at US$59 (pre-order) and a Korvo-1 on backorder at Mouser [S]. Unverified.
- ESP32-H4 datasheet PDF: the URL `esp32-h4_datasheet_en.pdf` returned an HTML page, not a PDF.
- ESP32-E22 datasheet: not published at the guessed URL (HTML returned).
- ESP32-C5 errata (chip-revision fixes): the PDF URL and two guessed HTML paths did not return content.
- Zubow et al. 2023, "Towards FTM...", https://bits.informatik.hu-berlin.de/~zubow/zubow2023towards-ftm.pdf: download failed.
- ESP-SDR on Zephyr (experimental TX on the ESP32-S3, v0.1.1, 2026-10-11): snippet only (esp32.co.uk) [S].
- esp-sdr-bridge (z2labs) and SoapyESPSDR repos: not opened; only named in the ESP-SDR README.
- No Espressif-published FTM accuracy figure was found; the accuracy numbers above come from the third-party arXiv benchmark (ESP32-S2, HT20).
