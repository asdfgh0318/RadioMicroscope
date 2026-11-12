# EXTRACTS — antenna research for the radio microscope (merged A + B + C + D)

Merged 2026-11-11 from `_EXTRACTS_A.md` (beam theory, sampling, polarisation, calibration, rotary joints),
`_EXTRACTS_B.md` (DIY designs, RF switches), `_EXTRACTS_C.md` (ready-made antennas, prices, pigtails) and
`_EXTRACTS_D.md` (PCB fab cost, FR4 loss, open designs, simulators, cable/connector losses). The part files are
left in place and are the authoritative copies; this file is their concatenation, unchanged except for this
header and the quote-check record at the end. Every quote is verbatim from a file saved in this folder.
Evidence tags: [V] read at source in the saved file; [S] search snippet only (no claim rests on it).



<!-- ===================== part A (from _EXTRACTS_A.md) ===================== -->

# Extracts, part A: beam theory for a mapper, calibration, rotary joints

Fork A. Covers Q1 (gain/beamwidth, sampling, side lobes, F/B, polarisation, CP indoors), Q7 (calibration)
and the rotary-joint / radio-on-the-head part of Q6. Every quote below is copied verbatim from the local file
named (pdftotext output, or page text extracted from the saved HTML). Retrieved 2026-11-11.
Page numbers are PDF page numbers unless stated as journal pages.

---

## A1. Wikipedia, "Directivity" (section "Relation to beam width")
- URL: https://en.wikipedia.org/wiki/Directivity
- Files: `A_wikipedia_directivity.html`, `A_wikipedia_directivity.txt`
- Quotes:
  - "If the beam solid angle is known, then maximum directivity can be calculated as D = 4 π Ω A"
  - "The beam solid angle can be approximated for antennas with one narrow major lobe and very negligible minor lobes by simply multiplying the half-power beamwidths (in radians) in two perpendicular planes."
  - "D ≈ 4 π ( 180 π ) 2 Θ 1 d Θ 2 d ≈ 41253 Θ 1 d Θ 2 d , where Θ 1 d is the half-power beamwidth in one plane (in degrees) and Θ 2 d is the half-power beamwidth in a plane at a right angle to the other (in degrees)." [i.e. D ≈ 41253/(Θ1·Θ2)]
  - "In planar arrays, a better approximation is D ≈ 32400 Θ 1 d Θ 2 d ." [i.e. D ≈ 32400/(Θ1·Θ2)]
- Note: this is directivity; gain = directivity × radiation efficiency, so real gain is lower for a given beamwidth.

## A2. Bob Atkins (KA1GT), "Antenna Gain, Beamwidth and Efficiency"
- URL: https://bobatkins.com/radio/gain_and_beamwidth.html
- Files: `A_bobatkins_gain_beamwidth_efficiency.html`, `.txt`
- Quotes:
  - "Of these parameters, the 3dB beamwidth is the easiest to independently measure with a reasonable degree of accuracy. Gain is hard to measure accurately, but can be inferred form 3dB beamwidth"
  - "Gain = (52525/BW^2)* IE" ... "IE is the illumination efficiency"
  - "Real world feed range in illumination efficiency from maybe 0.5 to maybe 0.8, with 0.65 being a typical value."
  - "Looking at data in EMECack for Yagi gain and beamwidths it appears that the gain for a single yagi can be estimated by: Gain = 44300/BW^2 and Gain(dBi)= 10*log(Gain) Where BW is the -3dB beamwidth in degrees. If the horizontal beamwidth BWh is different from the vertical beamwidth BWv, the replace BW^2 with BWh*BWv"
  - Sun-drift method: "This was taken by setting the Az and EL to the position of the sun 30 minutes after the start of the recording." and "rather then letting the sun drift through the beam, it may be more practical to first measure peak sun noise, then calculate the expected reading when the signal drops by 3dB (see the next paragraph), the rotate the antenna until you see the predicted -3dB noise level."
- Note: hobbyist write-up with measured dish data; formulas are approximations (52525 is for a circular beam of the given diameter; 44300 is an empirical Yagi fit).

## A3. NRAO, Essential Radio Astronomy, Chapter 3 "Radio Telescopes and Radiometers" (Condon & Ransom)
- URL: https://www.cv.nrao.edu/~sransom/web/Ch3.html
- Files: `A_nrao_era_ch3_radio_telescopes.html`, `.txt` (HTML, cited by section/equation)
- Quotes:
  - §3.1.6: "The main beam of an antenna is defined as the region containing the principal response out to the first zero; responses outside this region are called sidelobes or, very far from the main beam, stray radiation ."
  - §3.2.4: "Radio astronomers use the angle between the half-power points to ... half-power beamwidth (HPBW)" [text split by pdf/html markup]; "θ HPBW ≈ 0.89 ⁢ λ D" (uniform illumination); §3.2.5 tapered: "θ HPBW ≈ 1.2 λ D ."
  - §3.2.4: "scanning a radio telescope beam in angle θ across a point source will cause the antenna temperature to vary as sinc 2 ⁢ ( θ ) , and the width of the half-power response will equal the transmitting HPBW. The receiving HPBW is sometimes called the resolving power of a telescope because two equal point sources separated by the HPBW are just resolved by the Rayleigh criterion that the total response has a slight minimum midway between the point sources."
  - §3.3.3: "the beams of most radio telescopes are nearly Gaussian" ... "Ω A = ( π 4 ⁢ ln ⁡ 2 ) θ HPBW 2 ≈ 1.133 θ HPBW 2 ." (eq. 3.118)
  - §3.3.5 Pointing: "The power patterns of most radio telescopes are nearly Gaussian near the peak. In terms of the beamwidth between half-power points θ HPBW , the relative gain at a point offset by angle ρ from the beam axis is G G 0 = exp [ - 4 ln 2 ( ρ θ HPBW ) 2 ] ." (eq. 3.134)
  - §3.3.5: "Thus an rms tracking error of 0.2 ⁢ θ HPBW will contribute a 10% rms flux-density uncertainty. For 5% accuracy, σ 2 / θ HPBW ≈ 0.14 (or σ 1 / θ HPBW ≈ 0.10 in each coordinate) is needed."

## A4. Ford (2015), "Single-dish mapping techniques", NAIC/NRAO Single-Dish School slides
- URL: https://science.nrao.edu/facilities/gbt/single-dish-school-lectures/sds-2015/single-dish-mapping-techniques (serves a PDF)
- Files: `A_ford2015_gbt_single_dish_mapping.pdf`, `.txt`
- Quotes:
  - p.20 (slide 19/20): "Nyquist Theorem (1928): Fully-sampled observations must be separated spatially by no more than FWHM / 2."
  - p.22-23 (slides 21-22) "Stray radiation": "Real beams have sidelobes due to diffraction." ... "because of overlap between source and left sidelobe, measured intensity is too high" ... "Flux from bright regions leaks into surrounding map"
  - (ligatures in the PDF text such as "observaAons" restored to "observations" above; otherwise verbatim.)

