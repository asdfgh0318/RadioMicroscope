# Extracts, part D: make-your-own PCB antennas (fab cost, FR4 loss, open designs, simulators) and feed/connector losses

Written 2026-11-11 from the D_* files saved by the interrupted fork (all fetched 2026-11-11) plus one page
fetched in this pass (D_jlcpcb_shipping_methods.*). Every quote is copied verbatim from the local file named
(pdftotext -layout for PDFs, text dump for HTML). Where pdftotext split a sentence across columns or lines, the
words are rejoined with single spaces; nothing else is changed. URLs come from the fetch commands in the
earlier fork's log; where a URL is marked "(reconstructed)" it was rebuilt from the saved filename and the
page's own links, not copied from a fetch command.

Tags: [V] read in the saved file. Notes marked "(mine)" are arithmetic or inference, not source text.

---

## D-1. PCB fabrication cost and delivery to Poland

### D1. AISLER, "Our Simple Pricing" (community knowledge-base page)
- URL: https://community.aisler.net/t/our-simple-pricing
- File: `D_aisler_simple_pricing.txt`  [V]
- Quotes:
  - "For simplicity, pricing formulas described here are net-price formulas. Please add respective attributable VAT where required (i.e. if you are a consumer)."
  - "PCB Price = Job Fee + Area x Area-usage Fee x Quantity"
  - "Minimum order quantity is always 3, you can order any Beautiful Board in sets of 3."
  - Table rows: "2 Layer 1.6mm HASL Budget € 12.00 € 0.067 per cm 2" / "2 Layer 1.6mm ENIG Budget​ € 12.00 € 0.097 per cm 2" / "4 Layer 1.6mm ENIG Budget​ € 14.00 € 0.13 per cm 2" / "4 Layer 0.8mm ENIG Budget € 12.00 € 0.156 per cm 2"
  - "Example: 2-Layer 1.6mm HASL Budget -Service with a PCB that is 7.0 cm x 5.0 cm: Price = 12.00 € + 35 cm 2 x 0.051 €/cm 2 x 3 = € 17.35"
- Note (mine): the worked example uses 0.051 €/cm², the table 0.067 €/cm²; with the table rate the same board is 12 + 35 × 0.067 × 3 = €19.04 net. The table lists no 1.0 mm two-layer option.

### D2. AISLER, "A quick primer about shipping at AISLER"
- URL: https://community.aisler.net/t/a-quick-primer-about-shipping-at-aisler/672
- File: `D_aisler_shipping_primer.txt`  [V]
- Quotes:
  - "Standard shipping via Deutsche Post Großbrief or DHL Warenpost is always included in your order for free. These options do not include tracking or insurance."
  - European Union table: "DHL Warenpost 4-14 Business Days" / "UPS Standard 2-7 Business Days"
  - "For customers within the EU , the respective tax will usually be included in the checkout and thus deliveries should be delivered free of any additional charges."

### D3. AISLER, "Beautiful Boards" product page
- URL: https://aisler.net/en/products/boards
- File: `D_aisler_boards_page.txt`  [V]
- Quotes: "Locally manufactured in Europe within two business days, and directly delivered to your doorstep." / "Starting at just €14.20." / "2, 4, 6 or 8 layers on FR4, with HASL or ENIG surface finish and several further options." / "For a bare board, three is the minimum."

### D4. JLCPCB home page
- URL: https://jlcpcb.com/
- File: `D_jlcpcb_homepage.txt`  [V]
- Quotes: "FR-4 PCBs 1 - 32 layers ... From $2.00 / 5 pcs Build Time: 24 hours" / "High-Frequency PCBs Rogers/Teflon materials Low Dk/Df for signal integrity ... From $47.00 / 5 pcs Build Time: 4-5 days" / "JLCPCB offers affordable PCB prototypes starting at just $2 for 5 PCBs. Costs depend on size, layer count, surface finish, and quantity" / "most orders arriving within 2–7 business days."

