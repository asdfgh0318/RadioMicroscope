# Research report: sdr (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

**VERDICT: "new ESP SDR" is almost certainly ESP-SDR (ESPARGOS project, Oct 2026), community firmware, not a new Espressif chip. The ESP32-C5 you already plan to buy (30,90 PLN) runs it at no extra cost and adds a real I/Q receiver for 2.4 and 5 GHz.**

All files are in `/home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/sdr/`, with quotes in `EXTRACTS.md`. Prices are PLN gross. [V] = read at source, [S] = search snippet only.

**1. Verdict table**

| Option | Capability added | Cheapest verified price (PL) | Maturity for an ESP32 build | Tag |
|---|---|---|---|---|
| ESP-SDR on XIAO ESP32-C5 | Raw I/Q and on-chip FFT, 2.4 GHz and 4.8-6.0 GHz, 11-48 MHz analog bandwidth, no extra parts | 30,90 (Botland, InStock) | Works today, public code, browser flasher. Burst snapshots only, gain not dB-calibrated | [V] |
| ESP-SDR on S3 (already owned) | 2.4 GHz I/Q. Gap-free decimated stream up to 250 kS/s, spectra | 0 extra | Works today | [V] |
| ESP-SDR on ESP32-S31 | Continuous I/Q, 20 MS/s over USB or 40 MS/s over Gigabit Ethernet | No PL price found. Hackaday comment says ~$7 (unverified) | Experimental, preview chip | [V] code, [S] price |
| LR2021 raw I/Q (LakeShark / LR2021-SDR) | 100 MHz-2.74 GHz, 250 kS/s max | About $28 for Waveshare Core2021 plus ESP32-P4-WIFI6 (rtl-sdr.com claim, no PL price) | Research-grade, tested on one board | [V] press |
| RTL-SDR V4 plus ESP32-P4 USB host | 0.5-1766 MHz, 2.56 MHz bandwidth | 280,00 (radio-sklep.pl, in stock) | LakeShark proves it works on a P4. Not on a C5 or S3 | [V] |
| RTL-SDR V4 plus Pi Zero 2 W | Same, on a Linux host | 280 + 72,90 (Botland, BackOrder) = ~353 | Works today | [V] |
| tinySA Ultra (ZS-406) | Calibrated spectrum, 100 kHz-6 GHz (calibrated to 5,3 GHz), serial `scan`/`scanraw` | 689,00 (Gotronik, 24h) | Works today with a host that has USB-CDC or UART | [V] |
| tinySA Ultra+ ZS-407 | Same, to 7,3 GHz | 899,00 (Gotronik) | Same | [V] |
| HackRF One R9 | 1 MHz-6 GHz, 20 MS/s, TX | 825,00 (Gotronik) | Needs a PC | [V] |
| AD8319 RF power meter, USB-C (CAD8319) | 100 MHz-8 GHz power only, -50 to -5 dBm, +5 dBm max input | 85,00 (Gotronik) | It is a standalone meter with an LCD. Reading it from a microcontroller is unconfirmed, so treat as needing work | [V] |
| Bare AD8317/AD8318 module | Wideband analog power detector | Not found in PL. AD8318 click board is about 183 PLN via elecena | Needs ADC work | [S] |
| CC1101 | RSSI, 300-348, 387-464 and 779-928 MHz | Not priced | Works today | [V] datasheet |
| nRF24L01+ | 1-bit "power above -64 dBm" flag, 2.4 GHz only | Not priced | Poor | [V] |
| ADALM-Pluto | Full SDR | 1 409 (Kamami) | Needs a PC | [S] |
| CaribouLite, KrakenSDR, Airspy, SDRplay, Nooelec, Pluto+ and LibreSDR | None checked | No PL price found | Not assessed | not retrieved |

**2. Key facts**
- **The C5 is a supported ESP-SDR chip.** The README table row reads "ESP32-C5 | ✅ ... | also receives 5 GHz". The same table marks the P4 "❌ no radio".
- **What ESP-SDR gives you.** `esp-sdr-README.md` says: "receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver ... No extra SDR hardware is needed."
- **Its limits.** `esp-sdr-README.md` says: "Snapshots are bursts of up to 16,380 samples ..., so there are gaps between them. Gain is not calibrated in dB." The same README says the PLL "only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)" (see `esp-sdr-rx-controls.md` for the receive bands).
- **S3 can stream I/Q.** `esp-sdr-iq-stream.md` says 4- and 8-bit samples at 250 kS/s stream gap-free over native USB.
- **LR2021 is a 2026 project with caveats.** From `cnx-lr2021-sdr.txt` and `rtlsdr-lakeshark-lr2021.txt`: "Receive frequency range – 100 MHz to 2.74 GHz (experimentally tested)", and the results "do not establish calibrated receiver sensitivity". It needs LR2021 ROM 1.24 and does not work with the SX1262 variant. The sample rate is at most 250 kS/s.
- **tinySA has a serial interface.** `tinysa-wiki-usb.txt` shows `scan` and `scanraw {start(Hz)} {stop(Hz)} [points]`. `gotronik-tinysa-ultra-card.pdf` lists USB-CDC and UART-TTL and a maximum of 450 points.

**3. Recommendation**
- **Cheapest build:** use the C5 with ESP-SDR as the measuring head, and keep your plan unchanged at no extra cost. You gain raw I/Q, FFT and 5 GHz, but mapping is limited to the Wi-Fi bands and signal strength is not calibrated in dB.
- **Optional add-on:** a tinySA Ultra at 689 PLN for calibrated 100 kHz-5,3 GHz mapping through serial. For about 280 PLN of RTL-SDR V4, a P4 or Pi host gives 0.5-1766 MHz at 2.56 MHz bandwidth, but it adds a second host.
- **Skip:** the HackRF, Pluto and Kamami/TME-only items (a bare AD8317 module, SDRplay, Airspy, Nooelec and CaribouLite) have no PL price or evidence from me. Also skip the nRF24, which gives only a 1-bit flag at 2.4 GHz.
- **Watch:** the S31 and LR2021 are interesting but not yet stable.

**4. Could not retrieve / unverified**
- AD8317/AD8318 datasheet (analog.com blocked). SX1280 datasheet (link returned HTML). SX1262 and LR2021 datasheets not read.
- CC1101 datasheet: I read it and quote it in `EXTRACTS.md`, but deleted the file. Re-fetch from https://www.ti.com/lit/ds/symlink/cc1101.pdf.
- Kamami and TME return 403. The CaribouLite and KrakenSDR pages returned 403. Pluto at 1 409 PLN, Kamami HackRF at 1 486,99 PLN net, CaribouLite "$119" and Pluto+ at EUR 239 are snippets only.
- Botland HackRF page: price not extractable. Radio-sklep shows 280,00 on the page and 270 in the earlier snippet.
- RTL-SDR V3/V4L, Nooelec, generic R820T2, Airspy, SDRplay, KrakenSDR, LibreSDR and CaribouLite: no PL price or vendor page read.
- Whether a microcontroller can read the CAD8319 meter directly.
- The ESP32-S31 price of about $7 comes from a Hackaday comment.
