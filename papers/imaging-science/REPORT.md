# Research report: imaging-science (2026-11-11)

Written by a research agent. The quotes behind each claim are in EXTRACTS.md in this folder.

## 1. Verdict

| Option | What it adds | Cheapest verified price (PL) | Maturity for an ESP32/Arduino hobby build | Evidence |
|---|---|---|---|---|
| **ESP-SDR firmware (new, Oct 2026) on the planned XIAO ESP32-C5** | Raw I/Q bursts at 80…4 MS/s at 2.4 GHz and 5 GHz, so you get the band power of *any* emitter (BLE, non-Wi-Fi, 802.11b) instead of per-packet RSSI. Gain index is embedded in every sample. GPL. | 0 PLN extra (board 30.90 PLN, Botland, in stock) | Works today with public code (browser flasher, UART/USB protocol). Logging tied to the pan/tilt still needs writing. | [V] |
| ESP-SDR continuous I/Q on the XIAO ESP32-S3 you already own | Gap-free 15.6–250 kS/s I/Q over native USB. The S3 also receives 1850–2200 MHz. | 0 PLN | Works today. USB only, no 5 GHz. | [V] |
| Deconvolving the antenna beam (CLEAN / linear model r = G·P) | Sharper maps than the beamwidth allows, and separation of nearby sources | 0 PLN (host software) | Significant work. Least squares is reported to fail. | [V] |
| Wi-Fi holography (a scanned antenna plus a fixed reference antenna, two coherent receivers) | cm-scale 3-D emitter localisation and object shadows | 2nd XIAO C5 30.90 PLN, plus a shared 40 MHz clock, a phase reference and an RF switch (not priced) | Research-grade on ESP32. Published versions used an oscilloscope or a 2-channel AD9361 SDR. | [V] |
| ESPARGOS One (8 phase-coherent ESP32 receivers, CSI + I/Q) | A ready-made coherent 2.4 GHz "camera": AoA and Wi-Fi imaging | €350 excl. VAT, EU-only, sold by the project rather than a PL shop (PLN not verified) | Works today (pyespargos, demos). Only qualitative AoA has been published. | [V] |
| CSI-phase AoA / SAR / ToF (SpotFi, ArrayTrack, Ubicarse, Chronos) | 0.23–0.65 m localisation | n/a | Research-grade. They need ≥3 coherent antennas, motion plus phase, or a cooperating transmitter that hops channels. | [V] (Ubicarse not retrieved) |
| Ku-band LNB + satfinder payload | A thermal "warm object vs cold sky" map with a bare LNB; the Sun appears only with a dish | 29.99 + 49.90 PLN (MediaMarkt.pl, in stock) | Works today with a satfinder + Arduino ADC. The VA0314's analog output was not checked. | [V] |
| 21 cm hydrogen-line horn + SDR | Galactic HI | not priced | Not a pan/tilt payload: needs a 75×60 cm horn or a dish of ≥70 cm. | [V] |