## A5. Maddalena (NRAO Green Bank), "Observing Techniques" lecture slides
- URL: https://www.gb.nrao.edu/~jmaddale/Education/ObservingTechniques.pdf
- Files: `A_nrao_maddalena_observing_techniques.pdf`, `.txt`
- Quotes (p.15, "Mapping with a single pixel"):
  - "Spacing – Nyquist sampling = λ / 2D radians or less – Typically 0.9 λ / 2D radians – Loosely related to FWHM beamwidth (~1.2 λ / D radians)"
  - "Should oversanple ~3x Nyquist along direction of slew" [sic]

## A6. Mangum, Emerson & Greisen (2007), "The On The Fly Imaging Technique", A&A 474, 679 (arXiv:0709.0553)
- URL: https://arxiv.org/pdf/0709.0553
- Files: `A_mangum2007_otf_0709.0553.pdf`, `.txt`
- Quotes (p.4, §3.2.1-3.2.2):
  - "The minimum sampling interval on the sky, for an antenna with maximum dimension D, is at intervals of λ/2D." [fraction typeset over two lines in the PDF]
  - "undersampling the sky is really twice as bad as you might have thought."
  - §3.2.2 Beam Broadening: "If you set an arbitrary criterion that the telescope beam shouldn't be broadened by more than 1%, then you need to sample at least 4.5 points per FWHM beam width. Note that since Nyquist sampling is about 2.4 points per FWHM, assuming an illumination taper of about −13 dB; for a uniformly illuminated circular aperture the factor would be about 2.06, while for a −20 dB taper it becomes 2.60. This means that one needs to sample at about twice Nyquist to avoid degradation of resolution worse than 1%."

## A7. Martin et al. (Skynet), "Skynet Algorithm for Single-Dish Radio Mapping I", ApJS (arXiv:1808.06128)
- URL: https://arxiv.org/pdf/1808.06128
- Files: `A_skynet_mapping_1808.06128.pdf`, `.txt`
- Quote (p.2-3, §1.2.1): "As long as the gaps between scans do not exceed Nyquist sampling, or ≈0.4 beamwidths, in theory all information between scans can be recovered (modulo noise, interference, etc.)" ... "undersampled images will be flagged as not for professional use."

## A8. Rohde & Schwarz white paper 8GE01, "Antenna Basics" (3.2015)
- URL: https://scdn.rohde-schwarz.com/ur/pws/dl_downloads/premiumdownloads/premium_dl_brochures_and_datasheets/premium_dl_whitepaper/Antenna_Basics_8GE01_1e.pdf
- Files: `A_rs_8GE01_antenna_basics.pdf`, `.txt`
- Quotes:
  - p.7 §2.3 Far Field Conditions: "A good approximation for small antennas is that far field conditions are reached at: 𝑟 ≈ 2∙𝜆 For larger antennas (i.e. reflector antennas or array antennas) where the dimensions of the antenna (L) are significantly larger compared to the wave length (L >> λ), the following approximation for the far field distance applies: 𝑟 ≈ 2𝐿²/𝜆" [fraction typeset over lines]
  - p.7 §2.4 Free Space Conditions: "in order to avoid the majority of effects caused by superposition of direct and reflected signals, it is necessary that the first Fresnel ellipsoid (see Figure 5) is completely free of obstacles"
  - p.8 Polarization: "The losses that occur when trying to receive a linearly polarized signal with a circularly polarized antenna amounts to 3 dB (same vice versa) - this can usually be tolerated. Most critical is the case where the orthogonal antenna polarization is used, because the attenuation increases beyond all limits theoretically. In practice, most antennas have a limited polarization decoupling, so that the loss in reality will never reach infinity."
  - p.12: "The side lobe suppression (or side lobe level) is a measure of the relation between the main lobe and the highest side lobe." / "The half-power beamwidth (HPBW) is the angle between the two points in the main lobe of an antenna pattern that are down from the maximum by 3 dB. It is usually defined for both principal plane patterns." / "The front-to-back ratio specifies the level of radiation from the back of a directional antenna. It is the ratio of the peak gain in forward direction to the gain in the reverse (180°) direction. It is usually expressed in dB."

## A9. Powertec, "Front-to-Back Ratio" (technical library page)
- URL: https://portal.powertec.com.au/technical-library/wireless/rf-parameters/front-back-ratio
- Files: `A_powertec_front_back_ratio.html`, `.txt`
- Quotes:
  - "As antenna back lobes (i.e., lobes of energy radiating to the rear of the antenna) are not necessarily perfectly 180° to the main lobe, it's important that the metric looks at a range of angles. Powertec recommend using a ± 30° angular region to determine a worst-case figure, so that a true minimum is obtained."
  - "Radiation patterns are measured by rotating an actively transmitting antenna inside an anechoic chamber, and measuring power levels at set intervals."

## A10. antenna-theory.com, "Polarization"
- URL: https://www.antenna-theory.com/basics/polarization.php
- Files: `A_antenna-theory_polarization.html`, `.txt`
- Quotes:
  - "Due to the reciprocity theorem, antennas transmit and receive in exactly the same manner."
  - "If one antenna is vertically polarized and the other is horizontally polarized, the angle is 90 degrees and no power will be transferred."
  - "Cell phone antennas are often linearly polarized, so rotating the phone can often match the polarization of the phone and thus increase reception."
  - "Another advantage of circular polarization is that a RHCP wave will reflect off a surface and be LHCP. This is advantageous because an antenna designed to receive RHCP waves will have some immunity to the signal-fading effects of reflected waves interfering with the desired wave."
  - "As a result, the LP antenna will have a polarization mismatch loss of 0.5 (-3dB), no matter what the angle the LP antenna is rotated to."

## A11. antenna-theory.com, "Directivity" and "Field Regions"
- URLs: https://www.antenna-theory.com/basics/directivity.php ; https://www.antenna-theory.com/basics/fieldRegions.php
- Files: `A_antenna-theory_directivity.html/.txt`, `A_antenna-theory_fieldregions.html/.txt`
- Quotes:
  - Directivity table: "Patch (Microstrip) Antenna 3.2-6.3 5-8" [typical directivity linear / dB]; "Horn Antenna 10-100 10-20"
  - "if you are doing remote sensing, or targetted power transfer ... you want a high directivity antenna in order to maximize power transfer and reduce signal from unwanted directions."
  - Field regions: "In this region, the radiation pattern does not change shape with distance (R)." (far field; the equations themselves are images, not in the text)

