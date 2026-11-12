# EXTRACTS: 5.8 GHz VRX / palm-sized tracker research (fetched 2026-11-11)

Files sit next to this one. `.html` = raw page, `.txt` = w3m dump, `.md`/`.cpp`/`.h` = raw files. Quotes are verbatim from the
saved file. Tags: [V] = read in a saved file; [S] = search snippet only (no file; no firm claim). Vendor/news statements are
not independent measurements. Downloads were treated as data only; nothing was executed.

---
## Q1. "The new analog VRX ESP" - candidates

### B1. C5VRX (Twotoz) - ESP32-C5 analog 5.8 GHz FPV receiver  [V]  BEST MATCH
- Repo: https://github.com/Twotoz/C5VRX ; files B_c5vrx_README.md, B_c5vrx_P64.md, B_c5vrx_FINDINGS.md, B_c5vrx_LICENSE, B_c5vrx_github_api.json, B_c5vrx_githubpage.html
- GitHub API: `"created_at": "2026-08-30T11:52:11Z"`, `"pushed_at": "2026-11-10T23:29:42Z"`, `"stargazers_count": 532`, licence spdx GPL-3.0. (rtl-sdr.com says "first uploaded to GitHub on August 13" - dates disagree.)
- README: "C5VRX-5 receives analog 5.8 GHz FPV video with the ESP32-C5's own radio and outputs composite PAL/NTSC through a passive 6-bit resistor DAC: automatic gain control, a quick baseline boot with manual calibration, an on-screen menu, and browser-based flashing and controls."
- "The demodulator is **U80P64-R1** ... It has one positive NTSC check; PAL, weak-signal behaviour and range still need hardware validation."
- "A Seeed Studio XIAO ESP32-C5 and seven resistors; no extra RF parts"
- "> **C5VRX is an experimental FPV receiver. Bugs, signal loss, automatic receive-chain changes or incompatibility with your camera/goggles can cause sudden loss of video or sync ... Loss of FPV video can lead to a crash, property damage or serious injury.**"
- "Do not rely on C5VRX as your only means of maintaining safe control of an aircraft."
- Menu: "BAND, CHANNEL, SCAN, VIDEO (AUTO/NTSC/PAL), FILTER (AUTO/XNARROW/NARROW/NORMAL/WIDE) ... GAIN (LEVEL/KEEL/RSSI/MAX/fixed)"
- "IQ routing is internal (no wiring) and uses GPIO27 (the user LED, which may glow) and GPIO2."
- Licence: "C5VRX-5 is licensed under **GPL-3.0-only**"; "builds on ... ESPARGOS esp-sdr (GPL-3.0) for the C5 RX filter control."
- Mechanism (README of Q2 below + FINDINGS): FINDINGS.md: "the picture goes at about -85 dBm while the receiver noise reads -95 dBm in 12 MHz"; "**Nothing here was flashed or measured on a board.**" (that section is host-only work dated 2026-11-10); "The dBm meter ... reads C/N over the receiver's own noise".
- P64.md: "These are synthetic ADC/goggle models. They do not prove physical picture, chroma, timing or range gains."
- It is a standalone firmware (own demodulator in BitScrambler), not an ESP-SDR application; it only borrows ESP-SDR's C5 filter control.
- Price: XIAO ESP32-C5 board "Seeed ... [View on Amazon]"; README gives no PLN price. Seeed wiki: "As small as a thumb(21x17.8mm)".

