# EXTRACTS — imaging science for RadioMicroscope v2

Collected 2026-11-11. Every quote below is copied from the local file named with it (PDF text via
`pdftotext`; line breaks and hyphenation from the two-column layout joined; nothing else changed).
`[...]` marks an omission. Where a PDF symbol did not extract cleanly this is noted.
Evidence tags: **[V]** read at source in the local file; **[S]** snippet only. All entries below are [V]
unless marked otherwise.

Note on the brief: the arXiv id given for Holl & Reinhard (1608.06920) is wrong; it is a paper on
Liénard-type equations (downloaded, checked, deleted). The correct preprint is arXiv:1612.03194.

---

## A. Wi-Fi holography (scanned antenna + fixed reference antenna)

### A1. Holl & Reinhard, "Holography of Wi-Fi radiation" (PRL 118, 183901, 2017; preprint v2)
- URL: https://arxiv.org/pdf/1612.03194v2 — DOI 10.1103/PhysRevLett.118.183901 (APS PDF returned an HTML block page; the arXiv v2 was read)
- File: `holl2017_wifi_holography.pdf` / `.txt`
- Fig. 1 caption: "We record a hologram of Wi-Fi radiation by a synthetic aperture approach. A Wi-Fi antenna (scanning antenna) is moved across a 3 by 2 meter plane, point-wise registering Wi-Fi signals. The signal phase is recovered by a homodyne scheme, normalizing the signals to the signal of a stationary antenna (reference antenna)."
- Intro: "Our method does not require any prior knowledge of the emitted radiation and works with any type of signal, including encrypted communication."
- Results: "Its extension (σ = 3cm) is close to the diffraction limit set by the size of the recording plane and comparable to the Wi-Fi wavelength, allowing for cm-scale localization of its position in 3D space." (σ subscript garbled in extraction)
- Results: "the emitter focus (bright spot in Fig 3b-d) contains only 15% of the received intensity."
- Multipath: "The amplitude modulation has a standing wave ratio of SWR=9.7. It creates artefacts in the recovered phases"
- Bandwidth: "(Δf ≈ 70MHz)"
- Outlook: "a stationary two-dimensional array of antennae could replace our slow synthetic aperture approach of mapping a wavefront by pointwise scanning."
- SI (hardware): "The mixing stage consists of a high-frequency local oscillator set to approximately 2.4 and 5 GHz, respectively. Its output is split and then fed into two equal mixers, one for each antenna."
- SI (speed): "The trigger setup limits the data acquisition rate to about two points per second on average."
- SI Table 1: oscilloscope "Rigol DS4034, 350 MHz bandwidth, 4 GSa/s"; amplifiers/mixers/oscillators "Mini-circuits ZX60-43-S+", "ZX05-C42-S+", "ZX95-2500A-S+" (2.4 GHz set).

### A2. Zhong, He, Li, "Through-the-Wall Imaging Exploiting 2.4GHz Commodity Wi-Fi" (cites A1)
- URL: https://arxiv.org/pdf/1903.03895 — File: `cites_holl_1903.03895.pdf` / `.txt`
- Abstract: "a pair of antennas in a synthetic aperture mode is used to acquire signals produced by commodity Wi-Fi devices and reflected from the scene in a synthetic aperture mode."
- Sec. II: "the proposed Wi-Fi signal based through-the-wall imaging system consists of three main components: a conventional oscilloscope, Wi-Fi routers, and two receiving horn antennas. In our experiments, the scene of interest is located behind a 6cm-thick wooden wall." [...] "Two horn antennas are connected to the two ports of the oscilloscope (AgilentTM MSO9404A) [...] One receiving antenna is kept fixed and used for providing the reference signal."
- Sec. III: "Fig. 4 shows that the two objects can be separated reasonably well for a cross range separation of 10cm."