## A12. Cotton, Achatz, Lo, Holloway, "Indoor Polarization and Directivity Measurements at 5.8 GHz", NTIA Report 00-372 (Nov 1999)
- URL: https://its.ntia.gov/publications/download/00-372_ocr.pdf (landing: https://its.ntia.gov/publications/details?pub=2403)
- Files: `A_ntia_tr00-372_5p8GHz_polarization.pdf`, `.txt`
- Quotes:
  - Abstract (p.1 of report, pdf p.5): "Directional linearly-polarized (LP), directional circularly-polarized (CP), and omnidirectional LP antennas were employed ... Measurements indicated less LP basic transmission loss than CP basic transmission loss for both line-of-sight (LOS) and obstructed (OBS) channels. Also, LP rms delay spread was similar to CP rms delay spread in both LOS and OBS paths. The apparent advantage of using LP signals over CP signals indoors may be attributed to the relatively high degree of circular depolarization measured."
  - §1 Introduction: "It was conjectured in [2] that directional CP antennas are more likely to reduce rms delay spread when compared to directional and omnidirectional LP antennas"
  - §6 Conclusion (report p.15-16): "1. CP and LP signals have similar delay spreads for both LOS and OBS paths" / "2. Omnidirectional transmit and receive antennas (e.g., combinations 5, 8, and 9) produce higher delay spreads, especially for channels with large geometric aspect ratios (e.g., corridor)." / "7. CP signals are depolarized more than LP signals" / "8. The indoor channel significantly depolarizes transmitted signals." / "it does not appear that CP signals offer advantages over LP signals for co-polarized transmission."
- Note: CP at BOTH ends in this study (co-polar CP link); the radio-microscope case is CP receive vs LP Wi-Fi transmitters, which this report did not test.

## A13. Wunderlich, Welpot, Gaspard (2014), "Indoor radio channel modeling and mitigation of fading effects using linear and circular polarized antennas in combination for smart home system at 868 MHz", Adv. Radio Sci. 12, 53-59, doi:10.5194/ars-12-53-2014 (CC-BY 3.0)
- URL: https://ars.copernicus.org/articles/12/53/2014/ars-12-53-2014.pdf
- Files: `A_ars_2014_12-53.pdf`, `.txt`
- Quotes:
  - p.53: "The scattered and reflected waves that contribute to multipath fading can also transfer energy from the transmitted polarization plane into the orthogonal polarization plane (called cross-polarization coupling) (Cox et al., 1986). Such coupling occurs as a result of oblique reflections from the walls as well as due to scattering from indoor clutter, such as furniture (Kyritsi and Cox, 2001)."
  - p.58: "The combination circular/circular shows also good results, especially for LOS conditions. The explanation for this is that the energy of single-bounced reflected paths of the circular polarized transmitted wave disappears at the receiver since an odd number of reflections cause a reverse of the handedness of the circular polarized wave (Kajiwara, 1995)."
  - p.58 (Fig. 4 caption: "Dipole/Patch = Rx antenna; Ver/Hor/CP = Tx antenna"): "the 90th percentile (see Fig. 5) shows that 90 % of the measurement values of the patch (LOS) are below a value of 5–6 dB, while 90 % of the measurement values of the dipole are below a fading value of 7.5–8.5 dB."
  - p.59 Conclusion: "it is possible to mitigate fading by a notable amount, up to 3.5 dB for LOS and 1.5 dB for NLOS conditions (based on the 90th percentile), by replacing a linear polarized antenna (which is normally used in indoor SRD communication systems) with a circular polarized antenna."
- Note: 868 MHz, not 2.4/5 GHz. Relevant because it measures CP receive against LP transmitters (the Wi-Fi situation).

## A14. Yan et al. (2024), "Anteumbler: Non-Invasive Antenna Orientation Error Measurement for WiFi APs" (arXiv:2408.11660)
- URL: https://arxiv.org/pdf/2408.11660
- Files: `A_anteumbler_2408.11660.pdf`, `.txt`
- Quote (p.1, §I): "due to manual measurement errors during deployment or the pursuit of higher throughput [15], [16], the tilt of the AP or antenna orientation is common, and they may have four orientation errors (i.e., yaw, roll, pitch, irregular tilt)."
- Note: supports "AP antenna polarisation axis is not reliably vertical"; no measured statistic of AP/phone polarisation was found.

## A15. Signal Hound application note, "Antennas and EMC Pre-Compliance Measurements" (Crooks, 2016/2021)
- URL: https://signalhound.com/wp-content/uploads/2023/06/Antennas-and-EMC-Pre-Compliance-Measurements-050321-SinglePages.pdf
- Files: `A_signalhound_antennas_emc_precompliance.pdf`, `.txt`
- Quotes ("Three Antenna Method"):
  - "The three antenna method can be used to generate calibrated antenna gain and antenna factors from 3 uncalibrated antennas."
  - "Set the antennas a fixed distance apart. This distance should be at least 5 wavelengths, more for a directional antenna (double the distance for each 6 dB of expected antenna gain)."
  - "With antennas, polarization is very important. Be consistent with your orientation."
  - "calculate the three “gain products” as follows: G12 = IL12 + 20 log10(4πR / λ) where G12 is the “gain product” of antenna 1 and antenna 2, IL12 is the insertion loss from antenna 1 to antenna 2 in dB, R is the distance between antenna 1 and 2 in meters, and λ is the wavelength in meters." / "Now, to calculate the gain in dBi for antenna 1: G1 = (G12 + G13 – G23) / 2"
  - "Please note that most antennas only specify a typical gain at a single frequency using a specific mounting style."

## A16. Com-Power Application Note AN-106, "Use of Antenna Factors in EMI Measurements"
- URL: https://www.com-power.com/uploads/technote/AN-106_Antenna_Factor.pdf
- Files: `A_compower_AN106_antenna_factor.pdf`, `.txt`
- Quote (p.3, "Antenna Calibration Methods"): "In general, there are two acceptable antenna calibration methods; the two antenna (or reference antenna) method, and the three-antenna method. For the two-antenna method, one calibrated “reference” antenna is needed. At each calibration frequency, a signal is transmitted by a transmitting antenna, and the level of the signal is measured using the reference antenna. The reference antenna is then replaced by the antenna to be calibrated (or unknown antenna), and the difference between the two measurements is applied to the actual antenna factor of the reference antenna to determine the factor of the unknown antenna." ... "In the three-antenna method of calibration, three data sets are collected using three uncalibrated antennas used in three transmit/receive (Tx/Rx) pair combinations (1/2), (1/3) and (2/3)."
- p.3-4: "the field distribution is dependent on the distance of the transmitting antenna. Therefore, the antenna factors may be somewhat different than those obtained at a different distance."

