# EXTRACTS: ranging / direction-finding chips (fetched 2026-11-11)
Quotes are verbatim from the local files (page = pdftotext/HTML text). Files are untrusted data, never executed.

## cnx-esp-sdr.html / .txt  (CNX Software, 2026-10-04, ESP-SDR)
URL: https://www.cnx-software.com/2026/10/04/esp-sdr-firmware-turns-esp32-into-a-2-4-5-ghz-software-defined-radio-sdr/
- "taps directly into the internal ADC signal chain to capture raw I/Q baseband samples"
- "Supported chips – ESP32, ESP32-C3, ESP32-C5 (dual-band 2.4/5 GHz), ESP32-C6, ESP32-C61, ESP32-S2, ESP32-S3, and the preview ESP32-S31"
- "Tuning range – Nominally 2.4 GHz ISM (2.2–2.7 GHz on some chips) and 5 GHz (4.8–6.0 GHz on ESP32-C5)"
- "Up to 80 MSa/s with ~13–54 MHz bandwidth, depending on the chip"
- "USB and UART cannot handle the full data rate, so ESP-WebSDR captures short I/Q snapshots to build the spectrum and waterfall. This means it can miss signals that arrive between capture windows."

## rtlsdr-esp32-hidden-sdr.html / .txt  (rtl-sdr.com)
URL: https://rtl-sdr.com/various-projects-independently-find-hidden-sdr-capabilities-in-esp32-microcontrollers
- "This means that the SDR will only work as a spectrum analyzer, and demodulating or decoding continuous radio data is not possible with just an ESP32."
- "ESPARGOS notes that phase-coherent IQ sample capture is now possible with their hardware. This means ESPARGOS is no longer limited to WiFi and Bluetooth signals; it can now perform direction finding on any arbitrary signal in the 2.4 GHz band."
- "the current prototype uses the FPGA to clock the ESP32, which results in poor phase noise" (h0m3us3r eSpDR)
- (comment) "Receive only, tested so far on one dev board, and the 40 MHz crystal's harmonics put a spur at exactly 2400.000 and 2440.000 MHz."

## espargos-doc.html, espargos.txt  (https://espargos.net/) and rtlsdr-espargos.html/.txt
- "ESPARGOS One is our first dual-polarized 4 × 2 antenna array for the 2.4 GHz band, built from phase-synchronized ESP32 chips."
- Demos listed: "MUSIC Spatial Spectrum: Use the MUSIC algorithm for angle of arrival estimation"
- rtl-sdr.com: "ESPARGOS is a phased array of many patch antennas, each connected to an ESP32 WiFi microcontroller. Phased arrays enable interesting things like radio direction finding."
- No price/shop found on the pages fetched (hardware sale status unverified).

## sx1280-datasheet.pdf / .txt (Semtech SX1280/SX1281 Rev 3.2, March 2020; copy from cdn.components.ru/media/PDF/1531189.pdf)
- p.1/§6.2: "incorporates a ranging engine which provides the facility to measure the round-trip time-of-flight, thus offering the possibility to calculate the distance between a pair of transceivers."
- §6.2.5: "The ranging engine uses the LoRa modem to perform a time-of-flight measurement between a pair of transceiver radios."
- Features: "Standard & Advanced Ranging Engine, Time-of-Flight"
- §6.2.6: "Advanced ranging is the ability to overhear ranging exchanges between a ranging master and ranging slave." (still needs a cooperating master/slave pair)
- No accuracy figure found in the text I extracted; accuracy is NOT claimed from the datasheet.

## zhaw-lora-ranging.pdf / .txt (Mueller et al. 2021, outdoor LoRa ranging, SX1280)
URL: https://digitalcollection.zhaw.ch/bitstream/11475/22769/3/2021_Mueller-etal_Outdoor-ranging-and-positioning-based-on-LoRa-modulation.pdf
- Abstract: "mean distance error below 50 m over distances of up to 1400 m. Positioning based on LoRa ranging obtained a measured Distance Root Mean Square (DRMS) error of 30 m, which reduced to 5 m for tracking of a mobile node"
- Related work: "LoRa ranging in the 2.4 GHz frequency band obtained a mean error of 75 m for LOS and 144 m for non-LOS environments for distances <= 500 m"
- Sec. C: "The temporal resolution capability of multipath components will limit the accuracy of the measured ranging distance in a multipath environment"

