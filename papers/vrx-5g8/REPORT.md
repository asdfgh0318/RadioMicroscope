# Research report: 5.8 GHz analog video receivers on ESP32 (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

VERDICT: "The new analog VRX ESP" is most likely C5VRX (github.com/Twotoz/C5VRX, GPL-3.0): a Seeed XIAO ESP32-C5 plus 7 resistors that receives analog 5.8 GHz FPV and outputs composite PAL/NTSC to goggles or a monitor. A second candidate, ESPsoup (espsoup.com), shows analog video on a phone or PC and has an RSSI "Find" mode. Both exist and run today, but both are experimental. Nothing else matched: no commercial ESP-based analog VRX turned up in two searches (standard and extended), and the ExpressLRS VRX Backpack only changes channel. All files and full quotes: /home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/vrx-5g8/ (EXTRACTS.md + 60-odd saved files). I wrote nothing outside that directory.

1. WHAT IT IS, AND IS IT USABLE
- C5VRX [V]: repo created 2026-08-30, pushed 2026-11-10, 532 stars. CircuitDigest covered it 2026-10-23.
  - The XIAO C5 reads the radio's raw ADC stream (MODEM_DIAG, 40 MS/s) and does the FM demodulation in the BitScrambler peripheral, so the CPU is not in the sample path. It covers 48 channels with a scan mode.
  - The README says the demodulator "has one positive NTSC check; PAL, weak-signal behaviour and range still need hardware validation." rtl-sdr.com says it "doesn't yet work reliably at range."
  - The README carries a crash-risk warning: do not rely on it as the only video path.
  - It has a GAIN mode "RSSI" and a dBm meter that reads carrier-to-noise over its own noise floor.
  - It is its own firmware, not an ESP-SDR app. It only borrows ESP-SDR's C5 filter control.
- ESPsoup [V]: firmware 0.7.1, GPL-3.0, based on ESP-SDR, updated 2026-11-06. Free web and Android app.
  - Its TV tool demodulates analog FPV on the C5 itself, at about 25 fps, black and white with coarse colour.
  - The test was lab-signal-generator only: 52 of 52 channels gave a picture, 2 needed a second try.
  - Output is the phone or PC screen, not goggles.
  - It also has "Find (hot/cold) with GPS heatmap", usable over about 25-30 dB, and a live panorama at about 15 sweeps/s over 2.4 GHz.
- Other candidates:
  - ExpressLRS VRX Backpack: ESP8285/ESP-01F; sends channel changes over ESPnow, no video.
  - PhobosLT: ESP32 + RX5808 lap timer, MIT, RSSI only.
  - FENIX/sheaivey rx5808-pro-diversity: MIT, STM32/Arduino-class MCU, not ESP.
  - Happymodel EP82: backpack only.

2. CAN AN ESP32-C5 WITH ESP-SDR DEMODULATE FPV VIDEO?
- Stock ESP-SDR on the C5 cannot do it by itself [V]. The C5 has no continuous-capture mode, only snapshots of up to 16,380 samples with gaps, at 4-80 MS/s. Its analog bandwidth is 11-48 MHz, so an 18-20 MHz channel fits.
- rtl-sdr.com wrote that demodulating continuous radio on an ESP32 "is not possible with just an ESP32" (except the S31). That is true of stock ESP-SDR and is contradicted by C5VRX and ESPsoup.
- Demonstrated: video on the C5 from those two custom firmwares. Not demonstrated: independent flight or range figures, or PAL beyond synthetic tests.