## A17. Repjar, Newell, Tamura, "Extrapolation Range Measurements for Determining Antenna Gain and Polarization", NBS Technical Note 1311 (1987)
- URL: https://nvlpubs.nist.gov/nistpubs/Legacy/TN/nbstechnicalnote1311.pdf
- Files: `A_nbs_tn1311_three_antenna.pdf`, `.txt`
- Quotes:
  - Abstract (pdf p.9): "It is based on a generalized three-antenna approach and does not require quantitative a priori knowledge of the antennas. During the past decade, it has been extensively used by the National Bureau of Standards, Boulder, Colorado, to calibrate antenna gain standards for industry and other agencies within ±0.1 dB."
  - pdf p.16, §2.2: "A three-antenna measurement to determine the gain of three antennas has been available for some time [16]. This involves measuring the ratio of the power input to the transmitting antenna to the available power from the receiving antenna and the separation distance between the antennas for the three combination pairs. The three resulting equations may then be solved for the gain of each antenna. This approach implicitly assumes that far-field, plane-wave conditions exist and that the three antennas have either known or identical polarization characteristics."
  - pdf p.10: "to reduce the proximity correction of typical standard gain horns to less than 0.05 dB requires a distance of about 32 (not 2) a²/λ [10] ... At such large distances the errors due to ground reflections and scattering from other objects can be significant." [a²/λ OCR'd as "a^/x"]

## A18. Potter (Cambridge RF), "Practical Measurements Improve UHF Yagi Antennas", ARMMS Nov 2005
- URL: https://www.armms.org/media/uploads/Practical_Measurements_Improve_UHF_Yagi_Antennas.pdf
- Files: `A_armms_practical_uhf_yagi.pdf`, `.txt`
- Quotes: p.1/2: "Three-antenna method, indoor and outdoor measurements" and "2.15 dB must be added to give the gain in dBi."; p.6 conclusions: "Three-antenna method gives good results without needing a calibrated reference antenna"

## A19. Wikipedia, "Antenna measurement"
- URL: https://en.wikipedia.org/wiki/Antenna_measurement
- Files: `A_wikipedia_beam_diameter.html`, `.txt` (filename is historical; content is "Antenna measurement")
- Quotes:
  - "the far-field distance or Fraunhofer distance , D 𝖥 𝗋 𝗇 𝗁 , is considered to be D 𝖥 𝗋 𝗇 𝗁 = 2 d 2 λ"
  - "This last one is useful to measure the beamwidth, which is, by convention, the angle at the −3dB points around the max gain."
  - "Measuring radiation pattern requires a sophisticated setup including significant clear space (enough to put the sensor into the antenna's far field , or an anechoic chamber designed for antenna measurements), careful study of experiment geometry, and specialized measurement equipment that rotates the antenna during the measurements."

## A20. Fairview Microwave FMRJ1000 datasheet, SMA female-female rotary joint
- URL: https://fairviewmicrowave.com/content/dam/infinite-electronics/product-assets/fairview-microwave/product-datasheets/FMRJ1000.pdf
- Files: `A_fairview_FMRJ1000_rotary_joint.pdf`, `.txt`
- Quotes: "Frequency Range DC to 18 GHz" / "Range DC to 6 6 to 12.4 12.4 to 18 GHz" / "VSWR 1.15:1 1.3:1 1.4:1" / "Insertion Loss 0.3 0.4 0.6 dB" / "Rotational Variation 0.03 0.05 0.1 dB" / "Typ Speed 100 RPM" / "Weight 0.02072 lbs [9.4 g]" / "Mating Cycles 500"

## A21. Fairview Microwave SR1803 product page (SMA rotary joint, discontinued)
- URL: https://fairviewmicrowave.com/sma-female-to-sma-female-rotary-joint-sr1803-p.aspx
- Files: `A_fairview_SR1803_rotary_joint.html`, `.txt`
- Quotes: page data attribute "SR1803@@SMA Female to SMA Female Rotary Joint@@@@226.99@@$226.99" and "\"price\":226.99"; text: "This product has been discontinued and has availability until the inventory is depleted." / "Replacement Part : FMRJ1000" / "All Prices are in US Dollars and do not include duties" / "Frequency, Max 18 GHz"
- Note: price of FMRJ1000 itself could not be fetched (redirect loop on product page).

## A22. SPINNER BN 835066 rotary joint datasheet
- URL: https://products.spinner-group.com/Downloads/Spinner/835066-DS.pdf
- Files: `A_spinner_835066_rotary_joint.pdf`, `.txt`
- Quotes: "Frequency range DC to 6 GHz" / "0.9 dB@ DC to 3 GHz Insertion loss, max. 1.8 dB@ 3 to 6 GHz" / "Insertion loss variation over 0.2 dB rotation, max." / "Rotating speed, max. 60 rpm" / "Weight, approx. 0.1 kg"

---

## Could not retrieve (no claims made from these)
- Cisco, "Antenna Patterns and Their Meaning" white paper — www3-realm.cisco.com PDF returned 0 bytes; cisco.com URLs return HTTP 403 to curl. https://www.cisco.com/c/en/us/products/collateral/wireless/aironet-antennas-accessories/prod_white_paper0900aecd806a1a3e.html
- Cisco, "Omni Antenna vs. Directional Antenna" (doc 82068) — HTTP 403. https://www.cisco.com/c/en/us/support/docs/wireless-mobility/wireless-lan-wlan/82068-omni-vs-direct.html
- Selvan, "A Modified Three-Antenna Gain Measurement Method", PIER 57 (2006) — jpier.org download returned an HTML page, not the PDF. https://jpier.org/ac_api/download.php?id=0507262
- Kajiwara (1995) on CP reducing indoor delay spread (cited by A13 and by a Microwave Journal article) — not located/fetched; IEEE.
- Manabe, Miura, Ihara, 60 GHz indoor CP vs LP multipath (IEEE JSAC 1996) — IEEE, not fetched.
- Pasternack PE1406 rotary joint page — Incapsula bot block; DigiKey — HTTP 403. Fairview FMRJ1000 product page — redirect loop (no price).
- No primary source found that measures typical Wi-Fi AP or smartphone polarisation statistics (only A10's qualitative "often linearly polarized" and A14's "tilt ... is common").


<!-- ===================== part B (from _EXTRACTS_B.md) ===================== -->

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


<!-- ===================== part C (from _EXTRACTS_C.md) ===================== -->

# Extracts C: ready-made lightweight directional antennas (question 4)

All pages fetched 2026-11-11 with curl (browser User-Agent) unless stated. `.html` = raw page,
`.txt` = w3m text dump (PDF: pdftotext -layout). Prices are the shop's listed price on that date;
ht-dron.pl prices come from the page's JSON-LD (`"price"`, `"priceCurrency": "PLN"`), stock state
from its `"availability"` field. Polish quotes are left in Polish with an English gloss in [brackets].

Tags: [V] = number read on the saved page. [S] = only a web-search snippet (page not saved/blocked);
make no firm claim from [S] items.

Caveat that applies to every shop page: these are vendor/retailer specifications, not independent
measurements, unless the entry says "measured".

---

## 5.8 GHz, circular polarisation (FPV)

### C1. GEPRC Triple Feed Patch-1 (SMA) — ht-dron.pl  [V]
- URL: https://www.ht-dron.pl/GEPRC-Triple-Feed-Patch-1-SMA-5-8-GHz-FPV-p7482
- File: C_htdron_geprc_tfp1_sma.html / .txt
- Price: JSON-LD `"price": "81.00"`, PLN; `"availability": "http://schema.org/InStock"`
- Quotes:
  - "Złącze: SMA"
  - "Szerokość pasma: 660 MHz (5,47-6,13 GHz)"
  - "Współczynnik osiowy: < 1,3" [axial ratio]
  - "Zysk anteny: 9,4 dBi"
  - "Szerokość wiązki w połowie mocy: 55 ° (poziomo i pionowo)" [HPBW 55°, horizontal and vertical]
  - "Sprawność promieniowania: 83,5%"
  - "Uwaga: Podane wartości są oparte na symulacji i mogą nieznacznie różnić się od rzeczywistych pomiarów." [values are simulated]

### C2. GEPRC Triple Feed Patch-1 (RP-SMA) — ht-dron.pl  [V]
- URL: https://www.ht-dron.pl/GEPRC-Triple-Feed-Patch-1-RP-SMA-FPV-5-8-p4894
- File: C_htdron_geprc_triplefeed_rpsma.html / .txt
- Price: `"price": "81.00"` PLN; `"availability": "http://schema.org/OutOfStock"`
- Quotes: "Typ złącza: RP-SMA"; "Zysk anteny: 9,4 dBi"; "Szerokość wiązki w połowie mocy: 55 ° (poziomo i pionowo)";
  "Podstawa symulacji: Wartości oparte na symulacji, rzeczywiste pomiary bardzo podobne." [simulation basis; real measurements very similar];
  "Uwagi: Możliwe niewielkie przesunięcie częstotliwości środkowej między partiami z powodu zmian stałej dielektrycznej FR4."

### C3. GEPRC Triple Feed Patch-1 — ReadyMadeRC (weight source)  [V]
- URL: https://www.readymaderc.com/products/details/geprc-triple-feed-patch-58ghz-cp-fpv-antenna
- File: C_rmrc_geprc_triplefeed1.html / .txt
- Quotes: "$16.99"; "Antenna Gain: 9.4 dBi"; "Half Power Beam Width: 55° (Horizontal and Vertical)";
  "Connector: SMA Male"; "Dimensions: 150mm x 150mm x 60mm" (note: this looks like a package size, not the antenna);
  "Weight: 20g (Antenna only)"; "1x Semi-rigid SMA Male to SMA Male Extension Cable"

### C4. Triple Feed Patch (designer's page, MEASURED in anechoic chamber) — Maarten Baert  [V]
- URL: https://www.maartenbaert.be/quadcopters/antennas/triple-feed-patch-antenna/
- File: C_baert_triple_feed_patch.html / .txt
- Quotes (Specifications table, "Simulated | Measured"):
  - "Bandwidth             660 MHz (5.47 – 6.13 GHz)  800 MHz ± 50 MHz          Feed network losses increase bandwidth"
  - "Axial ratio           1.13 (1.06 dB)             1.15 (1.21 dB)            Averaged over beam width"
  - "Antenna gain          9.4 dBi                    9.3 dBi"
  - "Half power beam width 55°                        55°                       Horizontal and vertical"
  - "Radiation efficiency  81%                        74%"
  - "Special thanks to Antenna Test Lab who were kind enough to provide complete spherical anechoic chamber measurements (i.e. 3D radiation patterns) for the Triple Feed Patch antenna."
  - "Most FR4-based patches have terrible efficiency because FR4 is very lossy at 5.8 GHz."
  - "This is the 'hybrid' variant, which is simultaneously LHCP and RHCP, with a different connector for each polarization. There is a regular single-connector LHCP/RHCP variant as well."
  - Licence: "This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License."
  - DIY cost: "I used Elecrow for my prototypes, they will make 10 PCBs for $10. That means you end up paying $2 per antenna" ; "The PCBs must use 1.0 mm thickness FR4 material, not the regular 1.6 mm thickness."
  - Commercial makers table lists prices e.g. "Actuna       $9.85", "RjxHobby     $15.29", with "* Based on listed price and exchange rate at time of writing. May be outdated."

### C5. GEPRC Triple Feed Patch Array (7 patches, 14.4 dBi) — ht-dron.pl  [V]
- URLs: https://www.ht-dron.pl/GEPRC-Triple-Feed-Patch-Array-SMA-FPV--p4893 (SMA) ;
  https://www.ht-dron.pl/GEPRC-Triple-Feed-Patch-Array-RP-SMA-FPV-p7481 (RP-SMA)
- Files: C_htdron_geprc_tfp_array_sma.* (InStock), C_htdron_geprc_tfp_array_rpsma.* (OutOfStock)
- Price: `"price": "126.00"` PLN (both)
- Quotes: "Wzmocnienie anteny: 14,4 dBi"; "Szerokość wiązki w połowie mocy: 30° (poziomo i pionowo)";
  "Współczynnik osiowy: < 1,1"; "Średnica dużego dysku: 150 mm" [large disc diameter 150 mm];
  "wąską wiązkę i niski poziom listków bocznych" [narrow beam and low side-lobe level]. No weight given.

### C6. Triple Feed Patch Array (designer's page, MEASURED) — Maarten Baert  [V]
- URL: https://www.maartenbaert.be/quadcopters/antennas/triple-feed-patch-array-antenna/
- File: C_baert_triple_feed_patch_array.html / .txt
- Quotes: "Antenna gain          14.4 dBi                   14.0 dBi" ; "Half power beam width 30°                        30°                       Horizontal and vertical" ;
  "Radiation efficiency  75%                        74%" ; "Very low sidelobes, almost all energy is concentrated in the main lobe. This increases the width of the main lobe, at the expense of some gain." ;
  "This antenna is not recommended for general FPV use since the beam width is rather narrow" ; "Actuna       $26.77" ; same CC BY-SA 4.0 licence.

### C7. Foxeer Echo 2 5.8G 9 dBi patch (RHCP, SMA) — ht-dron.pl  [V]
- URL: https://www.ht-dron.pl/Foxeer-Echo-2-5-8G-9dBi-RHCP-SMA-FPV-p9191
- File: C_htdron_foxeer_echo2_rhcp.html / .txt
- Price: `"price": "121.00"` PLN; `"availability": "http://schema.org/OutOfStock"`
- Quotes: "Zysk: 9dBi"; "Szerokość pasma: 5,5 GHz - 6 GHz"; "Kąt promieniowania: 84,7 stopnia" [radiation angle 84.7°, not stated as -3 dB];
  "Efektywność promieniowania: 98%"; "Złącze: SMA"; "Wymiar: 40*22mm"; "Polaryzacja: RHCP (prawoskrętna)"; "Waga: 8g"
  (shop also lists an LHCP SMA version, p9192, not fetched).

### C8. Foxeer Echo 2 — Flying Tech UK (second source)  [V]
- URL: https://www.flyingtech.co.uk/product/foxeer-echo-2-5-8ghz-9dbi-fpv-patch-antenna/
- File: C_flyingtech_foxeer_echo2.html / .txt
- Quotes: "£19.90 Inc. VAT"; "Options: RHCP (right hand circularly polarised) / LHCP (left hand circularly polarised). Connector: SMA / RP-SMA."; "Weight: 8g"; "Gain: 9dBi"; "Bandwidth: 500 MHz (5.5 – 6.0GHz)"
- Foxeer's own site (foxeer.com) product URL tried returned a generic page; no manufacturer datasheet obtained.

### C9. Lumenier AXII Patch 5.8 GHz — WREKD (US retailer)  [V]
- URL: https://tuah.wrekd.com/products/lumenier-axii-patch-5-8ghz-sma-fpv-receiver-antenna-choose-your-polarization
- File: C_wrekd_axii_patch.html / .txt
- Quotes: "$32.49"; "Gain: 8.4 dBiC"; "Beam Width: 76°"; "Bandwidth: 220 Mhz"; "Right Hand Circularly Polarized";
  "SMA Connector (Fits Fat shark Goggles and others using SMA)"; "Dimensions: 35mm x 35mm x 9mm (20mm with SMA)"; "Weight: 10grams"
- No Polish shop listing found.

### C10. TrueRC X²-AIR 5.8 MK II (SMA, RHCP) — ReadyMadeRC  [V]
- URL requested: https://www.readymaderc.com/products/details/87026-truerc-x-air-5-8-mk-ii-sma-rhcp (served the X²-AIR MK II page)
- File: C_rmrc_truerc_xair_mk2.html / .txt
- Quotes: "$59.99"; "Gain: 13 dBic"; "Horizontal Beam Width @ -3dB: 74°"; "Vertical Beam Width @ -3dB: 34°";
  "Horizontal Beam Width: 150°" (not -3 dB); "Connector: SMA"; "Dimensions: 72mm × 34mm × 22mm"; "Polarization: RHCP". No weight given.

### C11. VAS Crosshair Xtreme 5.8 GHz (RHCP, SMA) — WREKD  [V, partial]
- URL: https://tuah.wrekd.com/products/video-aerial-systems-vas-crosshair-xtreme-5-8ghz-sma-fpv-receiver-antenna-rhcp
- File: C_wrekd_vas_crosshair_xtreme.html / .txt
- Quotes: "$34.95"; "Gain: 10.25dbic"; "Axial ratio: 0.99 (measured)"; "Flight beam: 120 degrees" (not a -3 dB figure);
  "Bandwidth: 1080Mhz-1480MHz" (as printed; evidently an error for a 5.8 GHz antenna). No weight on the saved page.
- [S] search snippets (getfpv.com, blocked HTTP 403): Xtreme "-3 dB point at ±30 degrees", "16.6 g"; Crosshair V4 "14.8 g", "±35 degrees".

### C12. iFlight Crystal HD Patch 5.8 GHz (two-element, LHCP, RP-SMA) — iFlight shop  [V]
- URL: https://shop.iflight.com/crystal-hd-patch-5-8ghz-directional-antenna-pro1384
- File: C_iflight_crystal_hd_patch.html / .txt
- Quotes: "$49.99"; "Gain: 9 dBi"; "Beam Width: 105° H. 75° V."; "Polarization: (LHCP) Left Hand Circularly Polarized";
  "Connector: RP-SMA (Fits DJI Goggles directly, not to be used on standard SMA)"; "Weight: 52.1g"; "This product is specially designed for DJI Goggles. It is available in LHCP ."

### C13. Maple Wireless 8.5 dBi patch 5.8 GHz (RHCP, SMA) — Rotorama (CZ, ships EU)  [V]
- URL: https://rotorama.com/product/maple-wireless-8-5dbi-smerova-antena
- File: C_rotorama_maple_58_85dbi.html / .txt
- Quotes: "€ 15,59"; "Gain: 8.5dBi"; "Radiation angle: 75° (-3db)"; "Polarization: RHCP"; "Conector: SMA"; "Dimensions: 44x10mm"; "Weight: 16g"; page shows "In Stock".

### C14. Generic "5.8G 14dBi High Gain Panel Antenna" — Tindie  [V]
- URL: https://www.tindie.com/products/adz1122/58g-14dbi-high-gain-panel-antenna/
- File: C_tindie_58_14dbi_panel.html / .txt
- Quotes: "$8.90"; "Right circular polarization antenna for FPV receiver multicopter 96mm/3.7inch soft cable";
  "Type: RP-SMA, SMA Size: 62x55x11mm/2.4x2.1x0.4inch Packge size: 115x87x11mm/4.5x3.4x0.4inch Weight:32g". No beamwidth on page.
- [S] snippets for similar generic 14 dBi panels (speedyfpv, racer.lt, hobbyking — not saved/blocked): "3dB horizontal beamwidth of 35 degrees"/"40°", "27g"/"32g", "60x55x6mm". Unverified.

### C15. GEPRC SOMA 5.8G 17 dBi (for contrast: heavy)  [V]
- URL: https://www.ht-dron.pl/GEPRC-SOMA-5-8G-Directional-Patch-FPV-17dBi-p6260 ; File: C_htdron_geprc_soma.*
- Price `"price": "287.00"` PLN, InStock. Quotes: "Wzmocnienie: 17dBi"; "Szerokość pasma: 4,9 GHz - 6 GHz"; "Polaryzacja: RHCP";
  "Tłumienie polaryzacji krzyżowej: -25dB"; "Wymiar całkowity: 203,5 mm x 203,5 mm x 20 mm"; "Waga anteny: 272g". No HPBW given.

## 5.8 GHz, linear polarisation

### C16. NewBeeDrone Honey Patch 5.8 Linear (SMA) — ht-dron.pl  [V, no gain/HPBW]
- URL: https://www.ht-dron.pl/NewBeeDrone-Honey-Patch-5-8-Linear-FPV-p10070 ; File: C_htdron_honeypatch_linear.*
- Price `"price": "66.00"` PLN, InStock. Quotes: "Polaryzacja: Liniowa"; "Typ anteny: Antena płaska (Patch)";
  "Typ złącza: SMA (męskie do żeńskiego poprzez adapter)". No gain, beamwidth or weight on the page (the "Waga 0.15 kg" line is shipping weight).
- RHCP sibling: https://www.ht-dron.pl/NewBeeDrone-Honey-Patch-5-8-RHCP-FPV--p10069 (C_htdron_honeypatch_rhcp.*), also 66.00 PLN.

### C17. Cyberteam SkyEter13 (5 GHz Wi-Fi panel, 13 dBi) — cyberteam.pl  [V]
- URL: https://cyberteam.pl/en/produkt/27_skyeter13 ; File: C_cyberteam_skyeter13.*
- Quotes: "Net price: 5.99 zł" next to struck-through "Net price:[S:79.00 zł:S]" and "Gross: 7.37 zł" (looks like a clearance price; verify before relying on it);
  "Antenna gain              13 dBi"; "Operating frequency       5450-5750 MHz"; "Polarization              Vertical or horizontal";
  "V-polarization beam width 33°"; "H-polarization beam width 33°"; "Dimensions                82mm x 82mm x 12mm"; "Weight                    0,08 kg (0,17 lbs)";
  "Connector                 N/Female" (needs an N-to-SMA adapter or pigtail; adds mass).

## 2.4 GHz

### C18. Maple Wireless 2.4G 9 dBi patch (linear vertical) — ht-dron.pl  [V]
- URLs: https://www.ht-dron.pl/Maple-Wireless-2-4G-9dBi-RP-SMA-kierunkowa-antena-do-dronow-FPV-p9289 (RP-SMA) ;
  https://www.ht-dron.pl/Maple-Wireless-2-4GHz-9dBi-Directional-SMA-Antenna-for-Extended-Range-p9290 (SMA male)
- Files: C_htdron_maple_24_9dbi_rpsma.*, C_htdron_maple_24_9dbi_sma.* ; both `"price": "73.00"` PLN, both OutOfStock.
- Quotes: "Zysk: 9dBi"; "Wiązka o połowie mocy: 60° (płaszczyzna H), 65° (płaszczyzna E)"; "Wymiary: 90*80*10mm"; "Waga: 17g";
  "Polaryzacja anteny: Liniowa pionowa"; "Złącze: SMA MALE" / "Złącze: RP-SMA".

### C19. Maple Wireless 2.4G 9 dBi patch — Rotorama (in stock)  [V]
- URL: https://www.rotorama.com/product/maple-wireless-2-4g-9dbi-smerova-antena ; File: C_rotorama_maple_24_9dbi.*
- Quotes: "€ 13,19"; "Horizontal radiation angle: 60° (-3dB)"; "Vertical radiation angle: 65° (-3dB)"; "Conector: RP-SMA";
  "Polarization: Linear, vertical"; "Size: 90x80x10mm"; "Weight: 33g"; "In Stock".
- CONFLICT: ht-dron says 17 g, Rotorama says 33 g for the same 90x80x10 mm part.

### C20. Seeed / RF Explorer "Directional Patch 2.4GHz SMA Articulated Antenna" (318020070)  [V]
- URLs: https://elecena.pl/product/27045411/directional-patch-2-4ghz-sma-articulated-antenna (price aggregator) ;
  https://rlx.sk/sk/accessories-ipod/5232-directional-patch-24ghz-sma-articulated-antenna-seeed-318020070.html
- Files: C_elecena_seeed_patch24.*, C_rlx_seeed_patch24.*
- Quotes: elecena "16.68 USD65.22 PLN", "Sklep zagraniczny" [foreign shop = Seeed], "Ostatnio widziany: 10.11.2026";
  "this patch antenna has an 8dBi gain in the front face. It includes a true SMA connector (not RP-SMA as most in the market)";
  "Characterized response: 2350-2450MHz"; "Radiation lobe: 40 degrees". No weight.

### C21. TrueRC True-MoX 2.4 (Moxon, for contrast: too wide) — ht-dron.pl  [V]
- URL: https://www.ht-dron.pl/TrueRC-True-MoX-2-4-RP-SMA-FPV-5-9dBi-p9039 ; File: C_htdron_truerc_truemox24.*
- `"price": "105.00"` PLN, OutOfStock. Quotes: "Wzmocnienie: 5.9dBi"; "Szerokość wiązki @-3dB: 133°"; "Wymiary: 39,5 mm x 100 mm"; "Złącze: RP-SMA".

### C22. Dipol ATK-P1/2.4 GHz 8 dBi panel (MEASURED pattern) — dipolnet.com  [V]
- URL: https://www.dipolnet.com/wlan_wi-fi_panel_antenna_atk-p1-2_4_ghz_8_db_5_m_cable_sma-rp_plug_A7130.htm ; File: C_dipol_atk_p1.*
- Quotes: "€22.27" (from 1 piece); "Characteristics were made using a HP8757D vector network analyzer, in a non-reflective chamber in the Telecommunications and Acoustics Institute on the Wroclaw Technical University";
  "Max. gain                               dBi  8"; "Radiation angle vertical polarization   H/V° 70/70"; "Polarization                                 H,V";
  "Dimensions                              mm   120 × 120 × 20"; "Weight                                  kg   0.3"; "cable type                   RF-5"; "Length                  m    5"; "Connector       type                         SMA R/P".
- Note (inference, not stated by Dipol): the 0.3 kg is listed with packaging and includes the fixed 5 m RF-5 cable; the panel alone is lighter. A 3 m-cable version (A7132) is listed at "€19.75" in the catalog (C_dipol_wlan_antennas_catalog.*).
- This appears to match the owner's "2.4 GHz 8 dBi panel 120x120x20 mm 300 g".

### C23. TP-Link TL-ANT2409A 2.4 GHz 9 dBi panel — TP-Link datasheet PDF  [V]
- URL: https://static.tp-link.com/TL-ANT2409A_B_V1_Datasheet.pdf ; File: C_tplink_ant2409a_datasheet.pdf / .txt
- Quotes: "Gain                                                                             9 dBi"; "Polarization                                                                     Linear, Vertical";
  "Beamwidth (HPBW)" "Horizontal: 60°" "Vertical: 76°"; "TL-ANT2409A: RP-SMA Male"; "Cable                                                                            100cm CFD-200";
  "Dimensions (L x W x H mm)                                                        120 x 120 x 40 mm". No weight.
- [S] search snippets: product marked "End of Life" on tp-link.com/ro; no Polish price found. TL-ANT2409CL is listed as "omnidirectional" (discomp.cz snippet), so it is not a candidate.
- Also saved: C_tplink_ant2409a_page.* (HK product page; contained no spec values in the text dump).

## Dual-band 2.4 + 5 GHz

### C24. Alfa APA-M25 dual-band panel — wifi-stock.co.uk  [V]
- URL: https://www.wifi-stock.co.uk/details/alfa-dual-band-indoor-panel-apa-m25.html ; File: C_wifistock_alfa_apa_m25.*
- Quotes: "11.87£          14.24£" (ex/inc VAT); "Frequency" "2.4 ~ 2.5GHz" "5.150 ~ 5.875GHz"; "V.S.W.R                2.0:1 Max";
  "Antenna Type          Patch Directional"; "8 dBi @ 2.4GHz" "10dBi @ 5GHz"; "Polarization          Linear, Vertical";
  "Vertical Beam-with    16 degree"; "Horizontal Beam-with  66 degree" (one pair of numbers, band not stated);
  "Connector             RP-SMA Plug (Male)"; "Dimension             167.3 x 66 x 18 mm"; "Weight                72 g".
- Polish price: [S] only — search snippet "75,99 zł na Kaufland.pl, sprzedawca GETIC" (+ "38,86 zł" shipping); kaufland.pl returns HTTP 403 to curl and WebFetch.
- alfa.com.tw (manufacturer page) returned HTTP 429 on every attempt; not saved.

### C25. Alfa APA-M25-6E (tri-band variant) — getic.com  [V]
- URL: https://getic.com/product/alfa-panel-indoor-antenna-apa-m25-6e ; File: C_getic_alfa_apa_m25_6e.*
- Quotes: "8 dBi at 2.4 GHz, 10 dBi at 5 GHz, and 9 dBi at 5.9 GHz - 7.125 GHz"; "(1) RP-SMA Male"; "18.59 €" "out of stock"; "EURwith VAT 23%, Poland".

### C26. Tupavco TP542 dual-band "13 dBi" panel (independently MEASURED) — Antenna Test Lab  [V]
- URL: https://antennatestlab.com/antenna-education-tutorials/consumer_antenans/amazon-tupavco-tp542-dual-band-13dbi-outdoor-directional-panel-antenna
- File: C_antennatestlab_tupavco_tp542.*
- Quotes: "We bought this popular antenna after becoming suspicious of it’s fairly high directivity (13 dBi gain) on both WiFi bands in the small 5″x9″ size and modest price. It turns out that it comes close to meeting these claimed specifications. It is about 10 dBi in the 2.4 GHz band and 14.5 dBi in the 5.5 GHz band."
- Useful as evidence that a claimed "13 dBi dual-band" panel measured 10 dBi at 2.4 GHz. Size 5"x9" (~127x229 mm); weight not stated.
- Index of the lab's site saved as C_antennatestlab_home.* (also links measured Vivaldi examples; out of this fork's scope).