### D5. JLCPCB, "Shipping Methods: Delivery Time & Global Options" (fetched in this pass)
- URL: https://jlcpcb.com/help/article/shipping-methods-and-delivery-time
- Files: `D_jlcpcb_shipping_methods.html`, `.txt`  [V]
- Quotes: "Last updated on Nov 10, 2026" / "Most international shipments will incur additional fees in the form of duties and taxes. These fees are your responsibility, and are related to the country with which you are importing. These charges are in addition to the shipping cost, and are not able to be estimated/calculated by JLCPCB."
- Note (mine): the shipping-option table on this page is an image; no shipping price to Poland is in the text.

### D6. JLCPCB, "EU Customs Reform (EUCR) July 2026 – Client FAQ"
- URL: https://jlcpcb.com/help/article/eu-customs-reform-faq
- File: `D_jlcpcb_eu_customs_reform_faq.txt`  [V]
- Quotes:
  - "Starting July 1, 2026, the European Union will eliminate the customs duty exemption for low-value goods."
  - "A new "temporary customs duty" of €3.00 per HS code will be introduced for shipment valued at €150 or less."
  - "Effective November 1, 2026, a handling fee of €2 per import customs declaration line item will be charged on B2C distance sales of goods imported into the EU, regardless of the shipment value."
  - "VAT applies to all shipments. Eligible orders can be collected/remitted via IOSS"
  - Disbursement-fee table, Poland row: "Poland 2.5% of the advanced amount, Minimum 69.00 PLN 3% of the advanced amount, Minimum 85.00 PLN, IF shipment value < 22.00 eur are collected with a charge of 41.30 PLN 2.5% of the advanced amount, Minimum 63.60 PLN" (columns DHL / UPS / FedEx, "Per Shipment")
  - "When you select the DDP service, JLCPCB will automatically calculate, collect, and pay the relevant fees on your behalf when you place the order: including VAT, temporary customs duty, and the duty & tax disbursement fee."

### D7. PCBWay home page
- URL: https://www.pcbway.com/
- File: `D_pcbway_homepage.txt`  [V]
- Quotes: "PCB Prototype From $5 /10pcs Build Time:24 hours" / "New here? Get a $5.00 Coupon!"
- Not retrieved: PCBWay's shipping page (https://www.pcbway.com/helpcenter/shipping/) loads costs only in the quote tool; no shipping price to Poland.

---

## D-2. FR4 dielectric loss and what it costs in gain

### D8. JLCPCB, "Controlled Impedance PCB Parameters and Stackup"
- URL: https://jlcpcb.com/impedance
- File: `D_jlcpcb_impedance_stackup.txt`  [V]
- Quotes: "Prepreg type Dielectric constant 7628 4.4 3313 4.1 1080 3.91 2116 4.16" / "3. Core dielectric constant Core dielectric constant 4.6". (No loss tangent is given on this page.)

### D9. Isola 370HR laminate data sheet (a common FR4-class laminate)
- URL: https://www.isola-group.com/wp-content/uploads/data-sheets/370hr.pdf
- Files: `D_isola_370HR_datasheet.pdf`, `.txt`  [V]
- Quotes: "Dk, Permittivity ... C. @ 2 GHz 4.04 ... D. @ 5 GHz 3.92" / "Df, Loss Tangent B. @ 1 GHz 0.0161 ... C. @ 2 GHz 0.0210 ... D. @ 5 GHz 0.0250"

### D10. Megnet & Mathis, "Circular Polarized Patch Antenna for 5.8 GHz Dedicated Short-Range Communication", Proc. 39th European Microwave Conference (2009)
- URL: https://www.ost.ch/fileadmin/dateiliste/3_forschung_dienstleistung/institute/icom/projekte/circular_polarized_patch_antenna_for_5.8_ghz.pdf
- Files: `D_megnet2009_FR4_airlayer_CP_patch_5G8.pdf`, `.txt`  [V]
- Evidence: loss figure SIMULATED (HFSS); S11/CPR measured.
- Quotes:
  - Abstract: "The patch antenna is based on low-cost, but lossy, FR-4 material."
  - §III: "The patch is separated from the substrate by an air layer. This stacked dielectric design reduces the dielectric losses without causing additional costs"
  - §III: "The antenna prototypes are built with an 1.4 mm air layer and an 1.5 mm PCB layer."
  - §IV.A: "Most of the dielectric power loss is caused by the PCB. Simulations showed that about 8.9 % of the power is dissipated in the FR-4 PCB."