### B2. CircuitDigest news on C5VRX - A_circuitdigest_c5vrx.html/.txt  [V]
- URL: https://circuitdigest.com/news/seven-resistors-and-an-esp32-c5-this-open-source-fpv-receiver-uses-the-wi-fi-radio-to-catch-analog-drone-video ; datePublished 2026-10-23.
- "the firmware taps the radio's diagnostic sample path (MODEM_DIAG), takes selected bits from the radio's ADC at 40 MS/s, and runs FM demodulation in the chip's BitScrambler peripheral, so the CPU is not in the sample path at all."
- "Band: 5.8 GHz analog FPV, 48 channels, with a scan mode that picks the strongest centred signal"; "Output: composite PAL/NTSC from a 6-bit resistor DAC, adjustable output level (0.5x to 5x)"; "Licence: GPL-3.0"
- "The maker is clear that this is experimental firmware. Video can drop out without warning, so it should not be your only way to keep control of a drone."

### B3. rtl-sdr.com, "Various Projects Independently Find Hidden SDR Capabilities in ESP32" - A_rtlsdr_esp32_sdr.html/.txt  [V]
- URL: https://www.rtl-sdr.com/various-projects-independently-find-hidden/ (published about 2026-10-01).
- "C5VRX, which was first uploaded to GitHub on August 13. C5VRX uses an ESP32-C5 as a 5.8 GHz real-time FPV video receiver. Although this project appears to use a different mechanism, the result is similar ... The project is still a work in progress and doesn't yet work reliably at range."
- "the SDR will only work as a spectrum analyzer, and demodulating or decoding continuous radio data is not possible with just an ESP32. The exception is the new ESP32-S31" (this statement about ESP-SDR predates ESPsoup/C5VRX-style onboard demodulation).

### B4. ESPsoup (Peter Holzhauser, "711IT") - A_espsoup_site.html/.txt, A_rtlsdr_espsoup.html/.txt  [V]  SECOND CANDIDATE, covers both scanning and analog video
- URLs: https://espsoup.com/ ; https://www.rtl-sdr.com/espsoup-turn-an-esp32-c5-into-a-2-4-5-ghz-pocket-scanner-with-a-connected-phone-or-pc/ (2026-10-06); repos github.com/pit711/ESPsoup , github.com/pit711/espsoup-firmware (linked from site, not fetched).
- "ESPsoup firmware 0.7.1 (open source, GPL-3.0, based on ESP-SDR by ESPARGOS), installed by the app"; "App 0.12.15 · ESPsoup firmware 0.7.1 · updated 2026-11-06"; "Price Free web app · tips welcome"; "ESP32-C5 dev board (about 15-25 EUR) on its native USB port".
- "Tools -> TV turns the ESP32 into an analog video receiver. Pick a channel from Raceband, Fatshark, Boscam A, B and E, Lowband or the 2.4 GHz AV channels, or type any frequency."
- "In our test with a lab signal generator all 52 receivable channels (5362-5945 MHz and 2414-2468 MHz) showed a picture, at 24-28 fps and about 7,900 lines per second; two of them needed a second try. The ESP32 demodulates the video itself. The picture is black and white, with optional coarse colour (PAL/NTSC)" (vendor test with a signal generator, not a flight test).
- Table: "Analog FPV video, live ~25 fps | 5.36-5.95 GHz | works | Black and white, optional coarse colour (PAL/NTSC)."; "Find (hot/cold) with GPS heatmap | any receivable frequency | works | Usable over about 25-30 dB; the heatmap needs location access."; "Panorama live ... About 15 sweeps/s over 2.4 GHz".
- "up to eight ESP32-C5s have been tested to work together on a single USB hub".
- Output goes to a phone/PC screen over USB, not to goggles (no composite out is mentioned).

### B5. ExpressLRS VRX Backpack - E_elrs_vrx_backpack.html/.txt  [V]
- URL: https://www.expresslrs.org/hardware/backpack/esp-backpack/
- "A Backpack is an add-on device that facilitates wireless communication between an ExpressLRS module and another device (e.g. a Video Receiver on your goggles) using the ESPnow protocol."
- "For the VRX Backpack, you can reuse any ESP-based ExpressLRS receiver ... or for a complete DIY route, you'll need an ESP-01F module." "An off-the-shelf VRX Backpack has also appeared from Happymodel: the EP82"
- Supported VRX list includes "ImmersionRC Rapidfire", "SkyZone SteadyView", "TBS Fusion", "Generic RX5808 Module (some)", "FENIX Module", "HDZero VRX4". It only changes channel/band; it carries no video.

