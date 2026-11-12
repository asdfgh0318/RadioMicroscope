# EXTRACTS: SDR / wideband receiver heads (fetched 2026-11-11)
Quotes are verbatim from the local files named. "snippet only" = web-search summary, file not opened.

## A. ESP-SDR (the "new ESP SDR")
### esp-sdr-README.md  (https://github.com/ESPARGOS/esp-sdr, README)
- "ESP-SDR turns the Wi-Fi/Bluetooth radio of an ordinary ESP32 board into a receive-only software-defined radio. The firmware captures raw I/Q samples from the chip's own receiver and sends them to your computer over USB or UART. No extra SDR hardware is needed."
- "we found an undocumented debug path that lets the CPU read those samples instead."
- Table row: "| ESP32-C5 | ✅ | Serial/JTAG | GPIO11 / GPIO12 | 80 … 4 | also receives 5 GHz |" ; "| ESP32-P4 | ❌ | | | | no radio |" ; "| ESP32-S3 | ✅ | Serial/JTAG | GPIO43 / GPIO44 | 80, 40, 16 | continuous capture¹ and I/Q over USB |"
- "Snapshots are bursts of up to 16,380 samples ..., so there are gaps between them. Gain is not calibrated in dB."
- "All chips accept tuning from 100 to 6000 MHz, but the PLL only locks in a limited range around 2.4 GHz (and 5 GHz on the C5)."
- "Continuous I/Q on the ESP32-S3: the second core filters and decimates the 16 MS/s stream to 15.625-250 kS/s, sent gap-free over native USB."
- "ESP32-S31 streaming ... continuous 8-bit I/Q at up to 20 MS/s over high-speed USB or 40 MS/s over Gigabit Ethernet, for SoapyESPSDR."
- "On-chip spectra (all chips): the firmware computes 256-2048-bin FFTs and sends compact spectra instead of raw samples."
### esp-sdr-rx-controls.md  (docs/rx-controls.md)
- "| C5 | 11–48 MHz | 6/7, two PHY modes | 6 bits |" (analog bandwidth); "| S3 | 13–69 MHz |"
- "The browser negotiates each chip's range and shows an informational warning outside 2400–2483.5 MHz (and, on the C5, outside 5150–5895 MHz)."
- "Nothing was received at 1500–1800 or 3050 MHz."
### esp-sdr-iq-stream.md / esp-sdr-spectrum.md: protocol + IQS command (decimation 64..1024 at 16 MS/s; "4- and 8-bit samples at 250 kS/s ... stream without gaps (60 s runs)").
### cnx-esp-sdr.txt (CNX Software, 2026-10-04)
- "Tuning range – Nominally 2.4 GHz ISM (2.2–2.7 GHz on some chips) and 5 GHz (4.8–6.0 GHz on ESP32-C5)"
- "This makes basic spectrum analysis possible on an ESP32 board that can cost less than $5."
- "ESP-WebSDR captures short I/Q snapshots ... means it can miss signals that arrive between capture windows."
### rtlsdr-esp32-hidden.txt, hackaday-esp32-sdr.txt, esp32co-zephyr.txt: corroborating press (not independently quoted). Hackaday comment (not authoritative): "ESP32-S31 USB 2.0 streaming 20 MSa/s @8bit to PC, pretty amazing at $7 + shipping."

## B. LR2021 SDR / LakeShark (ESP32-P4 + Semtech LR2021)
### cnx-lr2021-sdr.txt (CNX 2026-10-20)
- "Using an undocumented command in the chip’s ROM, this project exposes raw 16-bit I/Q samples"
- "Receive frequency range – 100 MHz to 2.74 GHz (experimentally tested), extending beyond the datasheet’s specified 150–960 MHz and 1.5–2.5 GHz bands."
- "Semtech LR2021 running ROM 1.24; not compatible with the SX1262 variant for raw I/Q access."
- "the results do not establish calibrated receiver sensitivity or guarantee the same frequency coverage on other hardware."
- "continuous I/Q capture at 125,000 samples per second"
### rtlsdr-lakeshark-lr2021.txt
- "The sample rate is relatively low at 250 Ksps max, meaning only a narrow bandwidth slice is available"
- "it is possible to DIY a receiver for about $28 with Waveshare’s Core2021 LR2021 modules and their ESP32-P4-WIFI6 board."
### rtlsdr-lakeshark.txt
- "...which allows a USB-connected RTL-SDR Blog V3 or V4 to be used for P25 Phase 1 trunking, FM, POCSAG, ADS-B, and sub-GHz capture." (ESP32-P4 host drives RTL-SDR over USB)

