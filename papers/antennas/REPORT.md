# Antenna choice for the radio microscope — report (2026-11-11)

Derived from `EXTRACTS.md` in this folder. The extracts govern if this report disagrees with them. Section
codes (C18, D11 …) point to entries there. PLN conversions use €1 ≈ 4.25 PLN and £1 ≈ 4.9 PLN, which are my
own assumed rates and not from any source. The $1 ≈ 3.9 PLN rate is the one implied by elecena (C20).

## 1. Recommendation

- **Buy first: Maple Wireless 2.4G 9 dBi patch** (C18, C19). 9 dBi; HPBW 60° (H) × 65° (E); linear vertical;
  90×80×10 mm; 17 g (ht-dron) or 33 g (Rotorama), so the weight is in conflict but under 40 g either way;
  Rotorama €13.19 (≈56 PLN), RP-SMA, in stock; ht-dron 73 PLN, SMA or RP-SMA, out of stock. **Claimed**
  (vendor). Add a 10 cm U.FL–SMA RF1.13 pigtail (rf-connectors.pl 13.90 PLN, C27) whose connector matches the
  antenna's (SMA or RP-SMA). Why this one: it is the cheapest in-stock directional antenna under 40 g. Its
  linear polarisation avoids the fixed 3 dB LP/CP loss against linear transmitters (A8). Its beam is wide
  enough that a 10° grid is already oversampled (§3). It also covers its whole band, while every light 5 GHz
  option covers only half of that band.
- **Best 5 GHz: GEPRC Triple Feed Patch-1, SMA** (C1, C3, C4). 9.4 dBi; 55°×55°; circular (CP); 20 g; SMA male;
  81 PLN at ht-dron, in stock; antenna dimensions not published. It covers **5.47–6.13 GHz, which is the
  upper half only (channels 100–165)**; lower channels 36–64 are not covered. GEPRC's figures are
  **simulated**. The same design was **measured** by its designer at 9.3 dBi, 55° and 74 % efficiency (C4);
  GEPRC's own build was not measured independently. No light antenna found covers 5.18–5.32 GHz.
- **Best single antenna for both bands: Alfa APA-M25** (C24). 8 dBi at 2.4 GHz and 10 dBi at 5 GHz;
  2.4–2.5 and 5.150–5.875 GHz (**both 5 GHz halves**); linear vertical; 66° H / 16° V, band not stated. The
  16° figure does not fit 10 dBi: the 41253 rule (A1) would give about 16 dBi. 72 g; 167.3×66×18 mm; RP-SMA
  male; £14.24 (≈70 PLN) at wifi-stock.co.uk; 75.99 zł on Kaufland is [S] only. **Claimed**. It breaks the
  40 g target.
- **Best make-it-yourself: Baert Triple Feed Patch-1**, CC BY-SA 4.0 with Gerbers published (C4, D12).
  9.3 dBi measured; 55°; CP; upper 5 GHz half only. It is two 2-layer **1.0 mm** FR4 boards (≤5×5 cm and
  ≤10×10 cm) spaced 4 mm, with an SMT SMA. JLCPCB lists boards "From $2.00 / 5 pcs" (D4). Shipping to Poland
  could not be retrieved (D5). The EU now adds €3 per HS code, €2 handling, VAT and a carrier fee (DHL
  minimum 69 PLN unless DDP) (D6). For one antenna, buying the GEPRC is probably no dearer; that is my
  inference. **Dual-band DIY:** Dou et al. 2021 (CC BY; B10, D16). **Measured** 6.55/8.1 dBi; 2.33–2.51 and
  5.09–5.92 GHz; E ~60°, H ~120°; linear; 69×50×1.6 mm FR4; weight not given. You must redraw it from
  Table 1. At Aisler, 3 boards cost €18.93 net, ≈€23.3 gross (≈99 PLN), with free EU shipping and VAT
  charged at checkout (D1, D2, C25).

## 2. Comparison