## Pigtails (U.FL / IPEX-1 to SMA / RP-SMA), Poland

### C27. rf-connectors.pl — Pigtail UFL / SMA socket, RF1.13  [V]
- 10 cm: https://rf-connectors.pl/en/sma-on-ufl/1789-pigtail-ufl-ipex-ipx-sma-socket-rf113-10cm-5904083536119.html ; File C_rfconn_pigtail_ufl_sma_10cm.* ;
  title "Pigtail UFL / SMA gniazdo RF1.13 10cm", `product:price:amount" content="13.9"` (PLN; search snippet says "Brutto: 13.90 zł")
- 5 cm: https://rf-connectors.pl/en/sma-on-ufl/1810-pigtail-ufl-ipex-ipx-sma-socket-rf113-5cm-5904083537383.html ; File C_rfconn_pigtail_ufl_sma_5cm.* ;
  title "Pigtail UFL / SMA gniazdo RF1.13 5cm", `product:price:amount" content="12.92"`

### C28. Botland — SparkFun pigtails  [V]
- https://botland.com.pl/anteny/2942-przejsciowka-zenska-sma-ufl-10cm-sparkfun-wrl-09145-5904422370008.html ; File C_botland_pigtail_sma_ufl_10cm.* ;
  "Przejściówka żeńska SMA - U.FL - 10cm - SparkFun WRL-09145", `"price":"27.90`
