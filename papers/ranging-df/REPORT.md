# Research report: ranging-df (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

**Verdict.** Research is partial. About half the technical claims have no source I could read, and I did not infer them. Sources and extracts are in `/home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/ranging-df/` (`EXTRACTS.md` plus the saved files).

**New finding (your "check new esp sdr too"):** ESP-SDR (Oct 2026) and ESPARGOS phase-coherent I/Q capture are more relevant to this project than any ranging chip below.

## 1. Verdict table
| Option | What it adds | Cheapest verified price in PL | Maturity on ESP32/Arduino | Works on arbitrary transmitters? | Evidence |
|---|---|---|---|---|---|
| ESP-SDR on the ESP32-C5 you already plan to buy | Raw I/Q and a spectrum/waterfall at 2.4 and 5 GHz (4.8–6.0 GHz on the C5). A single chip gives no direction by itself. | 0 PLN extra, firmware only | Works today, but is a snapshot spectrum analyzer only | Yes, any signal in band | [V] cnx-esp-sdr, rtlsdr-esp32-hidden-sdr |
| ESPARGOS-style phase-synchronized ESP32 array | Angle of arrival, MUSIC spatial spectrum, direction finding on any 2.4 GHz signal, no pan/tilt head needed | No price or shop found | Research-grade; hardware sale status unknown | Yes | [V] espargos.net, rtl-sdr.com. Price not found. |
| BLE Channel Sounding (nRF54L15, e.g. Seeed XIAO) | Distance to a cooperating BLE device | 42.90 PLN, Botland, shown as OutOfStock | Needs significant work. Both ends must run the stack. | No, cooperative only | Price [V]. Accuracy [S]: SIG "±50 cm", Nordic "IFFT ~50 cm, RTT ~5 m, no guarantees", users saw jumps of metres. |
| BLE AoA/AoD (nRF52833, Silicon Labs) | Angle to a BLE tag, which needs an antenna array | Not found | Not assessed | No, the tag must transmit a CTE (a special direction-finding signal extension) | Silicon Labs doc says only that AoA/AoD exist [V]. No accuracy or price found. |
| UWB DW3000 single-antenna (DWM3001C, Makerfabs/Ai-Thinker BU03, ESP32 UWB) | Two-way ranging (TWR) to a UWB tag at ≤10 cm marketing accuracy | No Polish shop found. Snippets only: DWM3001C $49.48 at Qorvo, BU03 about $17 at RobotShop. | Works with public code | No, cooperative tags only | Chip and standard [V], price [S], accuracy [S] |
| UWB DW3000 PDoA (MaUWB STM32 AOA kit, QM33120) | Distance plus angle to a tag | Not found | Needs significant work. Forum reports erratic angles below 1 m. | No, cooperative only | [V] for the architecture, no verified accuracy |
| SX1280 LoRa ranging (Ebyte E28, LilyGO T3-S3) | Time-of-flight distance between a master/slave pair | 39.90 EUR, Botnroll, Portugal. No Polish price. | Public code exists; needs calibration | No, SX1280 pair only | Datasheet [V], price [V] for Botnroll. Not verified for Poland. |
| Wi-Fi FTM / 802.11az | Not researched | none | none | none | Could not retrieve |
| GNSS + LoRa beacon on the target | Cooperative target position | Not verified | Not assessed | No, cooperative only | Parts cost not retrieved |

## 2. Key facts and sources
1. **ESP-SDR output.** It captures raw I/Q "up to 80 MSa/s" but moves it off the chip only as snapshots. The C5 tunes "4.8–6.0 GHz". It "will only work as a spectrum analyzer". (`cnx-esp-sdr.txt`; `rtlsdr-esp32-hidden-sdr.txt`)
2. **ESPARGOS DF.** ESPARGOS "can now perform direction finding on any arbitrary signal in the 2.4 GHz band". The array is "4 × 2 antenna ... built from phase-synchronized ESP32 chips". (`rtlsdr-esp32-hidden-sdr.txt`; `espargos.txt`)
3. **Single-ESP32 limits.** The eSpDR S3 + FPGA prototype has "poor phase noise". The no-FPGA S3 mode is receive-only with a spur at exactly 2400 MHz. (`rtlsdr-esp32-hidden-sdr.txt`)
4. **SX1280 needs a pair.** The ranging engine measures time-of-flight "between a pair of transceiver radios". Outdoor ZHAW tests found a mean error "below 50 m over distances of up to 1400 m" (30 m DRMS, 5 m when tracking a mobile node). That is useless for pointing a dish. (`sx1280-datasheet.txt` §6.2.5; `zhaw-lora-ranging.txt` abstract)
5. **UWB single-antenna boards give no angle.** A Qorvo forum answer about the Makerfabs ESP32 DW3000 board says: "AoA requires a twin antenna system ... can't measure angles itself". The DWM3001C documentation mentions only TWR and TDoA. (`qorvo-forum-makerfabs.txt`; `dwm3001c-ds.txt`)
6. **PDoA is unreliable at close range.** A user report says "Lower than 1 meter the antenna alignment (or not) makes the angle too erratic". (`qorvo-forum-qm33120-pdoa.txt`)

Every ranging chip above (Channel Sounding, UWB, SX1280) needs a cooperating partner device. Only ESP-SDR and ESPARGOS can work on arbitrary third-party transmitters.

## 3. Recommendation
Include nothing extra in the cheapest build. The planned C5 plus the pan/tilt head already maps signal strength versus direction on arbitrary transmitters. ESP-SDR on the same C5 is a free option worth trying for a spectrum view of 2.4 and 5 GHz around the target. Offer ESPARGOS-style phase-coherent arrays as an add-on only if hardware turns out to be buyable, since they could replace the pan/tilt head for direction finding. The ranging chips (UWB, Channel Sounding, SX1280) only suit your own cooperative beacon. If a tracked target carries a tag, UWB is the most accurate, but it adds cost and the tag must be yours. I would skip SX1280 ranging (metres to tens of metres of error) and BLE Channel Sounding (immature, unstable accuracy).

## 4. Could not retrieve / unverified
- **Nordic.** `devzone.nordicsemi.com` and `docs.nordicsemi.com` return JavaScript shells, so the Channel Sounding accuracy figures are [S]. The nRF54L15 DK, nRF52833 and BG22/BG24 prices and accuracy were also not retrieved.
- **Semtech.** AN1200.29, AN1200.50 and any SX1280 accuracy figure.
- **Qorvo.** Product pages are JavaScript-gated, so the "<10 cm" and "±5°" figures are [S]. The DW3000 user manual and QM33120 datasheet were not retrieved.
- **Other ranging parts.** NXP SR150/SR040, Apple U1/NearbyInteraction/FiRa, LR1121/LR2021, and Wi-Fi FTM/802.11az (esp-idf raw URL returned 404).
- **Prices.** Polish prices for DWM3001C, BU03, Ebyte E28, Waveshare, LilyGO T3-S3, GNSS modules and the nRF54L15-DK. The ESPARGOS One price was not found, and the Botland GPS category prices could not be mapped to products.
- **Shop access.** kamami.pl and tme.eu return 403, so I skipped them.
- **Semantic Scholar.** The API returned 429, so no open-access mirrors were found.