### A3. Wang, Paulus, Eibert, "Phase-Corrected Near-Field Microwave Imaging via Inverse Source Reconstruction with Modulated Signals" (EuCAP 2026; cites A1)
- URL: https://arxiv.org/pdf/2605.03875 — File: `cites_holl_2605.03875.pdf` / `.txt`
- Abstract: "The modulated signals from a non-cooperative transmitter are scattered by the targets of interest and captured by a fixed reference antenna together with an NF scanning probe at different positions. By normalizing with the reference signals, spatial coherence of the NF observations is obtained" [...] "it is shown that for realistic narrowband signals, an incoherent imaging approach is sufficient."
- Sec. IV: "For the Rx, an SDR based on an AD9361 [22] with two coherent receive channels and with a sampling rate of 15.36 MHz was employed. The fixed reference antenna and the moving probe antenna were connected to the SDR and automatic gain control of the receive channels was disabled."
- Sec. IV: "The planar measurements were performed with a sampling step of approximately λ/4 which lead to 162 × 80 sampling points uniformly distributed over a rectangular area of approximately 4.98 m × 2.46 m"

### A4. Wang, Tong, Eibert, "3-D Near-Field Passive Radar Imaging Using Multiple Illumination Sources" (AP-S 2025)
- URL: https://arxiv.org/pdf/2603.08217 — File: `cites_holl_2603.08217.pdf` / `.txt`
- Downloaded; only the first page was read. No claim is made from it.

---

## B. Commodity-Wi-Fi AoA / SAR / ToF localisation

### B1. Kotaru et al., "SpotFi: Decimeter Level Localization Using WiFi" (SIGCOMM 2015)
- URL: https://web.stanford.edu/~skatti/pubs/sigcomm15-spotfi.pdf — File: `kotaru2015_spotfi.pdf` / `.txt`
- Intro: "RSSI based systems are deployable and universal, but are not accurate; their median accuracy ranges from 2–4 m"
- Intro: "ArrayTrack uses six to eight antennas whereas typical APs have three, and LTEye requires motorized rotating antennas which are not found on deployed APs."
- Intro: "SpotFi, an indoor localization system that provides a median accuracy of 40 cm using standard, commodity off-the-shelf WiFi radios"
- Sec. 3 (impl.): "We use Intel 5300 WiFi chips in the current prototype because of the availability of CSI extraction software"
- Eval summary: "super-resolution AoA estimation algorithm whose median error is less than 5 degrees in LoS conditions and less than 10 degrees in NLoS conditions."
- Sec. 4.3: "ArrayTrack with six-eight antennas and Ubicarse/LTEye with rotating antennas achieve between 0.3–0.4 m median accuracy"
- Sec. 3 (STO): "STO adds a constant offset to the ToF estimates of all the [...] The additional phase induced by STO is the same across antennas"

### B2. Xiong & Jamieson, "ArrayTrack: A Fine-Grained Indoor Location System" (NSDI 2013)
- URL: https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final51.pdf — File: `xiong2013_arraytrack.pdf` / `.txt`
- Abstract: "With a combination of FPGA and general purpose computing, we have built a prototype [...] to within 23 centimeters median accuracy, with the system incurring just 100 milliseconds latency"
- Sec. 4: "We place the 16 antennas attached to the WARP radios in a rectangular geometry [...] Antennas are spaced at a half wavelength distance (6.13 cm)"
- Sec. 4 (calibration): "Each radio receiver incorporates a 2.4 GHz oscillator [...] it introduces an unknown phase offset to the resulting signal, rendering AoA inoperable. [...] Our solution is to calibrate the array with a USRP2 generating a continuous wave tone, measuring each phase offset directly."