### B6. PhobosLT (ESP32 + RX5808 lap timer) - E_phobos_README.md  [V]
- URL: https://github.com/phobos-/PhobosLT ; licence badge "License: MIT".
- "An RX5808 VRx module with SPI mod"; RSSI on ESP32 pin 33; "Please note that +5v pin on the RX5808 should be connected to a 3v3 source to undervolt the RX5808 to get a better RSSI resolution and to help with cooling"
- "RSSI is transmitted over a websocket to draw the RSSI graph in real time." RSSI only, no video.

### B7. FENIX rx5808-pro-diversity firmware - D_fenix_README.md  [V]
- URL: https://github.com/JyeSmith/FENIX-rx5808-pro-diversity ; "The code is distrubuted under the [MIT license]"; "2 and 4 Antenna Diversity - Supports Quadversity."; "Search Mode - Search channels based on RSSI."; "Finder Mode - Visual and audible indication of RSSI." Runs on STM32/Arduino-class MCU (not ESP). Forked from sheaivey/rx5808-pro-diversity (D_sheaivey_README.md: "The code is distrubuted under the [MIT license]").

### B8. Commercial ESP-based analog VRX module (Skyzone, Foxeer, RushFPV, HGLRC, SpeedyBee, BetaFPV, Happymodel, AKK, TBS, Steadyview, Wolf, OpenVRX)
- Two searches (standard + extended) returned no such product. The only ESP-chip "VRX" product found is the Happymodel EP82 VRX Backpack (control only, B5). Result: NONE FOUND. [S] only. RotorHazard/Chorus/OpenLap/Rapidfire not opened except as listed above.

---
## Q2. Can an ESP32-C5 running ESP-SDR demodulate analog FPV video?

### A1. ESP-SDR README - A_espsdr_readme.md  [V]  (https://github.com/ESPARGOS/esp-sdr, raw README)
- "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver and sends them to your computer over USB or UART."
- Table row: "| ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 ... 4 | also receives 5 GHz |" (no "continuous capture" footnote on C5; the footnote ¹ marks C6, C61, S3, S31).
- "Continuous capture means the chip records the signal without gaps while it computes spectra, over native USB only. It can't FFT all of it".
- "All chips accept tuning from 100 to 6000 MHz, but the PLL only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)."
- "Snapshots are bursts of up to 16,380 samples (8,190 on the C2 and 12,284 on the S2), so there are gaps between them. Gain is not calibrated in dB."
- "**ESP32-S31 streaming** ... continuous 8-bit I/Q at up to 20 MS/s over high-speed USB or 40 MS/s over Gigabit Ethernet"; "For continuous streaming into Gqrx ... use an ESP32-S31 with SoapyESPSDR, or an ESP32-S3 with esp-sdr-bridge".
- "Parts of the firmware are AI-generated"; GPL-3.0 per CNX (A_cnx_esp_sdr).

### A2. ESP-SDR rx-controls.md - A_espsdr_rxcontrols.md  [V]
- Bandwidth table: "| C5 | 11-48 MHz | 6/7, two PHY modes | 6 bits |"; "C5 uses PHY mode 0 for 11-23 MHz and mode 1 for 24-48 MHz or open." ("approximate receive-path noise widths").
- An analog FPV channel is about 18-20 MHz wide is the owner's figure; not quoted from a source here.

### A3. ESP-SDR spectrum.md - A_espsdr_spectrum.md  [V]
- "| ESP32-C5 | - | 256-2048 bins; 4/8/10/20/40/80 MS/s |" (continuous column is "-" for C5).
- "Snapshot FFT stops reception between captures, and the viewer marks these gaps."

