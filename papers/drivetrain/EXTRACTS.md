# EXTRACTS - drivetrain + ESP-SDR (fetched 2026-11-11)
Evidence tags: [V] = read at source in saved file; [S] = search snippet only (not opened/saved).

## Botland product pages (saved as botland/<id>.txt; price = JSON-LD "price" PLN gross, "availability" as served)
- 21963 Waveshare ST3215 30KG bus servo 22414: 109.00 PLN, availability BackOrder. https://botland.com.pl/serwa-praca-ciagla-360/21963-...waveshare-22414.html
- 25902 ST3235 30kg (Waveshare): 249.00 PLN InStock
- 24907 Bus Servo Adapter (A): 19.90 PLN BackOrder; 21964 ESP32 Servo Driver Expansion Board: 69.90 InStock
- 15546 Grove AS5600: 29.90 InStock; 12807 28BYJ-48+ULN2003: 12.90 InStock; 19883 BTT TMC2209 v1.3: 27.90 InStock
- 17177 Feetech FS90-FB: 12.90 InStock; 4689 FS90R 19.90; 9298 FS5106B 34.90; 24493 MG90S 65.90; 4798 MG-996R (continuous 360 version) 99.90
- 6429 NEMA17 JK42HS40-1704 0.4Nm: 69.00; 3616 JK42HW34-0334 0.22Nm: 64.90
- 7143 slip ring 6-wire 2A 22mm: 67.00 InStock; 7145 12-wire: 84.90
- 21106 Arducam Pan Tilt B0283: 135.00 (GH-S37D digital servos, 180 deg, no feedback); 3724 micro pan/tilt bracket: 4.50; 14430 Waveshare Pan-Tilt HAT: 59.90 BackOrder
- Quote 12807: "Posiada zintegrowaną przekładnię 64:1. ... Moment trzymający po przekładni wynosi 0,3kg*cm (0,03Nm)"
- Quote 17177: "umożliwia bezpośredni pomiar kąta wyjściowego. Kąt pracy wynosi od 0° do 120° w zakresie impulsów od 900 µs do 2100 µs."
- Quote 7143: "Pierścień ślizgowy wyposażony w 6 przewodów o średnicy 0,8 mm."

## msalamon_AS5600.txt  (https://sklep.msalamon.pl/produkt/as5600-enkoder-magnetyczny-12-bit/)
- JSON-LD price 11.19 PLN, availability InStock [V]

## STS3215_datasheet_core.pdf (Feetech spec sheet 2020-04-10, machine translated; https://core-electronics.com.au/attachments/uploads/sts3215-smart-servo-datasheet-translated.pdf)
- p.2 "5-4 Stall Torque ... 16.5kg.cm (6V) / 19.5kg.cm (7.4V)"; "No Load Speed 0.192sec/60° (52RPM)" at 7.4V
- p.4 "6-6 Angle Sensor ... 12Bits Magnetic Coding ... Angle 360° ... Lifespan No limit"; "6-10 Gear Ratio 1/345"; "6-11 Back Lash ... 0.5°" (symbol garbled by translation); "6-8 Weight 55±1g"
- p.5 "7-7 Rotation angle 360°(when 0-4096)"; "7-8 Electronic resolution 0.088°(360°/4096)"
- This sheet is the 6-7.4 V variant. The 12 V / 30 kg.cm figure comes from the Waveshare wiki below.

## ST3215_wiki.txt (https://www.waveshare.com/wiki/ST3215_Servo)
- "Baudrate: 1Mbps ... No load Speed: 0.222sec/60° (45RPM)@12V Pos Sensor Resolution: 360°/4096 ID Range: 0-253 Feedback: Position, Load, Speed, Input Voltage ... Locked-rotor Current: 2.7 A"
- "equipped with a 360° high-precision magnetic encoder, which can realize 360-degree absolute angle control"

## pololu_FS90FB.txt (https://www.pololu.com/product/3436)
- "specially modified to provide access to the feedback potentiometer through a fourth (green) wire, allowing you to directly measure the position of the output"; "Key specs at 6 V: 0.10 sec/60°, 21 oz-in (1.5 kg-cm), 13 g"; "running angle of approximately 120° over a servo pulse range of 900 µs to 2100 µs"

## AS5600_datasheet.pdf (Seeed wiki printout of the Grove module, not the ams datasheet)
- "12-bit high-resolution, 4096 positions per round"; "the maximum angle is also programmable, you can set the maximum angle from 18° to 360°, which means that the measured angular accuracy is up to 18/4096"

## ESP-SDR (https://github.com/ESPARGOS/esp-sdr, files ESP-SDR_*.md, cnx_espsdr.txt = CNX Software 2026-10-04)
- README: "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio."
- README table: "ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 … 4 | also receives 5 GHz"; "ESP32-S3 ... continuous capture¹ and I/Q over USB"; "ESP32-P4 | ❌ | no radio"
- README: "Snapshots are bursts of up to 16,380 samples ... so there are gaps between them. Gain is not calibrated in dB."
- README: "Continuous I/Q on the ESP32-S3: the second core filters and decimates the 16 MS/s stream to 15.625–250 kS/s, sent gap-free over native USB."
- README: "ESP32-S31 streaming (separate esp32s31-stream firmware, experimental): continuous 8-bit I/Q at up to 20 MS/s over high-speed USB or 40 MS/s over Gigabit Ethernet"
- README: "Parts of the firmware are AI-generated"; "All chips accept tuning from 100 to 6000 MHz, but the PLL only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)."
- ESP-SDR_spectrum.md: C5 "Continuous RF capture with on-chip FFT: —"; Snapshot FFT "256–2048 bins; 4/8/10/20/40/80 MS/s"
- ESP-SDR_rx-controls.md: "Hardware AGC is the default; manual gain indices are not absolute gain in dB."
- Implication: on the C5 it is a burst I/Q/spectrum snapshotter with uncalibrated gain, not a calibrated power meter; C5 sniffer RSSI stays the calibrated-ish metric.

## Snippet only [S] (pages not opened; no claim should rest on these)
- Gotronik AS5600 module + magnet 29.00 PLN (LCT-352); Gotronik SimpleFOCMini DRV8313 36.00 PLN (LCT-278); Gotronik 28BYJ+ULN2003 17.69 PLN
- openelab.io STS3215-C018 12V 30kg.cm 27.78 EUR; desertcart.pl C2208 gimbal motor w/ encoder 154 PLN; iFlight GM3506 EUR 28.90 (iflight-rc.eu, not PL shop)
- kamami ST3215-C047 listing (403, no price); Waveshare 2-axis pan-tilt (ST3215) 109.99 USD, Waveshare site
- Community report ~1 deg STS3215 free play vs 0.5 deg spec (forum, unverified)

## Could not retrieve
- TMC2209 datasheet (analog.com blocked; cdn.components.ru mirror PDF corrupt) - no StallGuard4 claim made. https://www.analog.com/en/tmc2209
- 28BYJ-48 manufacturer datasheet (alldatasheet 403; solarbotics 403) - only Botland's 0.3 kg.cm / 64:1 text used; backlash and true steps/rev unverified
- Feetech FS90R/FT90B/FB5311M-360/FS5103B-FB datasheets; MG996R/DS3218 datasheets; SimpleFOC docs; Hiwonder, Dynamixel (Botland only AX-12A 299 PLN), SCS0009; PTZ/Pelco-D heads, AZ-GTi, SatNOGS rotator, Allegro listings (no priced offers found)
- ABC-RC, Kamami, TME, Nettigo, elty, sapsan: not opened (search endpoints unusable / 403)