### B3. Vasisht, Kumar, Katabi, "Decimeter-Level Localization with a Single WiFi Access Point" (Chronos, NSDI 2016)
- URL: https://courses.grainger.illinois.edu/CS598WSI/sp2021/Papers%5CChronos_NSDI16.pdf (course mirror of the USENIX open-access PDF; usenix.org returned HTML) — File: `vasisht2016_chronos.pdf` / `.txt`
- Results: "Chronos computes the time-of-flight with a median error of 0.47 ns in line-of-sight and 0.69 ns in non-line-of-sight settings. This corresponds to a median distance error of 14.1 cm and 20.7 cm respectively." / "a median error of 65 cm in line-of-sight and 98 cm in non-line-of-sight settings."
- Sec. 4: "Chronos must ensure both the WiFi transmitter and receiver hop synchronously between multiple WiFi frequency bands. Chronos achieves this using a frequency band hopping protocol driven by the transmitter."
- Impl.: "We implemented Chronos as a software patch to the iwlwifi driver on Ubuntu Linux"

---

## C. ESP32 phase coherence, CSI phase, and the new ESP-SDR

### C1. Euchner, Schneider, Gauger, ten Brink, "ESPARGOS: An Ultra Low-Cost, Realtime-Capable Multi-Antenna WiFi Channel Sounder" (2025)
- URL: https://arxiv.org/pdf/2502.09405 — File: `euchner2025_espargos_channel_sounder.pdf` / `.txt`
- Sec. I: "Simply using multiple WiFi cards or microcontrollers without taking additional precautions does not produce phase-coherent CSI due to lack of synchronization – data acquired this way would be unusable for many JCaS algorithms, including e.g. angle of arrival (AoA) estimation. Proposed workarounds like antenna switching [10] come with their own downsides, such as requiring multiple frame transmissions for one sensing operation."
- Sec. II-A: "Reference clock distribution is insufficient for achieving phase coherence" [...] "By measurement it was determined that, indeed, the initial phase changes after a chip reset and after modifying the LO frequency (WiFi channel)" [...] "Hence, an additional, periodically performed phase calibration step is vital to ensure phase coherence."
- Sec. II-B: "each ESP32 is connected to an RF switch that can alternate between the ceramic antenna and a WiFi-based phase reference signal provided to every receiver using a distribution network made up of a resistive divider and microstrip transmission lines."
- Sec. III-A (per-packet phase): "rm[t] is affected by the initial phase φ of the transmitter, which is different for every time index t and unknown due to unknown oscillator frequency offset and oscillator drift. As a consequence, all channel coefficients for one particular time instance may be phase-rotated by a common factor e^jφ."
- Sec. IV-B: "we only consider a simple qualitative test, namely whether ESPARGOS can distinguish between three different transmitter placements." / Sec. V: "Quantitative performance testing and further characterizations of the system remain a subject for future study."

### C2. Euchner & ten Brink, "ESPARGOS: Phase-Coherent WiFi CSI Datasets for Wireless Sensing Research" (2024)
- URL: https://arxiv.org/pdf/2408.16377 — File: `euchner2024_espargos_datasets.pdf` / `.txt`
- Sec. II: "array consists of eight antennas, each connected to an off-the-shelf WiFi-capable microcontroller (Espressif ESP32-S2), arranged into two rows of four antennas"
- Sec. II: "by clocking all microcontrollers from the same crystal oscillator and by distributing a phase reference signal to compensate for phase ambiguities introduced by the phase locked loops (PLLs), the CSI measurements are synchronized in phase."

### C3. ESPARGOS One product page (HTML text saved)
- URL: https://espargos.net/espargos-one/ — File: `espargos_net_espargos-one.txt`
- "Work with WiFi channel state information (CSI) and coherent raw I/Q samples to explore wireless signals. Available now from €350 (excl. VAT, EU-only)."
- "Core Kit A single ESPARGOS One antenna array with 8 dual-polarized antennas in a 4×2 grid." [...] "€350 excl. VAT"
- Specs: "Designed for 2.402–2.482 GHz (2.4 GHz ISM band)." / "Raw I/Q samples synchronized across eight channels (low-duty-cycle capture)" / "λ / 2 antenna spacing (60 mm)" / "Power consumption: ~3.5 W"

