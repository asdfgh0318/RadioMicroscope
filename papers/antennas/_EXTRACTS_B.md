# Extracts — fork B (Q2 DIY designs, Q3 dual-band / RF switch)

All quotes verbatim from the local files named. Files in this directory, prefix `B_`.
Page numbers are PDF page numbers unless the document prints its own.

---

## B1. TI Application Note DN034 — "2.4 GHz YAGI PCB Antenna" (SWRA350, 2010)
- URL: https://www.ti.com/lit/an/swra350/swra350.pdf
- Local: B_TI_DN034_swra350.pdf / .txt
- Evidence: MEASURED (OTA chamber, return loss).

> "The antenna described in this document is a Yagi-Uda commonly named as Yagi and is a directional antenna with approximately 7dBi gain. Impedance of the antenna input is 50 Ω" (p.2, §3)

> "the ground plane, printed on all four layers of the PCB, acts as the reflector." (p.2, §3)

> "Total area of the antenna is 100 mm by 150 mm (4" by 6"). The antenna design is based upon 2 layers (Antenna Top & Antenna Bottom) of a 4-layer standard, FR4, PCB, 1.6mm (62 mils) stack-up" (p.3, §3.1)

> "Bandwidth = 2623 MHz(Marker 5) - 2126 MHz(Marker 1) = 497 MHz" (p.4, §4.1.1, -10 dB return loss)

> "The gain at 2400.000 MHz was recorded at 7.22 dBi." (p.6, §4.2)

Table 1 "OTA Test Results for 2400 MHz, 2440 MHz & 2480 MHz" (p.7, §4.3), verbatim rows:
> "Directivity 7.92 dBi 8.62 dBi 9.48 dBi"
> "Efficiency 85.20 % 71.70 % 58.24 %"
> "Gain 7.22 dBi 7.18 dBi 7.13 dBi"
> "Front/Back Ratio 14.16 15.77 15.25"
> "ThetaBW 82.1 deg 76.0 deg 63.6 deg"

> "As can be seen from Table 1, the gain of the antenna is similar across the whole 2.4 GHz ISM band. The efficiency is highest at 2400 MHz and as the frequency increases the efficiency drops slightly." (p.7)

Note (mine): the efficiency figures (58-85 %) are a direct measurement of FR4/feed loss on a 2.4 GHz printed Yagi; gerbers are "swrr074.zip" (ref [2], p.9).

---

