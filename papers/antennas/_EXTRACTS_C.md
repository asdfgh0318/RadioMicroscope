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