### C4. ESP-SDR — README of github.com/ESPARGOS/esp-sdr (repo pushed 2026-11-09)
- URL: https://github.com/ESPARGOS/esp-sdr (raw README) — File: `github_espargos_esp-sdr_README.md`
- "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver and sends them to your computer over USB or UART. No extra SDR hardware is needed."
- "Parts of the firmware are AI-generated: we understand the capture mechanism well on the ESP32-C61 used in our ESPARGOS One array"
- Supported-chips table: "ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 … 4 | also receives 5 GHz" ; "ESP32-S3 | ✅ | Serial/JTAG | GPIO43 / GPIO44 | 80, 40, 16 | continuous capture¹ and I/Q over USB"
- "Snapshots are bursts of up to 16,380 samples (8,190 on the C2 and 12,284 on the S2), so there are gaps between them. Gain is not calibrated in dB."
- "**Continuous I/Q on the ESP32-S3**: the second core filters and decimates the 16 MS/s stream to 15.625–250 kS/s, sent gap-free over native USB."
- "The firmware speaks a simple line-based protocol over native USB or UART (2 Mbaud): `INFO`, `FREQ 2442`, `CAP16 4096 0` and so on, with binary payloads protected by CRC32."
- "ESP-SDR is licensed under the GNU General Public License, version 3 or later"

### C5. ESP-SDR docs/rx-controls.md
- URL: https://github.com/ESPARGOS/esp-sdr/blob/HEAD/docs/rx-controls.md — File: `github_espargos_esp-sdr_docs_rx-controls.md`
- "Hardware AGC is the default; manual gain indices are not absolute gain in dB."
- "The Wi-Fi AGC is built to settle on packet preambles. It does not protect the ADC from a strong *continuous* signal: with a test tone a few centimetres from the antenna, every Wi-Fi chip clipped in AGC mode (peak at full scale), and clipping products buried the tone. Use manual gain for strong signals."
- Bandwidth table: "C5 | 11–48 MHz" ; "S3 | 13–69 MHz"
- Measured reception range table (CW tone, "One board per chip, October 2026"): row "C3, S2, S3 | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | – | – |" under columns "1850 | 1950 | 2100 | 2200 | 2300–2650 | 2750 | 2850 | 2950"; row "C5 | – | – | – | ✓ | ✓ | – | – | – | ✓" (last column "5180–5800").
- "Nothing was received at 1500–1800 or 3050 MHz."

### C6. ESP-SDR docs/iq-stream.md
- File: `github_espargos_esp-sdr_docs_iq-stream.md`
- "Measured on an S3 over native USB, 4- and 8-bit samples at 250 kS/s and 16-bit samples at 125 kS/s stream without gaps (60 s runs)."
- "Native USB only (`ERR transport` otherwise)."

### C7. ESP-SDR project page (HTML text saved)
- URL: https://espargos.net/espsdr/ — File: `espargos_net_espsdr.txt`
- "Bits 19–10 hold I and bits 9–0 hold Q, both signed 10-bit integers (−512 to +511). Bits 27–20 report the receiver gain setting (an index into the gain table)"
- "Tuning 2.2–2.7 GHz 4.8–6.0 GHz 5 GHz is only available on ESP32-C5."
- "Without any hardware modifications, ESPARGOS One can now phase-coherently capture raw IQ samples."
- "The serial burst-capture profiles transfer IQ samples at a low duty cycle, which is enough to display a live spectrum and waterfall in the browser. Packets that arrive between capture windows may be missed."
- FAQ: "Can an external mixer be added to the ESP32's RF input / output to support a wider frequency range? Yes, this is possible."