- Note (mine): 8.9 % dissipated = 10·log10(0.911) ≈ −0.4 dB, for an air-spaced patch with FR4 carrying only the feed.

### D11. "2.45 GHz inset-fed microstrip patch antenna on FR4 (openEMS)" — GitHub README (Muhad33/openems-patch-antenna)
- URL: https://github.com/Muhad33/openems-patch-antenna (reconstructed)
- File: `D_gh_Muhad33_openems-patch-antenna_README.md`  [V]
- Evidence: SIMULATED only (openEMS).
- Quotes:
  - "> **Status: simulation only.** No board has been built or measured yet."
  - Results table: "Peak directivity | 6.57 dBi" / "Peak gain (IEEE) | **3.26 dBi**" / "Radiation efficiency | **46.7 %**" / "Half-power beamwidth, E / H plane | 93.0° / 89.1°" / "Front-to-back ratio | 14.0 dB" / "−10 dB bandwidth | **67.4 MHz** (2.4167–2.4841 GHz, 2.75 %)"
  - "Board | 60 × 60 mm, FR4 (εr 4.4, tan δ 0.02), 1.6 mm, 35 µm copper"
  - "**FR4 tolerance.** The resonance moves about −26 MHz per +0.1 in εr. Generic FR4 ranges from about 4.2 to 4.6 at 2.4 GHz, so a ±0.2 spread shifts the band by about ±52 MHz"
  - "Gerbers, drill, DXF/SVG, KiCad footprint ([fabrication/](fabrication/README.md))"
  - "MIT, see [LICENSE](LICENSE)."
- Note (mine): directivity 6.57 dBi vs gain 3.26 dBi = 3.3 dB lost on a patch etched directly on 1.6 mm FR4 at 2.45 GHz (simulated).

### Cross-references to FR4 loss figures already in parts B and C (quoted there; not repeated)
- B1 TI DN034 PCB Yagi on FR4, MEASURED efficiency "85.20 % 71.70 % 58.24 %" at 2400/2440/2480 MHz.
- B10 Dou et al. dual-band on FR4 (tan δ 0.02), MEASURED "70% at 2.4 GHz and 84.5% at 5.5 GHz".
- B16 Zakaria et al. stacked FR4 CP patch: directivity "6.4 dBi at 2.45 GHz and 5.9 dBi at 5.8 GHz", simulated gains "2.84 dB and 4.32 dB".
- C4 Baert Triple Feed Patch (1.0 mm FR4, air-spaced), MEASURED radiation efficiency 74 %; "Most FR4-based patches have terrible efficiency because FR4 is very lossy at 5.8 GHz."

---

## D-3. Open antenna designs with a licence

### D12. Baert, Triple Feed Patch — design-file and fabrication details (supplementary quotes from the part-C file)
- URL: https://www.maartenbaert.be/quadcopters/antennas/triple-feed-patch-antenna/
- File: `C_baert_triple_feed_patch.txt`  [V]
- Quotes:
  - "Download Triple Feed Patch 1 design files (includes LHCP, RHCP and hybrid variant)"
  - "Manufacturers will make these for you if you send them the Gerber files which are included in the design files above."
  - "The PCBs must use 1.0 mm thickness FR4 material, not the regular 1.6 mm thickness. The correct thickness is critical, if you get this wrong the design won't work properly at all!"
  - "SMA connector (vertical type): For performance reasons I used surface-mount vertical SMA connectors. I used this for my prototypes. They cost $8 for 10 pieces, so that's $1.6 per antenna."
  - "The PCBs need to be spaced accurately to get good results. The correct spacing is 4 mm."
  - Reply in the page's comment thread: "- PCB Thickness: "1.0mm"" / "- PCB Size: "5cm Max * 5cm Max" (part1) / "10cm Max * 10cm Max" (part2)"
  - (Licence, measured gain 9.3 dBi, HPBW 55°, efficiency 74 % are quoted in C4.)