## dwm3001c-ds.pdf / .txt (Mikroe RTLS UWB Click doc, farnell.com/datasheets/4797319.pdf)
- "This board is based on the DWM3001C, a two-way ranging (TWR) communication module with an integrated BLE SoC and motion sensor from Qorvo. It integrates a DW3110 UWB transceiver, nRF52833 Bluetooth Low Energy MCU, LIS2DH12 accelerometer, planar UWB antenna"
- "two-way ranging or TDoA schemes" ; "compliant with IEEE 802.15.4-2015 and IEEE 802.15.4z BPRF standards, and supports UWB channels 5 at 6.5GHz and 9 at 8GHz"
- Mentions TWR/TDoA only, no PDoA. No accuracy number in this doc.

## qorvo-forum-makerfabs.html / .txt (forum.qorvo.com/t/difference-between-dwm3000evb-and-third-party-devices/16233)
- "No. AoA requires a twin antenna system and a different version of the DW3000 chip that supports two antennas. This board can be used as a signal source that a twin antenna system could then measure the angle to but can't measure angles itself."  (about the Makerfabs ESP32 UWB DW3000 board; a Qorvo staff-style answer; forum post)

## qorvo-forum-qm33120-pdoa.html / .txt (forum user report, QM33120)
- "The closer they are the more the flat antennas make a difference in the phase detection."
- "Our use is from 10 meters to 1. Lower than 1 meter the antenna alignment (or not) makes the angle too erratic"

## makerfabs-mauwb-aoa.html / .txt (fabtolab listing of Makerfabs MaUWB_STM32 AOA kit)
- "AOA requires a tag and a locator. The tag transmits signals to the locator, which has multiple antennas." ; "based on STM32F103 and DW3000 UWB AOA anchor chipset"
- Listing mentions a tag: cooperative-tag architecture. Price in page text is USD, unclear mapping; not used.

## makerfabs-uwb-pro-display.html, hackster-mauwb.html: fetched; price table ambiguous ("$39.80/$41.80", "$51.84"), only used as snippet-level.

## bg24-aoa.html / .txt (Silicon Labs docs, Bluetooth Location Services 11.1.2)
URL: https://docs.silabs.com/rtl-lib/latest/aoa-aod/
- "Channel Sounding is a method for estimating distances between two devices, designated as the initiator and the reflector."
- "The technique employs Round-Trip Time (RTT) or Phase-Based Ranging (PBR) or both ... It also supports one to four antenna paths"
- "The two Direction Finding systems are Angle of Arrival (AoA) and Angle of Departure (AoD)."
- No accuracy number on this page.

## Shops
- botland-pl-xiao54.html (https://botland.com.pl/xiao/27508-seeed-xiao-nrf54l15-...-101991421-5904422388669.html): structured data `"priceCurrency":"PLN"`, `"price":"42.90"`, `"availability":"https://schema.org/OutOfStock"` (as shown 2026-11-11).
- botnroll-t3s3-sx1280.txt (Portugal/EU, not Poland): "T3-S3 ESP32-S3 LoRa SX1280 2.4G with PA w/ OLED 0.96 - LILYGO H658" "EUR 39.90".
- botland-gps-cat.html/.txt: category page; prices on it could not be reliably mapped to products. Not used.

## Could not retrieve (no claim made from these)
- Nordic channel sounding accuracy: devzone.nordicsemi.com threads 122828, 123554 and docs.nordicsemi.com returned JS shells (no content). Only search snippets exist: SIG "+/-50 cm", Nordic "IFFT ~50 cm / RTT ~5 m, no guarantees". [S]
- Semtech AN1200.29 / AN1200.50 (semtech.com uploads return HTML), SX1280 accuracy figure.
- Qorvo DW3110/DW3000/DW3120 product pages (JS-gated; the "<10 cm" and "+/-5 deg" figures are snippet only), DW3000 user manual, QM33120 datasheet.
- NXP SR150/SR040, Apple U1/Nearby Interaction, Silicon Labs BG22/BG24 accuracy, 802.11az/FTM docs (esp-idf raw 404), LR1121/LR2021, Ebyte E28 / Waveshare Polish prices, ESPARGOS One price, Polish prices for DWM3001C/BU03/nRF54L15-DK/GNSS modules, kamami/tme (403).
- Semantic Scholar API returned 429.