### C8. Single-antenna ESP32 CSI phase — "SA-WiSense" (arXiv:2507.17623v2)
- URL: https://arxiv.org/pdf/2507.17623v2 — File: `sawisense_2507.17623.pdf` / `.txt`
- Sec. I: "the raw phase extracted from commodity Wi-Fi devices is unreliable for direct use due to random offsets induced by hardware imperfections, such as clock"
- Sec. III (Lemma 1 proof): "θRX(m,k) = θch(m,k) + n(m)·(ηb(k) + ηo) + φ(k), where ηb(k), ηo, and φ(k) denote the phase errors originating from packet boundary detection (PBD), SFO, and CFO, respectively" [...] "A key property of θos(m,k) is the linear relationship with the physical subcarrier index n(m), which enables the elimination of the offset by computing a ratio between different subcarriers"
- Abstract: "We use commodity ESP32 microcontrollers to build an experiment test."

---

## D. RSSI with a rotating directional antenna; beam deconvolution

### D1. Hood & Barooah, "Estimating DoA From Radio-Frequency RSSI Measurements Using an Actuated Reflector" (IEEE Sensors J. 11(2), 2011)
- URL: https://www.iitg.ac.in/pbarooah/publications/BH_PB_S_2011.pdf — DOI 10.1109/JSEN.2010.2070872 — File: `hood2011_actuated_reflector_doa.pdf` / `.txt`
- Abstract: "the error in the measured DoA has a mean smaller than 4° and standard deviation of smaller than 8°, in both indoor and outdoor environments in line of sight situations. Presence of moving objects in the vicinity of the transceivers seem to have an adverse effect" (degree signs dropped in extraction)
- Sec. I: "Little change in estimation accuracy was observed between indoor and outdoor environments, though one might expect multipath effects to be more severe in indoor settings." [...] "the proposed method is effective only when there are no moving objects in the vicinity of the transceiver pair."
- Sec. II: "The transceiver is the MaxStream XBee Pro with whip antenna, operating in the 2.4 GHz band" [...] "A 200 steps-per-revolution stepper motor is used to rotate the transceiver and reflector."

### D2. Ghosh, Xie, Krishnamachari, "miniRadar: A Low Power IEEE 802.15.4 Transceiver Based Implementation of Bistatic Radar" (HotWireless'17)
- URL: https://anrg.usc.edu/www/papers/miniradar.pdf — File: `usc_miniradar.pdf` / `.txt`
- Abstract: "we employ a single standard low power omnidirectional transmitter with known transmission parameters and a single rotating directional receiver antenna to collect a set of directional RSSI samples"
- Real experiment: "The directional antenna used is Rosewill Model RNX-AD7D [...] maximum Gain of 5dBi and 7dBi, respectively. The Half Power Beam Widths (HPBW) of the antenna are 70° and 50° for 2.4GHz and 5GHz, respectively." / "The rotating antenna platform completes a full scanning in 2s"
- Results (anechoic chamber, one reflector): "The results suggest that the proposed system performs well with error in the order of meters." Table 2 mean errors "0.9m 1.4m 0.7m" for Tx–Rx distance "1m 2m 3m".
- Future work: "ro = G · P" [...] "in absence of fading, we can exactly calculate the multipath components using (8) as the gain matrix G is known as well as the measured RSSI vector" [...] "However, in presence of fading, the linear equation does not hold" [...] "to solve for the vector P, we need to employ some sophisticated method such as compressible sampling. We verified that the traditional solutions such as Min-Square Approximation approach doesn't perform well."

### D3. Ghosh, Tran, Krishnamachari, "ARREST: A RSSI Based Approach for Mobile Sensing and Tracking of a Moving Object" (arXiv:1707.05493v2)
- URL: https://arxiv.org/pdf/1707.05493 — File: `arrest_1707.05493.pdf` / `.txt`
- Abstract: "uses a single rotating, off-the-shelf, directional antenna, novel angle and relative speed estimation algorithms, and Kalman filtering"
- Sec. VIII: "The instantaneous absolute angle errors are less than 40° with high probability (≈ 90%) for all three methods which is justified because the HPBW specification for the antenna is approx 70°."
- Sec. VIII: "our current system does not work if there exists no strong/good multipath signal in NLOS situations"

