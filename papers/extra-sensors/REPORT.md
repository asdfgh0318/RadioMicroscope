# Research report: extra-sensors (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

**Verdict.** Add ESP-SDR and the 24 GHz mmWave radar first. Then a VL53L5CX ToF and a camera. Sources are in `papers/extra-sensors/`, quotes in `EXTRACTS.md`. Every quote in that file was checked against the saved text. Prices are PLN gross, read from shop page data and listed in `EXTRACTS.md`. I did not get to 60 GHz radar, Infineon BGT60, InfiRay or Topdon cameras, HTPA, or RM3100. I also ran out of time to cover SPI versus I2C pin sharing in detail.

**New ESP SDR ("check new esp sdr too").** ESP-SDR is firmware from the ESPARGOS project that turns supported ESP32s into a receive-only 2.4/5 GHz I/Q sampler. This is from the CNX article of 2026-10-04, already saved in `papers/sdr/cnx-esp-sdr.txt` and quoted in `EXTRACTS.md`.
- It lists ESP32-C5 among supported chips, and your measuring radio is a C5, so it costs 0 PLN extra.
- Its limit is "captures short I/Q snapshots to build the spectrum and waterfall", so it is a spectrum and waterfall tool, not a continuous demodulator.
- It is not a Wi-Fi RSSI replacement. It could add a per-direction spectrum, which I did not test.
- Transmit support exists only in experimental community projects.

**1. Verdict table** (evidence: [V] read at source, [S] shop page or snippet text only)

| Option | What it adds | Cheapest verified PLN | Maturity (ESP32/Arduino) | Evidence |
|---|---|---|---|---|
| ESP-SDR (on the C5 you already plan) | Spectrum and waterfall per direction | 0 | New, partly AI-generated code, snapshot-only | [V] CNX article |
| HLK-LD2410B/C 24 GHz radar | Presence, distance gate, moving/still energy, up to 6 m | 33,19 (msalamon, B, in stock); C is 28,09 but out of stock | Works today (ESPHome driver) | [V] ESPHome page, [S] msalamon |
| HLK-LD2450 24 GHz radar | Up to 3 targets with x, y and speed, 6 m, ±60° azimuth / ±35° pitch | No Polish page found | Works today (ESPHome driver) | [V] manual, no PLN price |
| VL53L5CX 8x8 ToF | 64-zone depth map, 2–400 cm, 63° diagonal | 69,90 (Botland, Pololu 3417, out of stock); 149,90 SparkFun in stock | Needs a library plus a ~90 KB firmware upload at boot | [V] ST datasheet, [S] Botland |
| TF-Luna single-point lidar | 0.2–8 m, 100 Hz, 2° FOV, UART or I2C | 99,00 (Botland, in stock) | Simple | [S] Botland |
| MLX90640 / MLX90641 thermal | 32x24 (110° or 55° FOV), up to 64 Hz | Bare board: no PLN price found. M5Stick T-Lite kit 439,00; MLX90641 16x12 249,00 (out of stock) | Works today (I2C) | [V] datasheet, [S] kit prices |
| AMG8833 thermal | 8x8, 60° FOV, I2C | No Polish listing found | Works today | [V] spec, no PLN price |
| OV3660 / OV5640 camera | Visible image; OV5640 has autofocus | DFR1154 ESP32-S3 + OV3660 109,00; M5 CamS3 5 MPx 89,90 (I did not confirm the CamS3 sensor) | Autofocus needs a firmware blob loaded over SCCB | [V] esp32-camera README, [S] Botland |
| ESP32-P4 (MIPI-CSI) | Camera interface | M5Stamp ESP32-P4 63,90 (in stock) | Board is cheap, but the camera module and software are extra work | [V] datasheet lists MIPI CSI, [S] Botland |
| INMP441 I2S MEMS mic | Per-direction sound level (an acoustic camera needs more than one mic) | 12,00 (Gotronik) | Works today | [S] |
| XVF3800 4-mic array | Sound direction (DoA) and beamforming | 269,00 (Botland, out of stock) | Works over USB | [V] Seeed wiki, [S] Botland |
| QMC5883L / MMC5603 / BMM150 magnetometer | Magnetic field mapping | 27,90 to 31,90 | Works today | [S] |
| AS3935 lightning | Strikes to 40 km, I2C or SPI | 139,00 (Botland) | Works today | [S] |
| GNSS (AT6668 module) | Position, up to 10 Hz, UART | 61,90 (Botland); ATGM336H 32,59 (msalamon) | Works today | [S]; raw-data output not verified |
| LD19 360° lidar | 12 m scanner | 599,00 | Spins on its own, wrong fit for a pan/tilt head | [S] |

