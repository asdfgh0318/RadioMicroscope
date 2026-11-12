# Research report: prior-art (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

## Verdict
Adopt EasyComm over serial for the head, plus Wigle-CSV export and the SparkFun sweep logic, all free. ESP-SDR is a real option on the ESP32-C5, but its output is uncalibrated and it should stay out of the cheapest build. Nobody has built an ESP32-class "WiFi camera"; the working precedents use a HackRF or an RTL-SDR.

| Option | Capability added | Cheapest verified price (PL) | Maturity | Tag |
|---|---|---|---|---|
| EasyComm (AZ/EL) over serial, as in the SatNOGS rotator firmware; Hamlib rotctl drives it | Any ground-station or tracking software can steer the head | 0 PLN (software) | Works today with public code | [V] |
| Wigle CSV as the map export format | Scan data opens in existing wardriving tools | 0 PLN | Works today | [V] |
| SparkFun-style sweep, 5° steps, keep the best angle | Basic RSSI-vs-direction scan on an ESP | 0 PLN | Works today (ESP8266, 2017) | [V] |
| ESP-SDR on the ESP32-C5 (new, GPL-3.0, repo pushed 2026-11-09) | Raw I/Q and spectrum from the C5's own radio, including 5 GHz, with no extra hardware | 30.90 PLN for the C5 board (price from the brief; not re-checked) | Works today but young: gain is not in dB, data comes in gapped bursts, parts of the code are AI-generated | [V] |
| esp-csi (Apache-2.0) | CSI/RSSI at the C5 (every ESP32 series is listed as supported) | 0 PLN | Works today | [V] |
| PMTiles single-file map archive | Offline map file | 0 PLN | Format is stable; running it from an ESP32 web server was not checked | [V] for the format |
| LeRobot / Feetech STS3215 stack (Apache-2.0) | Confirms the servo model and a 1 Mbaud bus | ~105 PLN per servo (from the brief) | Works today, Python on a PC | [V] |
| RSSI-difference trackers (triversity) | Steering from signal level alone | 0 PLN | Concept only; source is download-only, so I did not read the algorithm | [V] on the concept |
| Ku-band LNB telescope (RTL-SDR + stepper dish) | Sky heatmaps at 0.9° | Not priced | Works, but needs an SDR and a Raspberry Pi | [V] |
| ArduPilot AntennaTracker, u360gts | Steering from GPS and telemetry | Not priced | Works, but irrelevant to mapping signal strength | [V] |

## Key facts (all in papers/prior-art/EXTRACTS.md)
1. **ESP-SDR does cover the C5.** The README table lists "ESP32-C5 | ✅ | ... | also receives 5 GHz" and "ESP32-P4 | ❌ | no radio". The CNX article of 2026-10-04 is the news coverage. Its own reception table has the C5 receiving a test tone at 2200, 2300–2650 and 5180–5800 MHz, one board, October 2026.
2. **It is not a calibrated power meter.** The README says "Gain is not calibrated in dB", gain indices are "PHY table entries, not dB", and snapshots have gaps. A map would show relative strength only. It has a line protocol (`FREQ`, `CAP16`) and `GPIO` control for antenna switches. Sources: ESPARGOS_esp-sdr-README.md, esp-sdr-protocol.md.
3. **Wi-Fi mapping by sweeping a directional antenna is proven.** Thought Emporium's HackRF build says "Each measurement results in a heatmap pixel ... an image is formed" and overlays it on a photo. SparkFun's ESP8266 version swept about 70° x 180° at 5° steps, kept the best RSSI angle, and notes that the best signal can be behind a limited arc. Sources: rtlsdr-wificam-hackrf.txt, rtlsdr-heatmap.txt, sparkfun-2363.txt.
4. **EasyComm is a tiny protocol that existing software already speaks.** The SatNOGS firmware (GPLv3) implements AZ/EL, stop, park and status commands, and its README tests with `rotctl -m 204 -s 19200`. Hamlib sends `AZ%.1f EL%.1f\n`. Sources: satnogs-rotator-fw.md, hamlib-easycomm.c.
5. **Wigle CSV is a documented, simple format.** It has a "WigleWifi-1.6,..." pre-header, then columns MAC, SSID, ..., Channel, Frequency, RSSI, CurrentLatitude, CurrentLongitude. Source: wigle-csv-format.txt. This is a format reference only. It carries GPS positions, not azimuth/elevation, so azimuth/elevation would have to be encoded in or alongside the file.
6. **Open-loop steppers hurt long-term accuracy.** The Ku-band telescope reports "cumulative backlash errors from the open-loop control scheme". This supports the choice of ST3215 servos, which have position feedback. Source: rtlsdr-ku-motorized.txt.

## Recommendation
Build the cheapest version around the C5 in normal Wi-Fi RSSI mode (scan or sniff, per-channel RSSI), with the sweep logic from the SparkFun approach. Expose the head to a PC by implementing EasyComm AZ/EL, so Hamlib and satellite-tracking tools can drive it, and export scans as Wigle-style CSV with azimuth/elevation columns added. Offer ESP-SDR on the C5 as an optional firmware mode. It gives a spectrum view and 5 GHz reception, but it needs a PC and is not calibrated in dB, so keep it out of the default build. Skip the RSSI-difference tracker for now (concept seen, algorithm not read) and skip GPS/MAVLink trackers such as ArduPilot and u360gts, which solve a different problem. The CSI route is available through esp-csi if wanted later. I did not research a camera-overlay method beyond the photo overlay in the Thought Emporium write-up.

## Could not retrieve / unverified
- Not downloaded or read: the SatNOGS wiki bill of materials (.ods) and docs.satnogs.org, the SO-ARM100 BOM, the Waveshare ST3215 wiki and Arduino library, SimpleFOC, Stackchan, Kismet docs (404), Thought Emporium design files, triversity and FR632 source code, ESPARGOS One price. The Instructables FR632 page came back empty.
- The current OnStep repo (hjd1964/OnStep main is a "defunct branch" stub). The "Itty Bitty" telescope was found only as an Instructables search hit and was not fetched.
- The Marauder licence badge is ambiguous. The open360tracker licence is not reported, and the project is stale (last push 2016).
- No Polish shop prices were checked in this run; the 30.90 and ~105 PLN figures come from the brief.
- Not checked: ESP32 web-server MBTiles/PMTiles viewers, and ESPHome integration (pages saved, no claim relied on).
- ESP-SDR is very new and parts are AI-generated by the authors' own admission; its measured table is one board per chip.

Files are in /home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/prior-art/; the quotes are in EXTRACTS.md there.