### D13. "Project Platypus — 2.4 GHz Microstrip Patch Antenna" — GitHub README (Matthewjg95/project-platypus-patch-antenna)
- URL: https://github.com/Matthewjg95/project-platypus-patch-antenna (reconstructed)
- File: `D_gh_Matthewjg95_project-platypus-patch-antenna_README.md`  [V]
- Evidence: built; gain NOT characterised.
- Quotes: "**Status: manufactured and functional. Gain vs the host's internal antenna is not yet characterised.**" / "Each board is 58 × 70 mm" / "Substrate: FR4, h = 1.6 mm, εr = 4.4, tan δ ≈ 0.02, 2 layers, ENIG." / "The ground plane extends only 10–12 mm (≈0.1 λ) past the patch, so realistic F/B is ~6–10 dB." / "Rev 9 — dual SMT connector lands (u.FL + MMCX); current" / "rev9_gerbers_jlcpcb.zip" / "**[CERN Open Hardware Licence v2 — Strongly Reciprocal](LICENSE)** (CERN-OHL-S v2)."

### D14. ICDT (Inatel CubeSat Design Team), "S-Band RHCP 2.45 GHz Antenna" — README and datasheet
- URL: https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna ; datasheet https://raw.githubusercontent.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/<branch>/docs/Datasheet%20S-Band%20RHCP%202.45%20GHz%20Antenna.pdf
- Files: `D_gh_ICDT-Inatel-Cubesat-Design-Team_S-Band-Antenna_README.md`, `D_gh_ICDT_SBand_RHCP_datasheet.pdf`, `.txt`  [V]
- Evidence: SIMULATED (README: "`simulation`: Ansys HFSS simulation and data files"; status "Testing").
- Quotes: "Axial Ratio Bandwidth: 14 MHz (2443 – 2457 MHz for AR < 3 dB)" / "Peak Realized Gain: 7.58 dBi" / "Polarization: Right-Hand Circular Polarization (RHCP)" / "Connector Type: Right-Angle SMA" / "`Fabrication`: BOM and Gerber files for JLCPCB manufacturing." / "**[CERN-OHL-W-2.0](LICENSE)**"; datasheet: "Board Size (Ground): 82.4 x 89.4 mm" / "Type: ZYF255DA (Permittivity: 2.55, Tangent Loss: 0.0018)" / "Thickness: 1.52 mm".
- Note (mine): not FR4, so it needs a high-frequency laminate order (D4: "From $47.00 / 5 pcs").

### D15. "Breitband-Vivaldi-Antenne" — GitHub README (ali-dev22/vivaldi-antenna-design)
- URL: https://github.com/ali-dev22/vivaldi-antenna-design (reconstructed)
- File: `D_gh_ali-dev22_vivaldi-antenna-design_README.md`  [V]
- Quote: "It currently contains **documentation only** — the OpenEMS/Octave scripts, KiCad layout files, and measurement report will be added here once the project is finalized and submitted." / "MIT — see [LICENSE](LICENSE)." — not orderable as-is.

### D16. Dou et al. 2021 dual-band directional antenna — licence and dimension table (supplementary quotes from the part-B file)
- URL: https://mdpi-res.com/d_attachment/applsci/applsci-11-02007/article_deploy/applsci-11-02007.pdf
- File: `B_MDPI_applsci-11-02007_dualband_directional.txt`  [V]
- Quotes: "This article is an open access article distributed under the terms and conditions of the Creative Commons Attribution (CC BY) license" / "Table 1. Parameters of the proposed antenna (unit: mm)." with "W1 69 ... L1 50" (board outline). Measured performance is quoted in B10. No Gerber files are published; the layout has to be redrawn from Table 1.