### D4. Cornwell, "Multi-Scale CLEAN deconvolution of radio synthesis images" (arXiv:0806.2228)
- URL: https://arxiv.org/pdf/0806.2228 — File: `cornwell2008_multiscale_clean_0806.2228.pdf` / `.txt`
- Abstract: "The most widely used radio synthesis deconvolution method is the CLEAN algorithm of Högbom. This algorithm works extremely well for collections of point sources and surprisingly well for extended objects."
- Sec. I: "each point on the sky is represented by a suitably scaled and centered point spread function. Hence one can find the brightest point source by simply performing a cross-correlation of the dirty image with the point spread function. Removing the effects of the brightest point then enables one to find the next brightest, and so on." [...] "Convergence is slow for extended objects [...] and instabilities occur"

### D5. Högbom 1974, A&AS 15, 417 (original CLEAN)
- URL: https://articles.adsabs.harvard.edu/pdf/1974A%26AS...15..417H — File: `hogbom1974_clean.pdf`
- Downloaded, but the PDF is a scanned image with no text layer and no OCR tool was available. **Not read; no claim made from it.**

---

## E. Satellite-TV / hydrogen-line hardware as an alternative payload

### E1. Mandal et al., "Everyday Radio Telescope" (arXiv:1601.02982)
- URL: https://arxiv.org/pdf/1601.02982 — File: `everyday_radio_telescope_1601.02982.pdf` / `.txt`
- Abstract: "With our set-up one can measure brightness temperature and flux of the Sun at 11.2 GHz and calculate the beam width of the antenna. The set-up uses commercially available satellite television receiving system and parabolic dish antenna. We report the detection of point sources like Saturn and extended sources like the galactic arm of the Milky way."
- Sec. II: "Satellite dish antenna consisting of a 68 cm parabolic dish reflector and an LNB" / "We have used a commercially available analog satellite finder (GC SF-02). Such a device acts as a square law detector" / "Arduino is a microcontroller board with a 10 bit Analog to Digital Converter [...] we digitize the intensity from the satellite finder at 10Hz sampling rate."
- Sec. III: "beam width of our telescope was characterized to be ∼ 3.5° with less than 1% error."
- Sec. V: "Most popular ammature telescopes like VSRT use RTL-SDR, which has a bandwidth of ∼ 3 MHz, whereas, with the satellite finder we can utilize the full 1.1GHz bandwidth, thus giving us a higher sensitivity."

### E2. Köppen, "Report on the experiences with the ESA-Dresden radio telescope" (ISU Strasbourg, 2007)
- URL: https://portia.astrophysik.uni-kiel.de/~koeppen/10GHz/docs/ESAreport2.pdf — File: `koeppen_ku_band_ESAreport2.pdf` / `.txt`
- Sec. 3 (calibration): "If one points a LNB towards a person, the walls of a room, or anything at room temperature, one notes a signal, e.g. measurable by a SatFinder indicator. Only when one points the LNB to the sky, a strong drop of the signal is noticed. As seen at 10 GHz, the sky is dark, but everything else on Earth is bright."
- Same section: "the hand calibration always gave a signal of 3 to 5 dB above sky background"
- App. A.1 (bare LNB, no dish): "Pointing at the sky through an opened window shows a drop in signal. [...] We found: ground +68.3dBµV, sky +64.4dBµV." / "Pointing at the Sun will not cause any noticeable enhancement of the signal; only a (parabolic) reflector of sufficient size will do that." / "Even pointing to a candle flame will not reveal obvious differences, because the flame covers only a very small portion of the beam of the LNB's horn antenna."
- Solar scans: "a rather large value for the half-power beam width (HPBW) of 3° was found" (1.2 m dish section)
- Sec. 5.3: "For the "primitive" approach one would need a satellite dish (€ 100, if bought new), a LNB (€ 5), a SatFinder (€ 10), and a small power supply (€ 10). And this already would permit to observe and even analyse drift scan of the Sun."

