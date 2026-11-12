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