### D17. KiCad footprint library: RF_Antenna.pretty listing and library licence
- URLs: https://gitlab.com/api/v4/projects/kicad%2Flibraries%2Fkicad-footprints/repository/tree?path=RF_Antenna.pretty&per_page=100 ; https://gitlab.com/kicad/libraries/kicad-footprints/-/raw/master/LICENSE.md
- Files: `D_kicad_RF_Antenna_pretty_listing.txt`, `D_kicad_footprints_LICENSE.md`  [V]
- Quotes: listing contains "Texas_SWRA117D_2.4GHz_Left.kicad_mod", "Johanson_2450AT18x100.kicad_mod", "Molex_47948-0001_2.4Ghz.kicad_mod" (chip and printed omni/IFA antennas; no directional antenna in the list); licence: "The KiCad libraries are licensed under the [Creative Commons CC-BY-SA 4.0 License]" / "Use of the library data in a project does not (by itself) require that the design or any files generated from the design are licensed under the CC-BY-SA 4.0 License."

---

## D-4. Free simulators

### D18. openEMS documentation, "Introduction" (v0.37.0)
- URL: https://docs.openems.de/en/latest/intro.html
- File: `D_openems_docs_intro.txt`  [V]
- Quotes: "openEMS is a free and open source electromagnetic field solver based on the Finite-Difference Time Domain (FDTD) method." / "Near-field to Far-field (NF2FF) transform for antenna simulation." / "openEMS is licensed under the GNU General Public License, Version 3 or later" / "Cross-platform support, including Linux, FreeBSD, macOS and Windows"

### D19. openEMS-Project on GitHub
- URL: https://github.com/thliebig/openEMS-Project
- File: `D_openems_github_page.txt`  [V]
- Quote: "openEMS is a free and open electromagnetic field solver using the FDTD method. Octave/Matlab and Python are available as easy and flexible scripting interfaces."

### D20. jPCBSim README
- URL: https://github.com/tvelliott/jPCBSim (reconstructed; wiki link in file: https://github.com/tvelliott/jPCBSim/wiki)
- File: `D_gh_tvelliott_jPCBSim_README.md`  [V]
- Quote: "Front-end and post processing software for simulating planar RF filters and antennas with the openEMS FDTD field solver." / "Use hyperlynx 6.3 or greater to export your eagle cad brd file to the .hyp file format."

### D21. NEC-2 Manual, Part III: User's Guide
- URL: https://www.nec2.org/other/nec2prt3.pdf
- Files: `D_nec2_user_guide_part3.pdf`, `.txt`  [V]
- Quotes: "The Numerical Electromagnetics code (NEC-2) is a computer code for analyzing the electromagnetic response of an arbitrary structure consisting of wires and surfaces in free space or over a ground plane." / "The Numerical Electromagnetics Code (NEC-2) is a user-oriented computer code for analysis of the electromagnetic response of antennas and other metal structures."

### D22. Xnec2c user manual
- URL: https://www.xnec2c.org/
- File: `D_xnec2c_manual_page.txt`  [V]
- Quotes: "Xnec2c is a high-performance multi-threaded electromagnetic simulation package to model antenna near- and far-field radiation patterns for Linux and UNIX operating systems." / "flatpak install flathub org.xnec2c.Xnec2c"

### D23. 4nec2 home page
- URL: https://www.qsl.net/4nec2/
- File: `D_4nec2_home.txt`  [V]
- Quote: "4nec2 is a completely free Nec2, Nec4 and windows based tool for creating, viewing, optimizing and checking 2D and 3D style antenna geometry structures and generate, display and/or compare near/far-field radiation patterns" / "Latest 4nec2 version (5.9.3)" / "last revised: Apr 28, 2021"

### D24. MMANA-GAL page
- URL: http://mmhamsoft.amateur-radio.ca/pages/mmana-gal.php
- File: `D_mmana_gal_page.txt`  [V]
- Quotes: "MMANA-GAL is an antenna-analyzing tool based on the moment method, which was introduced in MININEC version 3." / "MMANA-GAL basic version is free ONLY for private, non-commercial use (f.e. HAM radio, hobby, self education etc)."

