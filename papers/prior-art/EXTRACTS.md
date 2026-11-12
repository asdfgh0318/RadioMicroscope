# Prior-art extracts (retrieved 2026-11-11). All quotes verbatim from the local files named.

## ESP-SDR (new ESP32 SDR firmware), https://github.com/ESPARGOS/esp-sdr  (GPL-3.0 per GitHub API)
File ESPARGOS_esp-sdr-README.md
- "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver and sends them to your computer over USB or UART."
- Table row: "| ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 … 4 | also receives 5 GHz |"; "| ESP32-P4 | ❌ | | | | no radio |"
- "Snapshots are bursts of up to 16,380 samples ..., so there are gaps between them. Gain is not calibrated in dB."
- "The firmware speaks a simple line-based protocol over native USB or UART (2 Mbaud): `INFO`, `FREQ 2442`, `CAP16 4096 0` and so on"
- "All chips accept tuning from 100 to 6000 MHz, but the PLL only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)."
File esp-sdr-protocol.md: "`GPIO <pin> <Z|0|1>` | Spare GPIO outputs, e.g. for antenna switches."; "Hardware AGC is the default. Indices are PHY table indices, not dB." (GAIN row: "Indices are PHY table entries, not dB.")
File esp-sdr-rx-controls.md (Measured reception range): C5 row "| C5 | – | – | – | ✓ | ✓ | – | – | – | ✓ |" (2200, 2300-2650 and 5180-5800 MHz received); "'✓' means the tone was at least 15 dB above the noise inside the analog filter (typically 35–65 dB)"; "One board per chip, October 2026".
File cnx-esp-sdr.txt (CNX Software, 2026-10-04): "This open-source firmware bypasses the ESP32's fixed-function Wi-Fi and Bluetooth modems ... capture raw I/Q baseband samples."; "Both ESP-SDR and ESP-WebSDR are open-source projects released under the GPL-3.0 license."; "Parts of this code are AI-generated."; "ESP-SDR relies on the ESP32's built-in radio ... basic spectrum analysis possible on an ESP32 board that can cost less than $5."