**2. Key facts**
- LD2450 quotes (`ld2450.pdf`, section 2.1): "Precise motion target localization and tracking", "Longest detection range 6m", "Azimuth angle ±60°, pitch angle ±35°". The serial default is 256000 baud, so it wants a hardware UART.
- The MLX90640 datasheet says: "Small size, low cost 32x24 pixels IR array" and "2 FOV options – 55°x35° and 110°x75°". The AMG8833 spec says: "Pixel number 64（8×8 Matrix）".
- The VL53L5CX datasheet says: "Up to 400 cm ranging", "I2C: 400 kHz to 1 MHz serial bus, address: 0x52". I2C address 0x52 is fixed, so it needs an XSHUT or LPn pin to share a bus with a second ToF part.
- XIAO ESP32-S3 pins (`xiao_s3_wiki.txt`): D4/D5 are I2C (GPIO5/6), D6/D7 are UART (GPIO43/44), and the camera, SD card and PDM mic already use many other pins (PDM clock is GPIO42). Put I2C parts on one bus (VL53L5CX, a magnetometer, a thermal array, AS3935) and the radar on the UART. SPI is mostly taken by the SD card (SCK on GPIO7).
- ESP32-P4: the datasheet lists "– MIPI CSI". Botland describes the M5Stamp ESP32-P4 with "interfejsy MIPI CSI i MIPI DSI". It does not change the cheap build. You already own a camera on the XIAO S3 Sense.
- The cheapest Polish mmWave parts are Botland's Seeed Human Static Presence at 24,90 (UART and GPIO, 0.75–6 m) and the HLK-LD2410B at 33,19. The Waveshare S3KM1110 at 12,90 was out of stock.

**3. Recommendation.**
- **Cheapest build:** the ESP32-C5 you already planned, with ESP-SDR as a free software add-on. Add an LD2410B (33,19) on the UART only if you want moving-target or presence data.
- **Optional add-ons, by capability per zloty:** the 8x8 VL53L5CX depth overlay (69,90), then a magnetometer (about 30 PLN, a coarse magnetic map). A thermal camera is the next step if you accept 249–439 PLN. I found no Polish source for a bare MLX90640 or AMG8833.
- **Skip:** the LD19 360° lidar (599 PLN, it spins on its own), the XVF3800 (269 PLN, out of stock, USB only), the AS3935 (139 PLN) and Geiger modules (289–299 PLN), and the ESP32-P4 (no gain over the camera you own).

**4. Could not retrieve / unverified.**
- kamami.pl and tme.eu returned 403, so no price from them.
- No Polish PLN price found for LD2450, bare MLX90640, AMG8833, RD-03D/E, LD2420 or LD2461.
- Only shop page text (no datasheet PDFs) was read for TF-Luna, TFmini-S, LD19, INMP441, ICS43434, AS3935 and the magnetometers. INMP441, ICS43434 and AS3935 have no datasheet saved, so any claim about them is a shop claim only.
- Not researched: HLK-LD2420, MR24HPC1/MR60BHA2 manuals, Infineon BGT60, Ai-Thinker RD-03, HB100 specs (the Nettigo page was saved but not read for specs), HTPA, InfiRay P2, Topdon TC001, RM3100, MMC5983MA, and ESP32-C5 pin sharing.
- GNSS raw-data output is unverified.
- The WebSearch tool returned model-summarised text, so I relied only on pages I fetched myself.