### E3. Bhattacharjee, Grover, Arumugam, "Observations of the 21 cm HI Line [...] using Pyramidal Horn Radio Telescope" (arXiv:2512.19262)
- URL: https://arxiv.org/pdf/2512.19262 — File: `horn_hline_2512.19262.pdf` / `.txt`
- Sec. II: "The aperture dimensions were 75 cm × 60 cm, sufficiently large to allow passage through most doorways."
- Sec. III: "The conditioned RF signal was then digitised using a HackRF One software-defined radio (SDR)" / "The LNA used in the system was the Nooelec SAWbird + H1" / "the telescope achieved first light using only the LNA and the SDR."

### E4. PICTOR, "Building your very first Radio Telescope" (guide PDF)
- URL: https://pictortelescope.com/Building_your_very_first_Radio_Telescope.pdf — File: `pictor_building_first_radio_telescope.pdf` / `.txt`
- "Our radio telescope will consist of a parabolic antenna (e.g. satellite TV dish) with a feedhorn optimized for 1420 MHz, an appropriate low-noise amplifier (LNA) and an SDR receiver."
- "If you do not already have a dish, look for one with a diameter of at least 70 cm, although bigger is always better!"
- "the dimension of your waveguide should be approximately diameter = 15 cm x height = 18 cm."

---

## F. Prices (PLN gross, fetched 2026-11-11) — see `shop_prices_2026-11-11.txt`
- Botland, Seeed XIAO ESP32-C5: `"price":"30.90"`, `"priceCurrency":"PLN"`, `InStock`. [V]
- MediaMarkt.pl, Konwerter Technisat Unix Single LNB: `"price":29.99`, PLN, `InStock`; spec "Wejściowa 10.7 - 11.7 GHz, Wejściowa 11.7 - 12.75 GHz, Wyjściowa 1100 - 2150 MHz, Wyjściowa 950 - 1950 MHz". [V]
- MediaMarkt.pl, VAYOX VA0314 SAT Finder (digital meter): `"price":49.9`, PLN, `InStock`; "Zakres częstotliwości: 950-2150 MHz". Whether it has an analog/ADC-readable output was **not** checked. [V for price]
- ESPARGOS One: €350 excl. VAT, EU-only, sold by the project (not a Polish shop). [V]
- Not checked here: RTL-SDR, SAWbird H1, 2.4/5 GHz directional antennas, RF switches.

---

## G. Could not retrieve / not read (no claims made from these)
- Kumar, Gil, Katabi, Rus, "Accurate indoor localization with zero start-up cost" (Ubicarse), MobiCom 2014, DOI 10.1145/2639108.2639142. Semantic Scholar says `"status": "CLOSED"`; the Harvard and MIT links returned HTML. Only the secondary statement in SpotFi (B1) is used.
- Högbom 1974, A&AS 15, 417: downloaded as a scanned image; not read (see D5).
- Subbu et al., "I Am the Antenna: Accurate Outdoor AP Location" (Borealis, MobiCom 2011): https://www.cs.dartmouth.edu/~xia/papers/mobicom11_borealis.pdf returned HTML.
- IUCAA "Affordable Small Radio Telescope" (https://web.iucaa.in/~rpl/Folder%20With%20pdf/asrt.pdf) returned HTML.
- Xie et al., "SWAN: Stitched Wi-Fi ANtennas" (MobiCom 2018), the antenna-switching workaround cited in C1: not fetched.
- Hernandez & Bulut, ESP32 CSI Tool (WoWMoM 2020), and LTEye (rotating-antenna LTE localisation): not fetched.
- Holl & Reinhard PRL version (APS blocked the fetch); the arXiv v2 was read instead.