| Antenna | Band(s) | dBi | HPBW | Pol. | Weight | Size mm | Price / shop | Evidence | Tier |
|---|---|---|---|---|---|---|---|---|---|
| Maple 2.4G patch | 2.4 | 9 | 60°×65° | lin V | 17/33 g | 90×80×10 | €13.19 Rotorama; 73 PLN ht-dron | claimed | [V] |
| Seeed 318020070 | 2.35–2.45 | 8 | "40° lobe" | – | – | – | 65.22 PLN elecena (Seeed) | claimed | [V] |
| TP-Link ANT2409A | 2.4 | 9 | 60°×76° | lin V | – | 120×120×40 | no PL price (EOL [S]) | claimed | [V] |
| Dipol ATK-P1 | 2.4 | 8 | 70°×70° | H/V | 0.3 kg w/ 5 m cable | 120×120×20 | €22.27 dipol | measured (chamber) | [V] |
| WA5VJB PCB Yagi | 2.40–2.45 | 10 | – | – | – | – | $8 + intl. post | claimed | [V] |
| GEPRC TFP-1 | 5.47–6.13 | 9.4 | 55°×55° | CP | 20 g | – | 81 PLN ht-dron | simulated; design measured | [V] |
| Foxeer Echo 2 | 5.5–6.0 | 9 | 84.7° (not −3 dB) | RHCP/LHCP | 8 g | 40×22 | 121 PLN ht-dron (OOS); £19.90 | claimed | [V] |
| Maple 5.8 patch | 5.8 | 8.5 | 75° | RHCP | 16 g | 44×10 | €15.59 Rotorama | claimed | [V] |
| Lumenier AXII | 5.8 (220 MHz) | 8.4 dBic | 76° | RHCP | 10 g | 35×35×9 | $32.49 WREKD | claimed | [V] |
| GEPRC TFP array | 5.8 | 14.4 | 30°×30° | CP | – | ⌀150 | 126 PLN ht-dron | simulated; design meas. 14.0 | [V] |
| Cyberteam SkyEter13 | 5.45–5.75 | 13 | 33°×33° | V or H | 80 g | 82×82×12 | 7.37 zł (clearance?) | claimed | [V] |
| Alfa APA-M25 | 2.4 + 5.15–5.875 | 8/10 | 66°×16°? | lin V | 72 g | 167×66×18 | £14.24; 75.99 zł Kaufland | claimed | [V]/[S] |
| Tupavco TP542 | 2.4 + 5 | 10/14.5 meas. | – | – | – | 5″×9″ | – | measured (ATL) | [V] |
| DIY Baert TFP-1 | ~5.4–6.2 | 9.3 | 55° | CP | ~20 g | ≤100×100 | fab + fees (D4–D6) | measured | [V] |
| DIY Dou 2021 | 2.33–2.51 + 5.09–5.92 | 6.55/8.1 | ~60°×120° | lin | – | 69×50 | ≈€23 / 3 boards Aisler | measured | [V] |
| DIY TI DN034 Yagi | 2.13–2.62 | 7.2 | 64–82° | – | – | 100×150 | 4-layer fab | measured | [V] |

## 3. Beamwidth guidance

**Gain and beamwidth.** D ≈ 41253/(θ₁θ₂), or 32400/(θ₁θ₂) for planar arrays (A1). Gain = directivity ×
efficiency, so the real gain for a given beam is lower (A1, B15).

| dBi | 6 | 8 | 10 | 12 | 14 | 17 |
|---|---|---|---|---|---|---|
| HPBW (41253 / 32400) | 102°/90° | 81°/72° | 64°/57° | 51°/45° | 41°/36° | 29°/25° |

**Samples per beam.**
- Nyquist spacing is at most FWHM/2 (A4), or ≈0.4 beamwidth (A7).
- Nyquist is about 2.4 points per FWHM. Keeping beam broadening under 1 % needs at least 4.5 points (A6).
- A5 advises oversampling about 3× along the slew.
- A 5° grid therefore suits a 12–22° beam, and a 10° grid suits a 24–45° beam.
- The light antennas above have 55–65° beams. On a 10° grid that is already 5.5–6.5 points per beam.
  Resolution is about one HPBW (A3), so a finer grid does not resolve more.
- The narrowest near-light option is the 30° TFP array (weight not given).
- For tracking: G/G₀ = exp[−4 ln2 (ρ/θ)²] (A3). The signal is 1 dB down at about 0.29 θ, roughly 16° off
  axis for a 55° beam (my arithmetic).

**Indoor multipath.**
- Omnidirectional antennas give larger delay spread (A12).
- Sidelobes leak bright sources into nearby map cells (A4).
- Front-to-back ratio rose from 9 to 13 to 22 dB as the ground plane grew from ≈0.06 to 0.12 to 0.25 λ
  (B18).