## B2. Kent Electronics (WA5VJB) PCB antenna datasheets and price list
- Price list URL: https://www.wa5vjb.com/Prices-Square.html — Local: B_WA5VJB_page_Prices-Square.txt
- Product pages: https://www.wa5vjb.com/products1.html (log periodic), products5.html (UWB/Vivaldi), products6.html (patch arrays) — Local: B_WA5VJB_page_products1.txt, _products5.txt, _products6.txt
- Datasheets (https://www.wa5vjb.com/pcb-pdfs/<name>.pdf): B_WA5VJB_LP2TO11.pdf, B_WA5VJB_LP8565A2.pdf, B_WA5VJB_Yagi2400.pdf, B_WA5VJB_QuadPatch2400.pdf, B_WA5VJB_Viv1.5to15.pdf, B_WA5VJB_PCBPD.pdf, B_WA5VJB_5800MHzPatchArrays.pdf (return-loss plots only), B_WA5VJB_UWB_700M26Gdatasheet.pdf and B_WA5VJB_Wheels2400.pdf (image-only, no text layer).
- Evidence: gains are the designer's stated "Typical/Average Gain" on one-page datasheets; return-loss plots are measured (VNA / spectrum-analyser screenshots). No radiation patterns or beamwidths are published → treat gain as CLAIMED-by-designer (designer is a recognised antenna-measurement specialist, but no pattern data in the file).

Prices (B_WA5VJB_page_Prices-Square.txt, verbatim):
> "2400 -2450 MHz Yagi Antenna $8" · "850-6500 MHz Log Periodic Antenna $24" · "2-11 GHz Log Periodic Antenna $10" · "2400 MHz Quad Patch Array Antenna $12" · "5800 MHz 2 Patch Array Antenna $6" · "5800 MHz 4 Patch Array Antenna $8" · "5 - 18 GHz Vivaldi Antenna $8" · "1.5 - 15 GHz Vivaldi Antenna $14" · "2 - 26 GHz Planar Antenna $9"
> "SMA - Female Connector board-mounted $15" · "Prices Include First Class Domestic Shipping & Handling. International shipments incur additional shipping costs."

2-11 GHz LPDA (B_WA5VJB_LP2TO11.txt):
> "2 - 11 GHz PCB LP" · "Uses: EMI Work Broad Band Dish Feed Spectrum Analyzis SDR's" · "Average Gain 6 dBi" · "Typical Antenna Factors: 2 GHz 30 6 GHz 40 3 GHz 33 10 GHz 45"
> ".141 semi-rigid is not recommended, it's larger diameter unbalances the antenna above 6 GHz."
Product page (B_WA5VJB_page_products1.txt): "2100 - 11000 MHz: (2.1 - 11 GHz) This log periodic printed circuit board antenna gives great performance from 2100 - 11000 MHz. This range includes wireless networking at 2.4GHz (802.11b/g) and 5.8GHz (802.11a)."

850-6500 MHz LPDA (B_WA5VJB_LP8565A2.txt):
> "134 mm 142 mm" (outline dimension labels) · "Typical Forward Gain: 6 dBi" · "Typical Antenna Factors: 900 MHz 24.0 ... 2.4 GHz 32.0 ... 6 GHz 40"

2400-2450 MHz 5-element PCB Yagi (B_WA5VJB_Yagi2400.txt):
> "2400-2450 MHz 5 Element PCB Yagi" · "Uses: WiFi, 2.4 GHz Video, Beacons" · "10-11 dBi Max Signal" · "Average Gain 10 dBi"

2400-2480 MHz Quad Patch (B_WA5VJB_QuadPatch2400.txt):
> "Broad Band 2400-2480 MHz Quad Patch" · "Vertical Polarization As Shown" · "Average Gain 11-12 dBi" · "Size: 97 x 153 mm 6.0 x 3.8"" · "DC Grounded for ESD and Static Protection."

1.5-15 GHz Vivaldi (B_WA5VJB_Viv1.5to15.txt):
> "1.5-15 GHz Vivaldi Usable .5-20 GHz" · "Vert Polarization As Shown" · "Typical Gain 8-10 dBi" · "Uses: Dish Feed UWB Bench Work"
Product page (B_WA5VJB_page_products5.txt): "1.5 GHz - 15 GHz Vivaldi: This compact antenna provides consistent gain across an incredible wide frequency range, including all wifi networks and cell phone bands."

2-26 GHz planar disk (B_WA5VJB_PCBPD.txt) — for comparison, omnidirectional:
> "2-26 GHz PlanarDisk OMNI-Directional" · "Typical Gain 2-5 dBi"

---

## B3. Trevor Marshall — "BiQuad 802.11b Antenna" (web page, ©1995-2001)
- URL: http://www.trevormarshall.com/biquad.htm
- Local: B_TrevorMarshall_biquad.txt (page text)
- Evidence: gain CLAIMED (no measured pattern on the page; page says "Look at NEC2.org for information on simulating the performance of the stand-alone Biquad"). Dimensions are published.

> "BiQuad 802.11b Antenna 11dBi, wide band"
> "I used Printed Circuit board scraps for the 110 x 110 mm reflector ... If you are making a stand-alone antenna, rather than a feed, you will get better gain from a reflector 123 x 123 mm"
> "The reflector's 'lips' are 30 mm high ... The lips cut down radiation from the rear lobes of the biquad by about 6 dB The best SWR is obtained when the biquad loop is about 15mm above the ground plane"
> "To make the element take a piece of 1.2mm bare or enamelled copper wire exactly 244 mm long. ... The widths of the two quad elements will be approximately 30.5mm, from wire center to wire center."
> "The feed is oriented for vertical polarization in this photo. To make it horizontal merely rotate the feed by 90 degrees."
> "That's all there is to it, folks -- you now have a dish with 27-31 dBi of gain" (as a Primestar dish feed)

---

## B4. K7JLT, "WiFi Antennas" (SEA-PAC 2015 seminar slides) — soup-can (cantenna) and horn
- URL: https://seapac.org/seminars/2015/SEA-PAC2015-k7ijt-Wifi_Antennas.pdf
- Local: B_SEAPAC2015_k7ijt_wifi_antennas.pdf / .txt
- Evidence: author-MEASURED gain and F/B (informal amateur range; no pattern plots with method).

> "HSMM Soup Can Gain Antenna 11 ⅜ Inch Length or Longer 3 ¾ Inch From Inside of Can ... Soup Can 3.02 Inch Inside Diameter ... N Connector with probe Probe is 15/16 Inch Long" (slide 9)
> "Gain has been measured to be 8 to 9 dBi 6 or 7 dB better than router dipole Front to Back Ratio ≈15 dB" (slide 16, reassembled from the slide layout)
> "A circular funnel made out of sheet metal was added to the recommended length of cans for more gain per the article." (slide 19)
> "Gain has been measured at 11 to 12 dBi with better than 20 dB front to back ratio. ≈ 10 dB better gain than router dipole" (slide 21, can + funnel horn)
> "Lowest Frequency Supported – λL = 1.706 * Inside Diameter ... Next Mode Supported – λH = 1.3065 * Inside Diameter ... Cylinder Length = 0.75 * Lg Probe Location= 0.25 * Lg" (slides 25-26, "Calculations From QEX Article")
> "= Total $5 to $11" (slide 17, cost)

## B5. Khan & Spaulding, "Building the largest cantenna in Kansas", ASEE 2008 (AC 2008-820)
- URL: https://peer.asee.org/3516.pdf
- Local: B_ASEE3516_cantenna.pdf / .txt
> "This antenna is based on smaller Wi-Fi antennas commonly referred to as cantennas (gain of about 10 dBi). The smaller version is made with a single can (3-4 inches) in diameter" (p.1, abstract)
> "waveguide that permits only the dominant TE11 mode ... that exceeds ¾ of the guide wavelength for the TE11 mode at 2.4 GHz. The feed is placed" (p.2-3)
> "A standard cantenna (Figure 6) of known gain (10 dBi) was placed in a location" (gain-by-substitution procedure, p.5) — the 10 dBi for the small cantenna is ASSUMED, not measured, in this paper.

---

## B6. Helical (axial-mode): Kraus empirical rules, quoted in I. Ghoreishian, "The Spiro-Helical Antenna", M.S. thesis, Virginia Tech, 1999
- URL: https://vtechworks.lib.vt.edu/server/api/core/bitstreams/ffb653b2-1f5e-4a6c-b675-dd468585cb9d/content
- Local: B_VT_helix_thesis.pdf / .txt
> "For axial-mode helical antennas satisfying the conditions 12° < α < 15°, n > 3, and 3/4 < Cλ < 4/3, Kraus has developed empirical formulae for gain, input impedance, axial ratio, and half power beamwidth [1]. The empirical gain formula is given as G = 15 Cλ² nSλ, (2.8) where Cλ = C/λ and Sλ = S/λ are normalized circumference and spacing between turns" (§2.1.4, p.9; fraction layout reconstructed from pdftotext)
> "HPBW = 52 / (Cλ √(nSλ)) degrees (2.10) by Kraus" (§2.1.4, p.11; square-root sign lost in text extraction, formula as printed in the PDF)
> "Kraus's empirical formula for input impedance is R = 140 Cλ Ω. (2.12)" (p.11)
> "The equation for the axial ratio developed by Kraus is [1] AR = (2n + 1)/2n. (2.13)" (p.11-12)
> "the HPBW data can be used to obtain a rough estimate of gain using the relationship G = 41,253 / (HPBW)²" (§5.2.2, p.52)
> MEASURED (spiro-helix, a compact variant, ~1.5-2.5 GHz): "when the number of turns is 10, a gain of 11-14 dB, a boresight axial ratio of less than 3 dB, and a half-power beamwidth of about 40 degrees are achieved over a 30% bandwidth. The side-lobe level for most cases examined is better than 10 dB below the main beam." (Abstract) "Measured far-field patterns are presented over a wide range of frequencies. The measured and computed radiation patterns are in good agreement." (Abstract)

## B7. D. Emerson (NRAO), "The Gain of the Axial-Mode Helix Antenna", ARRL Antenna Compendium Vol.4, 1995 (author's web copy)
- URL: https://www.qsl.net/aa7fv/helix.htm
- Local: B_AA7FV_Emerson_helix_gain.txt
- Evidence: NEC-2 SIMULATION of ~10,000 helices compared with published measurements.
> "The maximum possible gains are up to 4 or 5 dB lower than those derived from the original Kraus formula for gain. The maximum gain increases much more slowly with increasing antenna length than the simple Kraus formula would predict."
> "An empirical expression for the maximum possible gain Gmax of the helical antenna as a function of its length L in wavelengths is: Gmax(dB) = 10.25 + 1.22 L - 0.0726 L^2 This expression is only valid for lengths L between 2 and 7 wavelengths."
> "most amateur literature, and even many standard textbooks, quote gains which are far too optimistic."

## B8. Paul et al., "Design And Simulation of a Monofilar Helical Antenna for 5G and Beyond Applications", IEEE M&N 2024, DOI 10.1109/MN60932.2024.10615465 (NSF PAR copy)
- URL: https://par.nsf.gov/servlets/purl/10552858
- Local: B_NSF10552858_helix58.pdf / .txt
- Evidence: SIMULATED only (CST).
> Table of dimensions (p.2): "Diameter (D) 16.46 · No. of turns (N) 10 · Spacing between turns (S) 12.93 · Height of helix (H) 129.31 · Pitching angle (α) 14° · Wire diameter (d) 2 · Ground plane (in diameter) 64" (mm)
> "The resonance frequency was specifically set at 5.8 GHz." (Abstract) "From above Fig.9(a) the value of gain is 11.53 dB." (p.3)

---

## B9. Pereira, Costanzo, Masotti, Carvalho, "3D-Printed Smooth-Walled Conical Horn Antennas: Manufacturing and Quasioptical Analysis", URSI GASS 2023
- URL: https://www.ursi.org/proceedings/procGA23/papers/YSASummaryPaperPereiraRicardoC.pdf (the 2021.ursi.org mirror has a TLS-name mismatch)
- Local: B_URSI2021_3Dprinted_horn_5p8.pdf / .txt
- Evidence: MEASURED gain (anechoic chamber), PLA + copper tape.
> "This paper presents two 3D printed smooth-walled conical horn antennas used in one such system, at 5.8 GHz. This method results in a high performance, low-cost and lightweight antenna." (Abstract)
> "[7] includes two different methods for applying the metal layer, through copper tape and copper paint spray, with the former achieving a much higher conductivity, reason for which this method is the one used in the present study." (§1)
> Table 1 (cm): "a Aperture Radius 10.893 · Rh Slant Length 30.587 · Lh Horn Length 28.582 · lw Waveguide Length 5.224"
> Table 2: "Gdesign Intended Gain value 19.000 · Gsim Gain from simulation 19.600 · Gmeas Measured Gain 19.064 19.064 · S11 Measured Return Loss -30.934 -18.357"
> "the fast cooling of the PLA filament ... forced the deformed pieces into place, even leading to some cracks in the plastic." (§4)
Note (mine): a ~19 dBi horn at 5.8 GHz is ~22 cm aperture × ~29 cm long — far too big for a light gimbal; no weight given.

---

## B10. Dou, Dong, Lin, Cai, Liu, "A Low Profile Dual-Band High Gain Directional Antenna for Anti-Interference WLAN Station Applications", Appl. Sci. 2021, 11, 2007, doi:10.3390/app11052007
- URL: https://mdpi-res.com/d_attachment/applsci/applsci-11-02007/article_deploy/applsci-11-02007.pdf
- Local: B_MDPI_applsci-11-02007_dualband_directional.pdf / .txt
- Evidence: MEASURED (S11, patterns, gain, efficiency).
> "The measured impedance bandwidth of the proposed antenna is 180 MHz (2.33–2.51 GHz) and 830 MHz (5.09–5.92 GHz) ... with the peak gain of 6.55 dBi in the lower frequency band and 8.1 dBi in the higher frequency band. The measured antenna efficiency is 70% at 2.4 GHz and 84.5% at 5.5 GHz. The proposed dual-band WLAN station antenna is designed on a FR4 substrate with overall dimensions of 69 mm × 50 mm × 1.6 mm." (Abstract, p.1)
> "fabricated on a 50 mm × 69 mm FR4 substrate with relative permittivity εr of 4.4, loss tan δ of 0.02, and thickness of 1.6 mm." (§2, p.3)
> "The cross-polarization for both the E-plane (xoz plane) and the H-plane (yoz plane) are less than −20 dB. ... The beamwidth of the E-plane is about 60°, while the beamwidth of the H-plane is about 120°." (§3, p.5)
Note (mine): the 5.8 GHz end of the measured band is 5.92 GHz, so 5.18-5.8 GHz is covered; the "about 60°/120°" beamwidths are read from the plots by the authors and are given for both bands together. No F/B number is stated in the text.

## B11. Ren et al., "An Ultra-Wideband Vivaldi Antenna System for Long-Distance Electromagnetic Detection", Appl. Sci. 2022, 12, 528
- URL: https://mdpi-res.com/d_attachment/applsci/applsci-12-00528/article_deploy/applsci-12-00528.pdf
- Local: B_MDPI_applsci-12-00528_vivaldi.pdf / .txt
- Evidence: wide-beam Vivaldi MEASURED; narrow-beam Vivaldi SIMULATED only.
> "is fabricated on a 150 × 150 × 1.6 mm FR4 substrate with a dielectric constant of 4.3." (§2.1, p.3)
> "The antenna is a wide beam antenna and the half-power beamwidth (HPBW) can be maintained above 90° in the frequency range 2.5–5 GHz, and the maximum beam width is 122°. ... the gain is shown in Figure 2b, which is greater than 3.26 dBi" (§2.1, p.3-4)
> Table 2 "HPBW (Measured)/° ... 2.5 GHz 108° · 3 GHz 122° · 3.5 GHz 109° · 4 GHz 90° · 5 GHz 95° · 6 GHz 86°" (p.4)
> Table 4 (simulated, narrow-beam design, 82 × 55 mm, 2.5-8.5 GHz): "65.9° 65.2° 59.4° 55.4° 44° 46.7° 66.2°" at "2 GHz 3 GHz 4 GHz 5 GHz 6 GHz 7 GHz 8 GHz" (p.7)
> Same table, other published Vivaldis: "[24] 120 × 90 2–5 GHz 130 ‐ 75 65" (HPBW at 2/3/4/5 GHz) (p.7)
Note (mine): this is the evidence that a single Vivaldi's beamwidth changes by ~1.3-2× across 2-6 GHz — the map resolution would differ between the 2.4 and 5 GHz scans.

## B12. Abdulhameed & Kubík, "Design a Compact Printed Log-Periodic Biconical Dipole Array Antenna for EMC Measurements", Electronics 2022, 11, 2877
- URL: https://dspace5.zcu.cz/bitstream/11025/49824/1/Kubik_electronics-11-02877-v2.pdf
- Local: B_MDPI_electronics-11-02877_printed_LPDA_0p5-6GHz.pdf / .txt
- Evidence: MEASURED (EMC chamber, patterns and realized gain).
> "broad bandwidth of 5.5 GHz (from 0.5 GHz to 6 GHz). This structure comprises 12 dipole elements with a compact size of 170 × 160 × 1.6 mm, reflecting low fluctuations gain of about (4.6–7) dBi" (Abstract)
> "The back lobe of the azimuth plane is prominent at low frequencies and decreases gradually with high frequencies. The radiation pattern deterioration is clearly observed at high-frequency bands in both E-field and H-field presented in Figures 15 and 16" (§5.3, p.12)
> "The proposed structure offered linear polarization with more than 20 dB AR except for some frequencies" (§5.4, p.13)

## B13. Herudin, Amir, Alimuddin — "Rancang Bangun Antena Mikrostrip Biquad Ganda untuk Aplikasi Wi-Fi" (double-biquad microstrip on FR4), Jurnal Nasional Teknik Elektro Vol.3 No.1, March 2014
- URL: https://jnte.ft.unand.ac.id/index.php/jnte/article/download/54/51 (DOAJ record b3089a7ae8f04d81961dce5d288251da)
- Local: B_JNTE2014_double_biquad_microstrip.pdf / .txt
- Evidence: MEASURED S11/VSWR and pattern HPBW; NO measured gain reported.
> "In this study designed a double biquad microstrip antenna using FR4 material ( epoxy ) . The double biquad microstrip antenna works at a frequency of 2.4 GHz ˗ 2.5 GHz ... has a 555 MHz bandwidth with a value of 1.135 VSWR and return loss is -25.23 dB. The resulting vertical radiation pattern has a HPBW ( Half Power Beamwidth ) about 41̊ and horizontal radiation pattern has a HPBW about 35̊" (English abstract, p.1)
> "Ukuran antena mikrostrip biquad ganda secara keseluruhan adalah 19 cm × 19 cm dan tebal antena 1,64 mm." (= overall size 19 cm × 19 cm, thickness 1.64 mm; p.6)
Note (mine): 41°×35° would imply ~14-15 dBi by the 41253/(θφ) rule, which is implausibly high for a lossy FR4 double biquad; treat the HPBW figures with caution.

---

## B14. RF switch datasheets (for the "two antennas + SPDT" option)
### HMC849ALP4CE (Hittite/ADI), v00.1013 — mirror copy
- URL: https://datasheet.chipsfind.com/HMC849ALP4CE-605496.pdf (official analog.com PDF did not download: connection refused to automated client)
- Local: B_HMC849ALP4CE_datasheet_mirror_chipsfind.pdf / .txt
> "HIGH ISOLATION SPDT NON-REFLECTIVE SWITCH, DC - 6 GHz" · "16 Lead 4x4 mm QFN Package: 16 mm²" · "Single Positive Control: 0/+3V to +5V" (p.1)
> Electrical Specifications (Min/Typ/Max): "Insertion Loss DC - 2.0 GHz 0.9 1.3 · 2.0 - 4.0 GHz 1.0 1.5 · 4.0 - 6.0 GHz 1.8 2.5" dB; "Isolation (RFC to RF1/RF2) DC - 2.0 GHz 53 60 · 2.0 - 4.0 GHz 48 56 · 4.0 - 6.0 GHz 35 50" dB (Min, Typ) (p.1)
### PE4259 (pSemi UltraCMOS SPDT)
- URL: https://www.psemi.com/pdf/datasheets/pe4259ds.pdf
- Local: B_pSemi_PE4259_datasheet.pdf / .txt
> "UltraCMOS® High-power SPDT RF Switch, 10 MHz–3.0 GHz" · "Low insertion loss: 0.35 dB at 1000 MHz 0.5 dB at 2000 MHz" · "Isolation: 30 dB at 1000 MHz" (p.1)
Note (mine): PE4259 is rated only to 3.0 GHz, so it is NOT usable for the 5 GHz antenna; a DC-6 GHz part such as HMC849 is needed, costing ~1.0 dB at 2.4 GHz and ~1.8 dB typ (2.5 dB max) at 5-6 GHz.

---

## B15. Antoniazzi (IW2ACD) & Arecco (IK2WAQ), "Measuring 2.4 GHz Helix Antennas", QEX May/June 2004 (archive.org copy)
- URL: https://archive.org/download/fea_Measuring_2.4_GHz_Helix_Antennas/Measuring%202.4%20GHz%20Helix%20Antennas.pdf
- Local: B_archive_Measuring_2p4GHz_Helix_Antennas.pdf / .txt
- Evidence: MEASURED (HPBW, gain) + NEC simulation.
> "we have analyzed two different antennas (Fig 5). One is a simple unit of five turns (gain = 12 dBi) and one is 16.7 turn with 14.5 dBi gain." (p.17)
> "Spacing between turns (0.24 λ or 30 mm at 2.4 GHz for our helices)." (p.18) · ground plane "(125×125 mm, λ at 2.4 GHz)" (p.18)
> Table 2 "Helix radiation angles, efficiency and gain — 5.0 Turns, L = 150 mm ... (degrees) 41 42 43 · 16.7 Turns, L = 500 mm ... 24 25 26" (p.22; the column headings are the measured −3 dB beamwidths)
> Table 3 "Comparison of simulated and measured helix gain — 5.0 turns L(λ) 1.2: NECWinPro 12.0 · Emerson simplified formula 11.6 · Measured 12.5 / 16.7 turns L(λ) 4.0: NECWinPro 14.5 · Emerson sim. 14.0 · formula 14.0 · Measured 15.0" (p.22)
> "The measured radiation lobes (–3 dB) at 2400 MHz agree within about ±1.5 degrees with the calculated" (p.22)
> Note: Table 3 footnote prints "G = 10.25 + 1.22 L –0.00726 L2"; Emerson's own page (B7) gives 0.0726 L², which reproduces the table's 14.0 dB at L = 4 λ, so the QEX footnote is a typo.
> "G ≅ 10 log10 (41,253 η / θ²) (Eq 11) where: θ = main-lobe radiation angle at half power, in degrees η = efficiency (< 1)" (p.21)

## B16. Zakaria et al., "Design of Stacked Microstrip Dual-band Circular Polarized Antenna", Radioengineering 21(3), Sept 2012, pp.875-880
- URL: https://www.radioeng.cz/fulltexts/2012/12_03_0875_0880.pdf
- Local: B_Radioeng2012_stacked_CP_patch_2p45_5p8.pdf / .txt
- Evidence: S11/AR MEASURED; gain SIMULATED.
> "circular polarized (CP) microstrip antenna for ISM band applications (2.45 GHz and 5.8 GHz). The proposed dual-band CP microstrip antenna with compact design has achieved design intention of having return loss of < −10 dB and axial ratio of < 3 dB for both frequencies" (Abstract)
> "two dielectric substrates FR4 with equal thickness of h1 = h2 = 1.6 mm" · "60 mm × 60 mm of ground plane" (§2)
> "The proposed antenna is shown to generate left hand circular polarization (LHCP) and right hand circular polarization (RHCP) at both frequencies. The maximum directivity gain is 6.4 dBi at 2.45 GHz and 5.9 dBi at 5.8 GHz." · "Based on the simulated result, the gains are 2.84 dB and 4.32 dB at 2.45 GHz and 5.8 GHz, respectively." (§3) — i.e. directivity 6.4/5.9 dBi but realized gain only 2.8/4.3 dB on FR4.

## B17. He, Hong, Xiong, Zhang, Tentzeris, "Design of a Novel High-Gain Dual-Band Antenna for WLAN Applications", IEEE AWPL vol.8, 2009, pp.798-801 (author-hosted copy)
- URL: https://tentzeris.ece.gatech.edu/AWPL09_He.pdf
- Local: B_AWPL2009_He_dualband_patch_monopole.pdf / .txt
- Evidence: MEASURED gain and patterns; FR4, reflector-backed.
> "The antenna is composed of a fork-like monopole, a rectangular ring, and a miniaturized rectangular patch. The backside radiation of the antenna is effectively reflected back by a rectangular metal, so maximum gain with the values of 6.2 and 10.4 dBi are achieved in the lower and higher frequency band, respectively." (Abstract)
> "Because of the affect of higher mode of rectangular patch, the gain drops down between 5.4 and 5.8 GHz." (§III)
> "the symmetry of the pattern in this plane is improved at 5.35 GHz through the additional contribution of the higher mode radiated by the rectangular patch." (§III)
Note (mine): direct evidence that dual-band printed antennas change gain and pattern shape across the upper band — the 2.4 and 5 GHz maps will have different beam shapes.

## B18. W. A. Coles et al., "A Radio System for Avoiding Illuminating Aircraft with a Laser Beam", arXiv:0910.5685 (2009) — patch ground-plane vs F/B, FR4 loss (1090 MHz)
- URL: https://arxiv.org/pdf/0910.5685
- Local: B_arxiv0910.5685_5p8GHz_patch_array_aircraft_radar.pdf / .txt (filename says 5p8GHz in error; the paper is at 1090 MHz)
- Evidence: MEASURED.
> "We tested a patch made with FR4 circuit board material. We found that FR4 has sufficient dielectric loss at 1090 MHz that it reduces the Q of the resonance by about 50%." (p.3)
> "The calculated gain for an infinite ground plane was 5.3 dBi, which includes a dielectric loss of 0.5 dB. The measured gain for a patch mounted on a large ground plane was 4.7 ± 0.5 dBi" (p.3, Rogers RO4535 patch)
> "we measured the impedance and the front-to-back ratio of a single patch with different ground plane widths. The front to back ratio of the three smaller ground planes shown in Figure 3 above, were 9 dB, 13 dB and 22 dB." (p.5) — per the Fig.3 caption (p.5) the three smaller ground planes extend ~17 mm (PCB only), ~34 mm (PCB + 17 mm plate) and ~68 mm ("A ground plane extending 51 mm past the antenna (a total of 68 mm beyond the patch) is indistinguishable from a much larger ground plane", p.3-5) beyond the patch; λ = 275 mm at 1090 MHz, so ≈0.06, 0.12 and 0.25 λ.
> "The extent of the ground plane is an important factor as it will often be convenient to minimize the weight and windage of the ground plane material." (p.5)

## B19. Maarten Baert, "Pagoda antenna" and "Measurements" pages (omni CP reference — the cloverleaf/pagoda family)
- URLs: https://www.maartenbaert.be/antennas/pagoda-antenna/ · https://www.maartenbaert.be/antennas/measurements/
- Local: B_baert_pagoda-antenna.txt, B_baert_measurements.txt
- Evidence: MEASURED (anechoic chamber by Antenna Test Lab).
> "The Pagoda antenna is an omnidirectional circularly polarized antenna design that I created." · "The diameter is just 22.5 mm"
> Specifications table (Simulated / Measured): "Center frequency 5.8 GHz / 5.8 GHz ± 100 MHz · Bandwidth 500 MHz (5.55 – 6.05 GHz) / 500 MHz ± 50 MHz · Axial ratio < 1.3 (2.28 dB) / < 1.33 (2.5 dB) · Antenna gain 1.2 dBi / 0.0 dBi · Radiation efficiency 94% / 78%"
> "For comparison, here's a simulation of the Pagoda antenna and a traditional cloverleaf antenna using the same simulation software and setup"
> "In the 'worst case' simulation, they are completely reflected back towards the antenna. The latter case usually results in standing waves on the outside of the coax, which causes the coax itself to radiate and interfere with the radiation pattern of the antenna."
> "The PCBs must use 1.0 mm thickness FR4 material , not the regular 1.6 mm thickness. The correct thickness is critical" · "I used Elecrow for my prototypes, they will make 10 PCBs for $10."
> Measurements page: "I have collected measurement results for many different 5.8 GHz FPV antennas." ... "The anechoic chamber used for these tests has a 'noise floor' of -20 dB." (lists Aomway Cloverleaf, Aomway Helical 11 dB, SpiroNet Patch 8 dB/13 dB, TrueRC X-Air — values are in images, not text, so no numbers are claimed here)

## B20. Stan Swan, "USB adaptors & DIY antenna = 'Poor Man's WiFi'?" (WokFi page, 2004; mirror)
- URL: https://mark0.net/mirror/wokfi/
- Local: B_WokFi_mark0_mirror.txt
- Evidence: informal field tests; gains mostly CLAIMED/estimated ("~15dB ?").
> "The largest so called "WIFRY" or "WOKTENNA" (12"= 300mm diam) shows 12-15dB gain ... costs ~US$5"
> "a 300mm diam mesh parabola (gain ~15dB ?) that fits this USB dongle beautifully."
> "Updating our own pattern field tests, using a rotating Lazy Susan kitchen support, confirms reception improvement ~15dB when directed at the distant signal source, but outgoing transmission gain may be less due to dish reflector "under illumination" ?"
> "~1/2dB loss per m is typical with microwave coax, with maybe another 1dB at each connector."