### A4. ESP-SDR how-it-works.md - A_espsdr_howitworks.md  [V]
- "Espressif doesn't document any of this." ... "Every supported chip contains a small debug block, which we call the **dump engine** ... copies baseband samples from the receiver into a block of ordinary on-chip SRAM".

### A5. CNX Software 2026-10-04 - A_cnx_esp_sdr.html/.txt  [V]
- "USB and UART cannot handle the full data rate, so ESP-WebSDR captures short I/Q snapshots to build the spectrum and waterfall. This means it can miss signals that arrive between capture windows."
- "Tuning range - Nominally 2.4 GHz ISM (2.2-2.7 GHz on some chips) and 5 GHz (4.8-6.0 GHz on ESP32-C5)".

Conclusion backed by the above: stock ESP-SDR on the C5 is snapshot-only (gaps), so it cannot demodulate continuous FM video by itself. Analog video demodulation on the C5 IS demonstrated by two separate firmwares that go beyond stock ESP-SDR: C5VRX (B1, hardware-validated only for one NTSC check per its own README; range unreliable per B3) and ESPsoup (B4, lab signal-generator test, display on phone/PC). No independent flight or range measurement was found.

### I1. ESP32-C5 datasheet v1.5 - I_esp32c5_datasheet.pdf/.txt  [V]
- "Operating frequency: 2412 ~ 2484 MHz, 5180 ~ 5885 MHz" (the normal Wi-Fi range; ESP-SDR tunes beyond it).
- Table 5-8: "802.11a/n, HT20 | RX ... 110" mA peak; "802.11n, HT40 ... 113"; 5 GHz TX "802.11a, 6 Mbps, OFDM @ 18 dBm ... 408".
### I2. Seeed XIAO ESP32-C5 wiki - I_seeed_xiao_c5_wiki.html/.txt  [V]
- "Ultra small size: As small as a thumb(21x17.8mm)"; "Better RF performance: External RF antenna included."; "Battery charging chip: Supports lithium battery charge and discharge management."; 8 MB PSRAM / 8 MB Flash variant listed.

---
## Q3. RX5808 / RTC6715

### D1. WREKD RX5808 listing - D_wrekd_rx5808.html/.txt  [V]
- https://tuah.wrekd.com/products/rx5808 : "Receiving Frequency: 5705-5945MHZ, 8 channel"; "Receiving Sensitivity: -90dBm"; "SPI Mod: Yes"; "Frequency Control: built-in frequency phase-locked loop"; "AV Output: Direct output analog audio and video signals"; "Supply Voltage: 5V+"; "Supply Current: ~170mA"; "Dimensions: 28 * 23 * 3mm"; "Weight: 3.6g"; JSON `"price":{"amount":"17.99"` (USD; the search snippet said 12.99 - page JSON says 17.99; sold as removed-from-equipment units).
### D2. Rotorama RX5808 (CZ) - D_rotorama_rx5808.html/.txt  [V]
- https://www.rotorama.com/product/rx5808-prijimac-modul : "Discontinued"; "EUR 7,49"; "Input voltage: 5V"; "Control: SPI (CH1 - DATA, CH2 - SEL, CH3 - CLK)"; "Video output / Audio output / RSSI output"; "The receiving module also has an RSSI output that indicates the strength of the received signal."
### D3. SPI mod - D_rotorhazard_hw.md, D_sheaivey_spimod.html  [V]
- RotorHazard: "RotorHazard requires RX5808 modules to have SPI communication enabled in order to change channels." "Remove the shield from the RX5808 ... Remove the following resistor: ..." (image only).
- sheaivey: "In order to get the rx5808 to use SPI you will need to open it and remove a single SMD resistor."
### D4. FENIX source - D_fenix_channels.cpp, D_fenix_receiver_spi.cpp, D_fenix_receiver.h  [V]
- Channel table (MHz): "5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // A"; "5733 ... 5866, // B"; "5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // E"; "5740 ... 5880, // F / Airwave"; "5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917, // R / Immersion Raceband"; "5362 ... 5621, // L"; further sets "// U", "// O", "// H" (5325-5933). 
- SPI: "Format is LSB first, with the following bits in order: 4 bits - address / 1 bit - read/write enable / 20 bits - data"; "F_lo = 2 * (N * 32 + A) * (F_osc / R) where: F_osc = 8 Mhz R = 8"; "Refer to RTC6715 datasheet for further details."
- RSSI per-module calibration (D_sheaivey_README.md): "No two modules have the same RSSI min and max readings."
### NOT RETRIEVED for Q3: the RX5808/RTC6715 datasheet itself. mikrocontroller.net "RX5808-Spec-V1.pdf", electronicsdatasheets.com, datasheetspdf.com, ozdisan, szlcsc (wrong chip) all returned HTML/errors. Therefore NO primary figure for: RSSI voltage range, RSSI response/settling time, video level, audio, supply range. Only vendor lines above. Polish shop prices NOT found: Botland search "Nie znaleźliśmy produktów dla 'rx5808'"; ht-dron/abc-rc/megadron/rcmaniak search pages are JS shells; Allegro HTTP 403; Kamami/TME not fetched; AliExpress empty. Rotorama (CZ) 7.49 EUR [V], WREKD 17.99 USD [V], search snippets "about 50-60 PLN" are [S] estimates only.