### D25. Dassault Systèmes, CST Studio Suite Learning Edition page
- URL: https://www.3ds.com/edu/education/students/solutions/cst-studio-suite-student-edition
- File: `D_3ds_cst_learning_edition.md`  [V]
- Quotes: "The CST Studio Suite Learning Edition is available free of charge to students, educators and researchers of personal and educational use" / "With this free edition you have - bar some restrictions - access to our powerful visualization engine and some of the most advanced solvers of CST Studio Suite" / "CST Studio Suite is available for modern Windows operating systems."

### D26. CATI blog, "4 Steps to Download CST Studio Suite & Antenna Magus FREE!" (Oct 2022)
- URL: https://www.cati.com/blog/4-steps-to-download-cst-studio-suite-antenna-magus-free/
- File: `D_cati_cst_antennamagus_student.txt`  [V]
- Quotes: "You don’t need affiliation with an academic institution to try out CST Studio Suite and Antenna Magus for free ." / "The Antenna Magus Student Edition ​​​​​​​ is available for Windows only and includes design capabilities for 12 popular antenna types."

---

## D-5. Feed cable and connector losses (closes the part-D gap and task 2)

Parts A/B/C contain no per-length loss for 1.13 mm or RG178 cable and no U.FL mating rating (A20's
"Mating Cycles 500" is for an SMA rotary joint; B20 gives only the generic "~1/2dB loss per m"). Datasheets:

### D27. Wellshow 1.13 mm coaxial cable specification (Techship download)
- URL: https://techship.com/download/datasheet-for-1-13mm-cable/
- Files: `D_cable113_techship.pdf`, `.txt`  [V]
- Quotes: "1.13mm Coaxial Cable Product No. D1130WS5BT (Black jacket)" / "Attenuation 2 GHz 2.4 GHz 2.5 GHz 5 GHz 6 GHz" / "dB/1m 2.80 3.20 3.25 5.05 5.40" / "VSWR (0 ~6 GHz) 1.3 Max."
- Note (mine): per 10 cm: 0.32 dB at 2.4 GHz; 0.53 dB at 5.8 GHz (linear interpolation 5→6 GHz).

### D28. Siretta 1.13 mm cable assembly datasheet (RS Components)
- URL: https://docs.rs-online.com/8f30/A700000015150624.pdf
- Files: `D_cable113_siretta_rs.pdf`, `.txt`  [V]
- Quotes: "Attenuation (across frequency) Frequency (GHz) 1 GHz 2 GHz 3 GHz 4 GHz 5 GHz 6 GHz 7 GHz 8 GHz" / "dB/1m 2.20 3.10 3.90 4.50 5.00 5.50 6.10 6.70" / "Suggested Working Frequency: DC to 6GHz"
- Note (mine): per 10 cm ≈ 0.34 dB at 2.4 GHz and 0.54 dB at 5.8 GHz (interpolated).

### D29. HUBER+SUHNER ENVIROFLEX_178_D data sheet (RG178 equivalent)
- URL: https://shop.richardsonrfpd.com/docs/rfpd/hs_enviroflex_178_d_en.pdf
- Files: `D_hubersuhner_enviroflex178D.pdf`, `.txt`  [V]
- Quotes: "RG178D/RD178 LSFH, 50 Ohm, 6 GHz, 105°C, ø2.45 mm," / "typical Attenuation [ formula: (a*f^0.5 + b*f) ]" "a = 1.4187 b = 0.207" / table rows "2,4 2,69 0,821" and "5,7 4,57 1,392" and "6,0 4,72 1,438" (GHz, dB/m, dB/ft)
- Note (mine): per 10 cm 0.27 dB at 2.4 GHz, ≈0.46 dB at 5.8 GHz.

### D30. Qualwave RG178 flexible cable data sheet
- URL: https://www.qualwave.com/uploads/pdf/RG178.pdf (reconstructed by analogy with the RG316 URL in the fork log)
- Files: `D_qualwave_RG178.pdf`, `.txt`  [V]
- Quotes: "Frequency: DC~6GHz" / "Attenuation(dB/100m) 52 120 170 242 308 363 415 480" at "Frequency (GHz) 0.1 0.4 1 2 3 4 5 6" / "Calcuate Connector Attenuation: Attenuation (dB) = 0.03 × F (GHz)"