3. RECEIVER OPTIONS FOR A PALM-SIZED 5.8 GHz TRACKER
| Option | Video? | RSSI, how fast | Size/weight | Price and shop | Maturity | Tag |
|---|---|---|---|---|---|---|
| RX5808 module (RTC6715) | Yes, analog out | Analog RSSI pin; speed not documented | 28x23x3 mm, 3.6 g, about 170 mA | 7.49 EUR Rotorama (discontinued), 17.99 USD WREKD; no PLN price found | Very mature: PhobosLT, RotorHazard, FENIX | [V] for the vendor figures; [S] for the "about 50-60 PLN" estimate |
| XIAO ESP32-C5 + C5VRX | Yes, composite via a 7-resistor DAC | dBm meter in firmware; update rate unknown | 21x17.8 mm; C5 RX about 110 mA peak | board about 15-25 EUR [V via ESPsoup]; no PLN price | Experimental, some range loss | [V] |
| XIAO C5 + ESPsoup | Phone/PC only, black and white | Panorama about 15 sweeps/s; Find mode | same board | free app | Beta, lab-tested | [V] |
| XIAO C5 + stock ESP-SDR | No | Snapshot spectra with gaps, gain not in dB | same | free | Works as a spectrum analyser | [V] |
| RX5808 + ESP32 (PhobosLT-style) | Optional, via the module | RSSI into the ESP32 ADC | RX5808 plus ESP32 | about 7-18 USD for the RX5808 | Mature | [V] |

4. RECOMMENDED ARCHITECTURE (my inference from the sources)
Use the XIAO ESP32-C5 as the signal-strength sensor and tracker brain: it is already in the main instrument, and ESP-SDR gives 5.18-5.8 GHz snapshot power. For video, add an RX5808 (SPI-modded, 3.6 g) rather than relying on C5VRX for flight use. C5VRX's own warning about video loss argues against that. Both radios need a shared antenna. I found no source for a splitter, so a 2-way split costs about 3 dB, or you can time-share. The alternative is C5VRX on a second C5, as a bench or experimental video path only. The RX5808's analog RSSI could also drive the tracker directly, as PhobosLT does on an ESP32 ADC pin. I could not read RSSI voltage range or settling time from a primary document.

5. WHAT EXISTING TRACKERS TEACH
- The documented RSSI-only builds compare two offset directional antennas and steer toward the stronger one. FR632 (FlyerFpv, 2018, AGPLv3 code) uses a diversity receiver, an Arduino Pro Mini and one servo, yaw only. Each receiver needs RSSI_MIN/MAX calibration. Hackaday said "the response could be snappier," and that the editors were "not sure it would" keep the video locked.
- A triversity (three-antenna) pan/tilt build exists on Arduino Project Hub, but its page is thin.
- GPS and telemetry trackers (u360gts GPLv3, open360tracker, ArduPilot AntennaTracker) are not RSSI-only.
- Lesson: RSSI differencing needs two or more offset beams. I found no source on a single scanning antenna, and no measured error or lock-rate figures for any RSSI tracker. Per-module RSSI calibration is mandatory ("No two modules have the same RSSI min and max readings").
- Antennas:
  - Analog video links are normally RHCP ("RHCP is the default for most (if not all) analog systems", IntoFPV, a community post), so buy RHCP; matching handedness matters.
  - Triple Feed Patch-1: about 60 mm disc, about 20 g (indirect sources), 9.3 dBi measured, 55 degree beamwidth. That is at the limit of a 9 cm head and a 20 g budget.
  - Foxeer Echo 2 RHCP: 8 g, 9 dBi, 121 PLN at ht-dron (out of stock when checked).
  - Helical options: not researched.
- Drone use:
  - (a) Ground tracker: the antenna must stay RHCP-matched to the video transmitter. C5VRX must not be the only video path.
  - (b) Airborne mapper: the RX5808 is 3.6 g and about 170 mA, the C5 about 110 mA RX peak and the Echo 2 8 g, so the receive chain is well under 20 g. Vibration, quad mass budgets and legal limits: no sources.

6. COULD NOT RETRIEVE / UNVERIFIED
- The RX5808/RTC6715 datasheet: every mirror failed. So no primary RSSI voltage range, response time, supply range or video/audio levels. I have only the vendor figures above, plus the SPI frame and channel table read from FENIX source.
- Polish RX5808 prices: Botland has no product; ht-dron, abc-rc, megadron and rcmaniak search pages are JS-only; Allegro returned 403; Kamami, TME and AliExpress were not retrievable. Please paste links if you want PLN prices.
- EzAntennaTracker page and manual (503/HTML): [S] only. The Instructables original was empty; I used a mirror.
- ESPsoup and C5VRX range or flight data (bench/lab claims only), and the ESPsoup GitHub repos (not fetched).
- Helical antennas, airborne vibration and mass budgets, and commercial ESP-based analog VRXs.