**Polarisation.**
- Linear-to-circular costs 3 dB at any rotation, while crossed linear antennas can null completely (A8, A10).
- AP antennas are often tilted (A14). A linear antenna will therefore record the transmitter's tilt as
  apparent intensity.
- CP receive against linear transmitters reduced fading by up to 3.5 dB in line of sight and 1.5 dB out of
  it (868 MHz, A13), because odd reflections reverse handedness.
- At 5.8 GHz indoors, depolarisation is strong and CP-to-CP links showed no advantage (A12).
- For this instrument: CP gives readings that do not depend on tilt, at a fixed 3 dB cost. Linear gives up
  to 3 dB more when it is aligned.

## 4. Feed and connector losses

| Item | 2.4 GHz | 5.8 GHz | Source |
|---|---|---|---|
| 10 cm 1.13 mm coax | 0.32–0.34 dB | ≈0.53–0.54 dB | D27, D28 |
| 10 cm RG178 | 0.27 dB | ≈0.46–0.47 dB | D29, D30 (Pasternack RG178B/U: 3 GHz max, D31) |
| SMA connector, max | ≤0.07–0.14 dB | ≤0.17–0.35 dB | 0.03·f (D34) to 0.06·f (D35) |
| U.FL mismatch (VSWR ≤1.3 / ≤1.4) | ≤0.08 dB | ≤0.12 dB | D32 (dB is my arithmetic) |
| HMC849 SPDT switch (two-antenna option) | 1.0 dB typ | 1.8 dB typ | B14 |
| FR4 board loss | 0.7–3.3 dB | 0.4–1.6 dB | B1, B10, B16, C4, D10, D11 |

- A 10 cm 1.13 mm pigtail with an SMA costs about 0.5 dB at 2.4 GHz and 0.9 dB at 5.8 GHz.
- FR4 Df is 0.021 at 2 GHz and 0.025 at 5 GHz (D9). Etching the patch on FR4 costs the most: 3.3 dB at
  2.45 GHz, simulated (D11). Air-spaced patches lose 0.4–1.3 dB (D10, C4).
- U.FL is rated for **30 matings** (D32, D33); SMA for 500 (D34, D35). Mate the U.FL once and strain-relieve
  the pigtail.
- **Rotary joint: not needed.** With the radio riding on the head, no RF crosses an axis; only power and data
  do (my inference). A joint would add 0.3 dB, 9.4 g and a $226.99-class price (A20, A21), or 0.9–1.8 dB and
  0.1 kg (A22).

## 5. Quote check

I checked 40 quotes from A, B and C, including JSON-LD prices, against the saved files. All 40 match. The
only differences are pdftotext line and column breaks, the "observaAons" ligature already noted in A4, and
one apostrophe. I also checked 41 new part-D quotes and corrected one capitalisation slip in my own text.
Inconsistencies inside the sources themselves:
- Maple weight: 17 g vs 33 g.
- Alfa beamwidth vs gain.
- B13's HPBW (already flagged).
- Aisler's worked example uses 0.051 €/cm² while its table gives 0.067 (D1).
- ht-dron calls the TFP-1 figures simulated on one page and "very similar" to measurements on the other
  (C1/C2).

## 6. Could not retrieve / unverified

- **PCB shipping to Poland:** JLCPCB/PCBWay prices are calculated at checkout only (jlcpcb.com/help/article/shipping-costs,
  pcbway.com/helpcenter/shipping/). Rotorama's shipping cost to Poland was not fetched. The current Elecrow
  price was not fetched.
- **Blocked or [S] only:** Kaufland, getfpv, Alfa (alfa.com.tw, 429), Delock, AliExpress, Rokland,
  sapsan-sklep (C).
- **A, B and D items:**
  - Cisco antenna white papers (403)
  - Selvan PIER 57 (jpier.org id=0507262)
  - Kajiwara 1995 and Manabe 1996 (IEEE)
  - Hindawi IJAP doi:10.1155/2022/4765008
  - ADI HMC849A datasheet
  - Skyworks switch datasheets
  - DRDO helix
  - TI swrr074 licence
  - Pasternack/DigiKey rotary-joint prices
- **Unpublished:**
  - GEPRC TFP-1 antenna dimensions
  - WA5VJB sizes, weights and beamwidths
  - Weight of the Dou 2021 board
  - U.FL insertion loss (graph only)
  - Any measured statistic of AP or phone polarisation (A)