## (a) WiFi-camera projects
- Thought Emporium WiFi camera, rtlsdr-wificam-hackrf.txt (https://www.rtl-sdr.com/building-a-wifi-camera-with-a-hackrf-and-helical-antenna-on-a-motorized-pan-tilt-mount/): "The idea behind the 'WiFI camera' is to point the directional helical antenna in different directions using the motorized mount and measure the WiFi signal power using the HackRF at each spot it points towards. Each measurement results in a heatmap pixel, and once enough pixels have been collected, an image is formed." Also "releasing a new open-source 3D printable version."
- rtlsdr-heatmap.txt: "After each movement step a HackRF and Python script is used to measure WiFi signal strength for a brief moment, and then the rotator moves onto the next angle."; "they've been able to successfully generate heatmaps that can be overlaid on top of a photo."
- SparkFun ESP8266 maximizer, sparkfun-2363.txt (https://news.sparkfun.com/2363, 2017): "the ESP8266 would take an RSSI reading and remember the yaw and pitch settings of the highest RSSI"; "sweeping up and down (about 70°) and left to right (about 180°). At 5° increments"; "Because the sweep arc is limited, the best connection might be behind the antenna."; "If you stand in front of the antenna ... You change the multipath propagation".
- 3D_wifi_scanner (3dwifi-readme.md, https://github.com/Neumi/3D_wifi_scanner): saved, README only 2 KB, no licence shown by API; no claim relied on beyond existence.
- ESPARGOS / pyespargos (espargos-pyespargos.md, LGPL-3.0): "Camera Overlay" demo exists in demos/wifi/camera; rtlsdr-espargos.txt saved.

## (b) Trackers / rotators
- SatNOGS rotator firmware, satnogs-rotator-fw.md (GitLab librespacefoundation/satnogs-rotator-firmware, GPLv3): "## Easycomm implemantation * AZ, Azimuth, number - 1 decimal place [deg] * EL, Elevation ..."; "Use commands of rotctl: rotctl -m 204 -s 19200 -r /dev/ttyUSB1"; "Licensed under the [GPLv3]". Controller hardware: satnogs-rotator-raw.md "Licensed under the CERN OHLv1.2".
- Hamlib easycomm backend, hamlib-easycomm.c: `SNPRINTF(cmdstr, sizeof(cmdstr), "AZ%.1f EL%.1f\n", az, el);` (set position for EasyComm 2/3); get position sends "AZ\n". rotctld man page: hamlib-rotctld.md.
- ArduPilot AntennaTracker, ardupilot-tracker.txt: "This tracker determines the position of a remote vehicle via its own GPS data and telemetry data from a Copter, Rover, or Plane, and uses this information to align a directional antenna towards the vehicle." (GPS/telemetry based, not RSSI).
- u360gts, u360gts-README.md (GPLv3): "released for free under the GPLv3 license"; "Multiprotocol. Automatic protocol detection."; STM32 F1/F3 target (not ESP32).
- open360tracker: SamuelBrucksch/open360tracker, open360tracker-README.md saved; last push 2016-11-02 (GitHub API); no licence reported by API.
- Triversity RSSI tracker, hackaday-triversity.txt (hackster, MIT, 2018): "The code is based on 3 antenna RSSI signal, one UP and two DOWN. The two Down are Left (SX) and Right (DX), the mean value of DX and SX is taken as DW value." Hardware "Arduino Mega, rx5808". Steering code itself is "download only" - algorithm details NOT read.

## (c) Servo stack
- LeRobot SO-101, lerobot-so101.md (Apache-2.0 per LICENSE + API): "The follower arm uses 6x STS3215 motors with 1/345 gearing."; BOM only linked (TheRobotStudio/SO-ARM100) - not read. lerobot-feetech.md: "Set the appropriate baud rate (typically 1000000 for most Feetech motors)".
- Waveshare PT firmware, SimpleFOC, Stackchan: NOT retrieved.

## (d) Radio-telescope scanners
- UPennEoR MiniRadioTelescope, miniradiotelescope-README.md: "This GitHub contains Arduino and Python code for the telescope."; hardware list: Arduino Uno, Raspberry Pi, Big Easy Driver, bias tee, "Power Detector ZX47-60LN-S+", LNA, RTL-SDR. No licence reported by API.
- hackaday-miniradio.txt: "the MRT is using an Arduino connected to a trio of Big Easy Drivers ... they allow the user to map the sky in radio frequencies."
- Ku-band motorised, rtlsdr-ku-motorized.txt: "66 cm parabolic dish, a standard Ku-band LNB ... RTL-SDR V3 ... Raspberry Pi 5 ... two NEMA17 stepper motors ... long term resolution is limited due to cumulative backlash errors from the open-loop control scheme."
- PICTOR (0xCoto/PICTOR, GPL-3.0), pictor-README.md: "Beamwidth (HPBW @ 1420 MHz): ~8.95°"; "fully open source (software & hardware)"; drift-scan (no motorised mount).
- OnStep: hjd1964/OnStep main README says "This is a defunct branch and should not be used!" (onstep-README.md) - no claim; current repo not located.

## (e) ESP32 tools / formats
- esp-csi (Apache-2.0), esp-csi-README.md: "All ESP32 series support CSI, including ESP32 / ... ESP32-C5 / ESP32-C6 / ESP32-C61."; "rich channel information, including RSSI, RF noise floor, reception time".
- Wigle CSV, wigle-csv-format.txt (https://api.wigle.net/csvFormat.html): pre-header "WigleWifi-1.6,appRelease=...,model=..."; header "MAC,SSID,AuthMode,FirstSeen,Channel,Frequency,RSSI,CurrentLatitude,CurrentLongitude,AltitudeMeters,AccuracyMeters,RCOIs,MfgrId,Type".
- PMTiles, pmtiles-docs.md: "PMTiles is a single-file archive format for tiled data." (spec v3 saved).
- Marauder (README saved; licence badge ambiguous - treat as unverified), Bruce: "distributed under the terms of the Affero General Public License (AGPL)" (bruce-README.md).
- ESPHome pages saved (esphome-wifi-signal.txt, esphome-ble-proxy.html); no specific claim relied on.

## Could not retrieve / not read
- SatNOGS wiki BOM (.ods) and docs.satnogs.org page; SO-ARM100 BOM; Waveshare ST3215 wiki/Arduino library; SimpleFOC; Stackchan; current OnStep repo (hjd1964/OnStep main is defunct stub); Kismet docs (404); ESPARGOS One price; Thought Emporium design files; triversity/FR632 source code; Instructables FR632 page (empty on fetch); open360tracker licence; kamami/tme (403).