---
## Q4. RSSI-only trackers

### G1. Arduino FR632 RSSI Antenna Tracker (FlyerFpv, 2018) - G_fr632_structables_mirror.html/.txt  [V] (mirror of instructables.com/Arduino-FR632-RSSI-Antenna-Tracker; the instructables page itself served no text)
- "This tracker not use any gps system. This tracker use a diversity video receiver and a arduino pro mini, through the analog inputs arduino read the RSSI sinal percentage from receivers. Sinal its compared and servo follow the stronger RSSI signal. No pairing, no telemetry, no configuration."
- "Only you need adjust the value RSSI_MAX and RSSI_MIN in the arduino code about your receiver"; parts: "Two directional antennas". Licence on page: "Structables Code (AGPLv3)". Method: compare two offset antennas, yaw only.
### G2. Hackaday 2018-05-04 "Super Simple, Super Cheap FPV Drone Tracking" - G_hackaday_2018_simple_tracking.html/.txt  [V]
- "Honestly, we're not sure it would [keep video locked], but we think it's pretty nifty to see [FlyerFpv]'s tracker following his drone around." "Sure, the response could be snappier, and we'd love to see another receiver and servo added to track pitch as well as yaw."
### G3. FPV RSSI Antenna Triversity Tracker (vannoz, Arduino Project Hub 2018-03-04) - G_arduino_triversity_tracker.html/.txt  [V, thin]
- "Three antennas diversity video receiver for FPV users with tracking pan/tilt system." Parts list: Arduino Mega 2560, rx5808. Code is binary download (not read); no performance text on page; licence not stated.
### G4. kwikius/RSSI_Free_Track - G_kwikius_RSSI_Free_Track_README.md  [V, mechanics only]
- "Mechanics for RSSI tracker that can be 3d printed ... The servo is GS3360BB ... The ballrace is 42 mm od ... sliprings". No algorithm text, no licence read.
### G5. Telemetry/GPS trackers (contrast, not RSSI-only)
- u360gts: "released for free under the GPLv3 license"; "Up to 10 Hz telemetry input"; "RSSI signal strength on OLED display." (G_u360gts_README.md [V]). open360tracker: "support for lots of different telemetry protocols" (G_open360_README.md [V]). kiryam/antenna_tracker "MavLink v2 ... LTM" (G_hackaday_io_162972.txt [V]). ArduPilot AntennaTracker: "determines the position of a remote vehicle via its own GPS data and telemetry data" [V via WebFetch only, not saved].
- ImmersionRC EzAntennaTracker: page and manual returned 503/HTML; claims about it (GPS telemetry on an audio sub-carrier, RSSI per antenna displayed) are [S] only.
### Not found: any RSSI-only tracker with measured performance figures (error angle, lock rate, oscillation), and any RSSI tracker built on a single scanning antenna.

