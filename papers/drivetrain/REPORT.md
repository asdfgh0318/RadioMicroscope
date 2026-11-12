# Research report: drivetrain (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

**Verdict.** Research is partial. Botland prices (read from product-page data, 2026-11-11), the Waveshare/Feetech ST3215 specs, the Pololu FS90-FB page and the ESP-SDR repo were read at source. The TMC2209 and 28BYJ-48 datasheets, the Feetech FS90R/FT90B/FB5311M-360, MG996R and DS3218 datasheets, the Hiwonder LX-16A/LX-224 and Dynamixel XL330/XL430 parts, and the PTZ heads, AZ-GTi, SatNOGS rotators and Allegro listings were not retrieved. Those rows are marked [S] or unverified.

Files are in /home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/drivetrain/ (EXTRACTS.md, botland/*.txt, ESP-SDR_*.md, STS3215_*.pdf, ST3215_wiki.txt, pololu_FS90FB.txt, AS5600_datasheet.pdf).

**1. Verdict table** (per axis, PLN gross; "unpowered" = holds position with power off)

| Option | Capability added | Cheapest verified price | Angle feedback | Accuracy / backlash | Speed | Unpowered | Maturity | Tag |
|---|---|---|---|---|---|---|---|---|
| Feetech FS90-FB micro servo | Pot feedback wire, 0-120° only | 12.90, Botland, in stock | analog pot, resolution unspecified | Not sourced | 0.10 s/60° at 6 V | Unverified | Works today; limited to 120° travel | [V] |
| 28BYJ-48 + ULN2003 + AS5600 | Cheapest continuous 360° axis | 12.90 (Botland, motor + driver) + 11.19 (msalamon AS5600) = 24.09 | AS5600, 12-bit (4096 counts) | Backlash and steps/rev unverified (datasheet not fetched) | Not sourced | Unverified | Public code exists; torque is the limit | [V] prices, datasheet missing |
| NEMA17 + TMC2209 + AS5600 | Direct drive, 200 steps/rev | 64.90 (JK42HW34, 0.22 Nm) + 27.90 + 11.19 = 104.0 | AS5600 | No gear backlash; sensorless homing unverified | Not sourced | Unverified | Works today | [V] prices only |
| Waveshare ST3215 (30 kg·cm at 12 V) | 360° absolute, 4096 counts, bus feedback | 109.00 Botland (BackOrder); +19.90 adapter (BackOrder) or 69.90 driver board | 12-bit magnetic, 0.088° per count | Spec sheet backlash ≤0.5° (garbled in the translated sheet); a forum snippet reports about 1° | 45 RPM at 12 V | Unverified | Works today | [V] |
| ST3235 | Same family, higher torque | 249.00 Botland | magnetic | not read | not read | Unverified | Works today | [V] price |
| SimpleFOC Mini + gimbal motor + AS5600 | Smooth, quiet, backlash-free | about 200 (36 + 154 + 11) | AS5600 | Not sourced | Not sourced | No | Needs significant work | [S] |
| Ready-made mechanics | Brackets, no printing | 4.50 micro pan/tilt bracket; 135 Arducam B0283 (2 axes, 180°, no feedback) | none | not sourced | not sourced | n/a | Works today | [V] |
| 6-wire slip ring | Unlimited pan rotation | 67.00 Botland | n/a | n/a | n/a | n/a | n/a | [V] |

Other Botland prices: MG90S 65.90, FS5106B 34.90, Dynamixel AX-12A 299.

PTZ heads, AZ-GTi, SatNOGS rotators and Allegro: no priced offer found, so no claim.

**2. Key facts**
- ST3215: "Pos Sensor Resolution: 360°/4096 ... Feedback: Position, Load, Speed, Input Voltage ... No load Speed: 0.222sec/60°(45RPM)@12V" (ST3215_wiki.txt). The Feetech sheet gives "Angle Sensor ... 12Bits Magnetic Coding", "0.088°(360°/4096)" and gear ratio 1/345 (STS3215_datasheet_core.pdf, p.4-5).
- FS90-FB: "access to the feedback potentiometer through a fourth (green) wire ... approximately 120° over 900-2100 µs ... 1.5 kg-cm, 13 g" (pololu_FS90FB.txt). Botland 17177 is 12.90 PLN.
- 28BYJ-48 (Botland 12807): "przekładnia 64:1 ... Moment trzymający po przekładni wynosi 0,3kg*cm". That torque is thin for a 150-500 g antenna.
- AS5600 gives 4096 counts per turn (AS5600_datasheet.pdf), which is far finer than a 30-60° beam needs.
- ESP-SDR (ESPARGOS, CNX 2026-10-04): "ESP32-C5 | ✅ ... 80 … 4 | also receives 5 GHz". It gives burst I/Q snapshots of up to 16,380 samples with gaps between them, and "Gain is not calibrated in dB" (ESP-SDR_README.md, ESP-SDR_rx-controls.md). The C5 has no continuous capture (ESP-SDR_spectrum.md). Continuous I/Q needs the S3 (250 kS/s max over USB) or the experimental S31. The README says parts of the firmware are AI-generated. So the C5 sniffer's RSSI stays the measurement; ESP-SDR is a bonus for spectrum snapshots and cannot replace it.
- Slip ring: 67 PLN for 6 wires at 2A. A pan limited to about ±180° with a service loop avoids it.

**3. Recommendation**
- **Cheapest good-enough build:** two FS90-FB servos on the 4.50 PLN pan/tilt bracket, about 30 PLN for both axes. A 30-60° beam does not need 0.088° resolution. The catch is that each axis only covers 120°, and the payload is marginal at 1.5 kg·cm. Keep the antenna under about 150 g, centred.
- **Best under 150 PLN per axis:** the ST3215 at 109 PLN. It gives full 360° absolute angle and load feedback with no extra encoder, plus one shared 19.90 PLN adapter. Botland shows it on backorder, so check stock before ordering.
- **Optional add-on:** AS5600 at 11.19 PLN on a 28BYJ-48 or NEMA17 axis if a stepper is preferred. Add ESP-SDR on the C5 only as a spectrum-snapshot bonus.
- **Skip:** the gimbal-motor route (about 200 PLN per axis, needs significant work, no sourced numbers), the slip ring (67 PLN), and any Dynamixel or PTZ-head route.

**4. Could not retrieve / unverified**
- TMC2209 datasheet: analog.com blocked, mirror corrupt. Sensorless homing is unverified.
- 28BYJ-48 manufacturer datasheet: alldatasheet and solarbotics returned 403. Backlash and true steps per turn are unverified.
- Datasheets for Feetech FS90R/FT90B/FB5311M-360/FS5103B-FB, MG996R, DS3218 and SG90, plus SimpleFOC docs.
- Hiwonder LX-16A/LX-224, Dynamixel XL330/XL430 and SCS0009: no Polish prices found.
- Snippet-only prices: Gotronik AS5600 + magnet 29.00, SimpleFOCMini 36.00, desertcart C2208 gimbal motor 154, openelab STS3215 at 27.78 EUR.
- Waveshare's ST3215 pan-tilt kit: USD 109.99 snippet, no Polish price.
- Kamami and TME return 403.
- ABC-RC, Nettigo, elty, sapsan and Allegro: not opened.
- Unpowered holding torque is unverified for every option.