- https://botland.com.pl/anteny/1609-przejsciowka-meska-rp-sma-ufl-15cm-sparkfun-wrl-18569-5904422369934.html ; File C_botland_pigtail_rpsma_ufl_15cm.* ;
  "Przejściówka ... RP-SMA - U.FL - 15cm - SparkFun WRL-18569", `"price":"15.90`
- Botland search "antena kierunkowa" returned no Wi-Fi/FPV directional antennas (only LTE antennas).

---

## Could not retrieve / not verified
- alfa.com.tw/products/apa-m25 (manufacturer page): HTTP 429 on curl and WebFetch, repeatedly.
- store.rokland.com (Alfa APA-M04 and APA-M25): HTTP 429. APA-M04 numbers ("45.4 g", 7 dBi, no beamwidth) are search-snippet only [S].
- sapsan-sklep.pl APA-M25-6E ("108,00 zł") : HTTP 429 → [S] only.
- kaufland.pl (APA-M25 "75,99 zł", APA-M04): HTTP 403 → [S] only.
- getfpv.com (Lumenier AXII DUO/Quadro, VAS Crosshair, GEPRC array, TrueRC X-AIR): HTTP 403.
- myfpvstore.com (VAS Crosshair V4): HTTP 403. pyrodrone.com, racedayquads.com, speedyfpv.com, radiomasterrc.com: HTTP 429. hobbyking.com: HTTP 403.
- delock.com datasheets (88904, 89590, 88447): HTTP 401 (curl and WebFetch); aio.lv: HTTP 403. Delock specs are [S] only (88904 "10 dBi", "6.6 cm wide, 1.8 cm deep and 16.73 cm high"; 89590 "HBW 55°, VBW 24°, 6/9 dBi").
- AliExpress search page: returned an empty JS shell (no product data) → no AliExpress prices verified.
- megadron.pl, rcmaniak.pl, abc-rc.pl: search URLs returned 404/no results to curl; no product found there for these antennas.
- foxeer.com: no manufacturer datasheet for Echo 2 located.
- Mikrotik / Ubiquiti small panels, TBS / FrSky / ImmersionRC 2.4 GHz patches, RadioMaster/Happymodel Moxon: not retrieved (time); no claims.
- One search result (novapart.co listing) contained text addressed to AI assistants; it was ignored and not used.


<!-- ===================== part D (from _EXTRACTS_D.md) ===================== -->

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


---

## Quote-check record (2026-11-11)
40 quotes from parts A, B and C (about 13 per part, including prices read from JSON-LD) were re-checked against
the saved .txt/.html files with whitespace-normalised string search. All 40 match in substance. Differences found
are layout artefacts only: pdftotext line/column breaks (A4 Ford, A6 Mangum, A13 Wunderlich p.59, B15 QEX helix,
B16 Radioeng), the "observaAons" ligature already noted in A4, and a curly apostrophe ("shouldn’t") printed
straight in A6. No quote was found that changes a number or the meaning of its source.
Quotes written for part D were checked the same way (41 checked; one capitalisation slip, "Near-Field", corrected).