---
## Q5. Antennas (additions to papers/antennas/_EXTRACTS_C.md, which was read first)

### H1. Maarten Baert Triple Feed Patch page - H_baert_tfp.html/.txt  [V]
- Size: only indirect. Author's answer on PCB ordering: "PCB Size: "5cm Max * 5cm Max" (part1) / "10cm Max * 10cm Max" (part2)"; reader question: "if I made the bottom PCB 57.5mm in diameter instead of 60mm". Spacing "The correct spacing is 4 mm". ReadyMadeRC says "Weight: 20g (Antenna only)" (from _EXTRACTS_C C3). So a TFP1 is a ~60 mm disc, ~20 g: at the limit of the 20 g budget, wider than a 9 cm head's margin is comfortable.
- "There is a regular single-connector LHCP/RHCP variant as well."
### H2. Polarisation of analog video links
- IntoFPV thread (H_intofpv_28438.html/.txt, 2025-05-17) [V]: "So, LHCP on the vtx with LHCP on the goggles, or RHCP on the vtx with RHCP on the goggles. Don't mix them. LHCP is the default for DJI and walksnail, and RHCP is the default for most (if not all) analog systems." (community post, not a standard).
- Oscar Liang (H_oscarliang_best_fpv_antenna.html/.txt) [V]: "The transmitter and receiver should use matching polarization; otherwise, you may experience significant signal loss." "If you mix LHCP and RHCP antennas, the system may still work to some extent, but the usable range will be greatly reduced."
- Consequence (inference): for analog video buy RHCP (Foxeer Echo 2 RHCP, 8 g, in _EXTRACTS_C C7); for a signal-strength mapper of unknown emitters a circular patch loses ~3 dB to linear emitters, not tested here.
### Helical options: not researched (no source). Baert's index page says "Or use a helical antenna, those are fine too." (H_baert_antennas_index.txt [V]) - one line only.

---
## Q6. "For drone use" - sourced facts only
- (a) Ground tracker: video link polarisation = H2; trackers in G1/G2 are yaw-only, "response could be snappier"; analog loss of video "Loss of FPV video can lead to a crash" (B1 warning) is the reason the experimental C5VRX must not be the only video path.
- (b) Airborne: RX5808 "Weight: 3.6g", "Supply Current: ~170mA" (D1); ESP32-C5 5 GHz RX "110" mA peak (I1); XIAO C5 "21x17.8mm" with battery charger (I2); Echo 2 "Waga: 8g" (_EXTRACTS_C C7). Vibration, quad mass budgets, legal limits: NOT researched, no source. ESPsoup advertises a "GPS-enabled heatmapping tool" ("Find ... GPS heatmap", "Usable over about 25-30 dB") but needs phone/PC and GPS; not a drone payload design.

---
## Could not retrieve / unverified (summary)
- RX5808/RTC6715 primary datasheet (RSSI voltage, response time, supply range, video/audio levels).
- Polish shop prices for RX5808 (Botland no product; others JS/403); Kamami/TME/Allegro/AliExpress not retrievable.
- EzAntennaTracker page/manual (503 / HTML), Instructables original page (empty), arduino triversity code.
- ESPsoup GitHub repos and firmware README not fetched; ESPsoup/C5VRX range/flight performance: only lab/bench claims.
- Any commercial ESP-based analog VRX: none found.
- Helical antennas for 5.8 GHz: no data. Vibration/mass/legal for airborne use: no data.
- Instruction-like text: none encountered in saved pages.