### D31. Pasternack RG178B/U data sheet
- URL: https://www.pasternack.com/images/ProductPDF/RG178B-U.pdf
- Files: `D_pasternack_RG178.pdf`, `.txt`  [V]
- Quotes: "Frequency Range DC 3 GHz" / "Attenuation, Typ 13.81 27.8 44.41 78.4 dB/100ft" "45.31 91.21 145.7 257.22 dB/100m" at "0.1 0.4 1 3 GHz" — rated only to 3 GHz.

### D32. Hirose U.FL series catalogue (2023/2024)
- URL: https://www.farnell.com/datasheets/3993933.pdf
- Files: `D_hirose_UFL_catalog_2024.pdf`, `.txt`  [V]
- Quotes: "Rated Frequency 0 to 8GHz" / "Mating Durability Contact Resistance : Initial + 5 m Ω 30 times" / V.S.W.R. table: "U.FL-LP-068HF φ 1.13 1.3 Max. 1.4 Max." (columns "0 to 3GHz" / "3GHz to 6GHz")
- Note: the catalogue's insertion-loss chart is a graphic; no U.FL insertion-loss number is in the text.

### D33. I-PEX MHF I connector product specification PRS-1726-07EN and test report TR-12096
- URLs: https://www.i-pex.com/sites/default/files/downloads/pdf/PRODSPEC_MHF_I_PRS-1726-07EN.pdf ; https://www.i-pex.com/sites/default/files/downloads/pdf/TEST-REPORT_MHF_I_TR-12096-09EN.pdf
- Files: `D_ipex_MHF1_prodspec_PRS-1726.pdf/.txt`, `D_ipex_MHF1_testreport_TR-12096.pdf/.txt`  [V]
- Quotes: "Frequency ： DC~9.0GHz" / "VSWR ：Plug: 1.3 MAX. at 0.1~3GHz , 1.5 MAX. at 3~6GHz" / "3. Durability ... repeat mating and un-mating 30cycles at a speed 25±3mm/min. along the mating axis." / "Total unmating force Initial: 5N Min. After 30 cycles: 3N Min."

### D34. IMS Connector Systems SMA 50 Ohm data sheet
- URL: https://cms.imscs.com/sites/default/files/2023-05/sma.pdf
- Files: `D_ims_SMA.pdf`, `.txt`  [V]
- Quotes: "Insertion loss ≤ 0.03 x f [GHz] dB straight, semi-rigid cable" / "Durability (matings) 500"

### D35. Cinch / Johnson SMA connector catalogue pages
- URL: https://hkjdwchip.com/image//files/cinchconnectivitysolutions-1420901931-datasheets-3439.pdf
- Files: `D_cinch_johnson_SMA.pdf`, `.txt`  [V]
- Quotes: "Insertion Loss: (dB maximum) Straight flexible cable connectors and adapters ...................... 0.06 f (GHz), tested at 6 GHz" / "Right angle flexible cable connectors ......................... 0.15 f (GHz), tested at 6 GHz" / "Durability: 500 cycles minimum"

---

## Saved but not used in the report
- `D_hubersuhner_enviroflex316D.*`, `D_pasternack_RG316.*`, `D_qualwave_RG316.*` (RG316, thicker than needed), `D_harbour_MIL_coax_talley.*` (RG142), `D_3ds_cst_studio_suite.md` (commercial product page).

## Could not retrieve (part D) — no claims made from these
- JLCPCB and PCBWay shipping prices to Poland: both sites compute them only in the quote/checkout tool (JLCPCB's options table is an image, D5). https://jlcpcb.com/help/article/shipping-costs ; https://www.pcbway.com/helpcenter/shipping/
- Current Elecrow price for 10 × 1.0 mm boards (Baert's "10 PCBs for $10" is undated page text). Not fetched.
- TI swrr074.zip (DN034 Yagi Gerbers) licence terms: not fetched; DN034 itself says TI grants no licence under its IP (B_TI_DN034_swra350.txt, legal notice).
- A sourced single number for "FR4 vs low-loss laminate, same patch, same frequency" measured side by side was not found; the figures above come from different designs.