## 2. Key facts
1. **ESP-SDR is the real news.** It "turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio". On the C5 it supports "80 … 4" MS/s and "also receives 5 GHz". Each snapshot is up to 16,380 samples, and "Gain is not calibrated in dB". On the C5 the receiver is driven over UART at 2 Mbaud on GPIO11/12, so the S3 controller can talk to it. (`github_espargos_esp-sdr_README.md`)
2. **Use manual gain for power mapping.** With a strong continuous signal, "every Wi-Fi chip clipped in AGC mode … Use manual gain for strong signals." (`github_espargos_esp-sdr_docs_rx-controls.md`)
3. **A single ESP32 cannot give you imaging phase.** Every packet's CSI is "phase-rotated by a common factor e^jφ". "Reference clock distribution is insufficient", because the PLL phase "changes after a chip reset and after modifying the LO frequency". ESPARGOS fixes this with a per-receiver RF switch and a distributed phase-reference signal. (`euchner2025_espargos_channel_sounder.txt` §II-A, §III-A). The single-antenna workaround (a ratio across subcarriers) cancels the CFO/SFO offsets, so only relative phase is left (`sawisense_2507.17623.txt` Lemma 1).
4. **Holography requires two coherent channels.** Holl & Reinhard fed "two equal mixers, one for each antenna" from one oscillator. They reached σ = 3 cm emitter focus over a 3×2 m scan, at "about two points per second" (`holl2017_wifi_holography.txt`, Fig. 1 and SI). A 2026 follow-up used "an AD9361 with two coherent receive channels" and found that "an incoherent imaging approach is sufficient" for narrowband signals (`cites_holl_2605.03875.txt`).
5. **RSSI with a rotating directional antenna is about as good as the beam.** An actuated reflector gave a mean error of <4° and an SD of <8° both indoors and outdoors, but only with "no moving objects" (`hood2011_actuated_reflector_doa.txt`). A 70° HPBW antenna gave errors under 40° about 90% of the time (`arrest_1707.05493.txt` §VIII). The r = G·P inversion needs "compressible sampling"; "Min-Square Approximation … doesn't perform well" (`usc_miniradar.txt`).
6. **A bare LNB sees heat, not the Sun.** Readings were "ground +68.3dBµV, sky +64.4dBµV", and "Pointing at the Sun will not cause any noticeable enhancement … only a (parabolic) reflector" (`koeppen_ku_band_ESAreport2.txt` App. A.1). A 68 cm dish gives a beam of about 3.5° (`everyday_radio_telescope_1601.02982.txt`).

## 3. Recommendation
- **Cheapest build:** keep the XIAO ESP32-C5 and run ESP-SDR on it in burst mode with manual gain. For each pointing, log band power and the gain index. This gives spectrum-resolved 2.4/5 GHz maps of any emitter for 0 PLN extra. Then add beam deconvolution on the host, starting with CLEAN, using a beam pattern you measure yourself.
- **Optional add-ons:**
  - LNB + satfinder (about 80 PLN) as a swappable Ku-band "thermal" payload.
  - ESPARGOS One (€350 + VAT) for anyone who wants real coherent Wi-Fi imaging.
- **Skip:**
  - A DIY two-ESP32 coherent holography rig: it needs a clock modification, phase-reference distribution and calibration, which is research-grade.
  - CSI-phase AoA on a single ESP32: the phase is random per packet.
  - The hydrogen-line payload: the antenna is too big for the head.
- **My untested idea, not supported by any source:** high-band LNB output (1100–2150 MHz) overlaps the S3's measured 1850–2200 MHz reception. An LNB feeding the S3 through a bias-tee/DC block might work as a Ku-band spectrum radiometer without a satfinder.

**Single most valuable first experiment:** put one ESP32 beacon at a fixed position and scan it on an az/el grid. Record ESP-SDR manual-gain band power and ordinary RSSI side by side. This measures the beam pattern and shows which reading is more repeatable. Then add a second beacon closer than the beamwidth and test whether CLEAN separates the two.

## 4. Could not retrieve / unverified
- Ubicarse (DOI 10.1145/2639108.2639142): closed access. Only SpotFi's secondary "0.3–0.4 m" statement is used.
- Högbom 1974 CLEAN (A&AS 15, 417): only a scanned image with no text; not read.
- Not fetched:
  - Borealis (MobiCom 2011)
  - IUCAA small-radio-telescope PDF
  - SWAN (MobiCom 2018)
  - ESP32 CSI Tool (WoWMoM 2020)
  - LTEye
- The brief's arXiv id 1608.06920 is wrong. The correct id is 1612.03194, and that is what was read.
- Not checked:
  - Whether the VA0314 has an analog output
  - The ESPARGOS price in PLN
  - Polish prices for an RTL-SDR, SAWbird, directional antennas and RF switches
  - ESP-SDR's power repeatability as an RSSI substitute (nobody has published a measurement)

Files are in /home/adam/ŻYCIE/VIBECODING/RadioMicroscope/papers/imaging-science/: 21 sources (PDFs and saved docs) and their extracted .txt, plus EXTRACTS.md and shop_prices_2026-11-11.txt.