## C. Conventional SDRs
### rtlsdr-v4-datasheet.pdf (rtl-sdr.com V4 datasheet p1): "Frequency Range 500 kHz to 1.766 GHz"; "Bandwidth 2.56 MHz stable (up to 3.2 MHz with drops)".
### rtlsdr-blog-about.txt: "RTL-SDR is a very cheap ~$30 USB dongle"; "...some people have had luck with 2.8MS/s and 3.2 MS/s working well on some USB 3.0 ports."
### radio-sklep-rtlsdr-v4.txt (https://www.radio-sklep.pl/pl/p/RTL-SDR-V4-R828D-RTL2832U/3341): "W ofercie: TAK, w naszym magazynie Wysyłka w: 24 godziny Cena: 280,00 zł" (cart button also shows "powiadom o dostępności"; web-search snippet earlier showed 270,00 zł).
### elecena-rtlsdr-v4.txt: foreign shop (The Pi Hut) "81.60 GBP 428.32 PLN" for V4 kit (not a Polish shop).
### gotronik-hackrf-r9-card.pdf (dated 11-11-2026): "HackRF One R9 ... Cena brutto 825,00 zł ... Czas wysyłki 24 godziny"; "Zakres częstotliwości: 1 MHz do 6 GHz"; "do 20 milionów próbek na sekundę z 8-bitowymi próbkami".
### botland-pizero2w.html (schema.org JSON): "price":"72.90", "priceCurrency":"PLN", "availability":"https://schema.org/BackOrder" (Raspberry Pi Zero 2 W, Botland, 2026-11-11).
### botland-xiao-c5.html: "price":"30.90", "PLN", "availability":"https://schema.org/InStock" (XIAO ESP32-C5).
### Snippet only (pages not opened/403): Kamami ADALM-PLUTO 1,409.00 PLN gross; Kamami HackRF One 1,486.99 PLN net; CaribouLite "$119" 2021 crowdfunding (rtl-sdr.com); Airspy Mini "$99" old; KrakenSDR price not found; Pluto+ EUR 239 (Fruugo); LibreSDR EUR ~369 (sdrstore.eu). Allegro RTL-SDR V4 ~300-450 PLN (snippet).

## D. Non-SDR wideband power
### gotronik-tinysa-ultra-card.pdf (11-11-2026): "TinySA ULTRA analizator widma od 100kHz do 5,3GHz  Cena brutto 689,00 zł ... Czas wysyłki 24 godziny"; "złącze komunikacyjne: USB-CDC, UART-TTL"; "maksymalna częstotliwość wejściowa: 800MHz, 6GHz w trybie ULTRA"; "liczba punktów skanowania: 450 max".
### tinysa-ultra-gotronik-zs407.pdf: "TinySA ULTRA+ ... ZS407 Cena brutto 899,00 zł"; "100 kHz – 900 MHz (tryb normalny), 100 kHz – 7,3 GHz (tryb Ultra)"; "Czas skanowania (0–350 MHz) ok. 165 ms".
### tinysa-wiki-usb.txt (tinysa.org USB Interface): "After connecting the tinySA to a PC using the a USB cable a serial interface will become available"; "usage: scan {start(Hz)} {stop(Hz)} [points] [option]"; "usage: scanraw {start(Hz)} {stop(Hz)} [points] [option]".
### gotronik-cad8319-card.pdf: "Cyfrowy miernik mocy RF 100MHz - 8GHz 24-bit ADC USB-C AD8319 Cena brutto 85,00 zł"; "Zakres dynamiki pomiarowej: -50 dBm do -5 dBm"; "Maksymalna bezpieczna moc wejściowa: +5 dBm"; "Typ sygnału: fale ciągłe". (Needs USB host; has LCD; raw analog output not documented in the card.)
### CC1101 TI datasheet (not saved as file; downloaded and read then removed): "frequencies in the 300-348 MHz, 387-464 MHz and 779-928 MHz bands"; "The RSSI value is given in dBm with a ½ dB resolution". Re-fetch: https://www.ti.com/lit/ds/symlink/cc1101.pdf
### nrf24l01p-datasheet.pdf §6.4: "Received Power Detector (RPD) ... triggers at received power levels above -64 dBm ... If the received power is less than -64 dBm, RDP = 0." (1-bit, 2.4 GHz only).

## Could not retrieve
- AD8317/AD8318 datasheet (analog.com blocked; mirrors wrong file). https://www.analog.com/media/en/technical-documentation/data-sheets/AD8317.pdf
- SX1280 datasheet (Semtech link returned HTML). SX1262/LR2021 datasheets not read.
- Kamami and TME pages (403). CaribouLite and KrakenSDR crowdsupply pages (403). Airspy, SDRplay, Nooelec, ADALM-Pluto/ Pluto+ / LibreSDR vendor pages not opened. Botland HackRF page: price not extractable.
- No Polish-shop price found for: AD8317 module, Nooelec, generic R820T2 stick, Airspy, SDRplay, KrakenSDR, CaribouLite, Pluto+, LibreSDR.