---

## Could not retrieve / not verified (fork B) — no claims made from these
- Hindawi IJAP 2022, "A Low-Profile Dual-Band Directional Antenna for Unmanned Aerial Vehicle Applications", doi:10.1155/2022/4765008 — PDF https://downloads.hindawi.com/journals/ijap/2022/4765008.pdf and Wiley mirrors return a Cloudflare challenge page.
- Official ADI HMC849A datasheet https://www.analog.com/media/en/technical-documentation/data-sheets/hmc849a.pdf — connection fails for automated client; the older Hittite HMC849ALP4CE v00.1013 sheet from a mirror was used instead (B14).
- Skyworks SKY13351-378LF and AS179-92LF datasheets — skyworksinc.com document URLs return a 404 page to automated fetch; no Skyworks numbers are quoted.
- EV1HMC849ALP4C evaluation-board / HMC849 chip prices (Richardson RFPD returns HTTP 403; findchips loads prices by script). No switch-board price is claimed.
- ExpressLRS-style 2.4 GHz Moxon pages (radiomasterrc.com, betafpv.com) — HTTP 429 rate-limit; no Moxon numbers claimed here.
- DRDO Defence Science Journal 3D-printed 2.4 GHz helix (https://publications.drdo.gov.in/ojs/index.php/dsj/article/download/20901/8563/89094) — download returned nothing.
- Trevor Marshall biquad: no measured pattern/gain found; the referenced OH3GPJ test page (koti.mbnet.fi/zakifani/biquad/) is offline.
- Kent Electronics datasheets B_WA5VJB_UWB_700M26Gdatasheet.pdf and B_WA5VJB_Wheels2400.pdf are image-only (no text layer); nothing quoted from them.
