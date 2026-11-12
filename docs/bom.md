# RadioMicroscope v2: parts list

Prices are gross PLN as seen on 2026-11-11. This list is derived from [`sourcing.md`](sourcing.md) and the reports in `papers/`; those govern if a figure here disagrees with them.

**Confirmed** means the shop's own product page was opened. **Unconfirmed** means the price was seen only in a search result or price aggregator, because the shop blocks automated access. Prices and stock will have moved by the time you order.

## Desk build: 2.4 GHz, brushless

| # | Part | Qty | Each | Total | Shop | Status |
|---|---|---|---|---|---|---|
| 1 | Seeed XIAO ESP32-C5 (sensor radio) | 1 | 30,90 | 30,90 | [Botland](https://botland.com.pl/xiao/28890-seeed-xiao-esp32-c5-wifibluetoothzigbeethreadmatter-seeedstudio-100010048-5902186335752.html) | confirmed, orderable |
| 2 | Seeed XIAO ESP32-S3 Sense (brain, camera) | 1 | — | 0 | already owned | 79,90 at Botland, out of stock until about 31.12.2026 |
| 3 | ESP32 board with ESP-WROOM-32, 38 pins, USB-C, pins soldered (motor controller) | 1 | 29,69 | 29,69 | [MSX Elektronika](https://sklep.msalamon.pl/produkt/esp32-plytka-z-esp-wroom-32-38-pin-z-ukladem-cp2102-usb-c/) | confirmed, in stock |
| 4 | SimpleFOC Mini driver (DRV8313) | 2 | 25,00 | 50,00 | [Gotronik](https://www.gotronik.pl/modul-sterownika-silnika-simplefoc-mini-na-ukladziedrv8313-p-14252.html) | confirmed, in stock |
| 5 | iFlight GM3506 gimbal motor with AS5048A encoder | 2 | ~90,19 | ~180,38 | AliExpress, item 1005011728866518 | **unconfirmed**; VAT inclusion not confirmed |
| 6 | Maple Wireless 2.4 GHz 9 dBi patch antenna, SMA | 1 | 73,00 | 73,00 | [ht-dron](https://www.ht-dron.pl/Maple-Wireless-2-4GHz-9dBi-Directional-SMA-Antenna-for-Extended-Range-p9290) | confirmed, **out of stock**; €13,19 in stock at [Rotorama](https://www.rotorama.com/product/maple-wireless-2-4g-9dbi-smerova-antena) (Czech, RP-SMA) |
| 7 | U.FL to SMA socket pigtail, 200 mm | 1 | 7,32 | 7,32 | [ABC-RC](https://abc-rc.pl/pl/products/przejscie-u-fl-ipex-na-sma-jack-adapter-prosty-z-przewodem-200mm-9838.html) | confirmed, 432 in stock |
| 8 | USB-C PD trigger, 5–20 V by switch | 1 | 12,00 | 12,00 | [Gotronik](https://www.gotronik.pl/wyzwalacza-szybkiego-ladowania-pd-usb-c-p-13295.html) | confirmed, ships in 24 h |
| 9 | Step-down converter to 5 V, MP1584EN | 1 | 4,90 | 4,90 | [ABC-RC](https://abc-rc.pl/pl/products/przetwornica-dc-dc-mp1584en-max-3a-5v-micro-2-gramy-step-down-do-fpv-19861.html) | confirmed, 307 in stock |
| 10 | 1/4" tripod screw | 1 | 7,45 | 7,45 | [Gotronik](https://www.gotronik.pl/sruba-statywowa-gwint-14-fotograficzna-14-cala-165-x-8-x-5-mm-p-13875.html) | confirmed |
| | **Total** | | | **about 396** | | of which about 180 (the motors) unconfirmed |

Not priced: filament for the four printed parts, M3 and M4 screws, hook-up wire, a 1/4" nut for the base.

Notes:

- **The antenna is the supply problem.** Both ht-dron versions were out of stock again on re-check, and no other small 2.4 GHz patch was found in stock at a Polish shop. The Czech shop has it at €13,19 plus €4,99 shipping to Poland.
- **Match the pigtail to the antenna.** The ht-dron antenna has an SMA plug, so the pigtail needs an SMA socket (item 7). The Rotorama one is RP-SMA and needs the [RP-SMA pigtail](https://abc-rc.pl/pl/products/przejscie-u-fl-ipex-na-rp-sma-jack-adapter-prosty-z-przewodem-200mm-20555.html) (4,68) instead.
- **The motors are the one part with no Polish source.** No regular Polish shop whose pages opened sells a gimbal motor. If the 23% VAT is added at checkout rather than included, item 5 rises to about 222.
- **Motor choice.** The GM3506 gives 0.059–0.098 N·m (maker's page), enough for a balanced head with this antenna. The smaller GM2804 (about 72 zł, 0.025–0.034 N·m) saves 1 mm of size and leaves little margin. For a heavier antenna hung off-centre, the GM4108H-120T (about 169 zł) holds 0.118–0.177 N·m but runs hot doing it.
- **Optional protection:** a 3 A resettable fuse (Littelfuse RUEF300, 3,32 each at TME, minimum 5) on the motor supply.

## Add a 5 GHz antenna (same cradle)

| Part | Each | Shop | Status |
|---|---|---|---|
| Cyberteam SkyEter13, 13 dBi, 33° beam, 82 × 82 × 12 mm, 80 g, 5.45–5.75 GHz, N socket | 7,37 | [Cyberteam](https://cyberteam.pl/en/produkt/27_skyeter13) | confirmed on the page, but it looks like a clearance price (was 79,00 net); needs an N-to-SMA adapter |
| GEPRC Triple Feed Patch-1, 9.4 dBi, 55° beam, circular, 20 g, 5.47–6.13 GHz, SMA | 81,00 | [ht-dron](https://www.ht-dron.pl/GEPRC-Triple-Feed-Patch-1-SMA-5-8-GHz-FPV-p7482) | confirmed, in stock |

## Alternative drivetrain: bus servos

Replaces items 3, 4 and 5 (about 260) with about 230, all from one Polish shop.

| Part | Qty | Each | Total | Shop | Status |
|---|---|---|---|---|---|
| Waveshare ST3215-HS bus servo, 20 kg·cm | 2 | 105,00 | 210,00 | [Botland](https://botland.com.pl/serwa-praca-ciagla-360/23725-20kg-bus-servo-motor-serwomechanizm-z-enkoderem-magnetycznym-360-stopni-waveshare-25127.html) | confirmed, 38 in stock |
| Waveshare Bus Servo Adapter (A) | 1 | 19,90 | 19,90 | [Botland](https://botland.com.pl/sterowniki-serw/24907-bus-servo-adapter-a-sterownik-do-serwomechanizmow-magistrali-szeregowej-serii-stsc-uart-waveshare-25514-5904422385736.html) | confirmed, out of stock until about 04.12.2026 |

The 3D model is drawn for the brushless motors; a servo build needs its own yoke.

## Useful extras

| Part | Price | Shop | Adds |
|---|---|---|---|
| GY-271 magnetometer | 29,90 | [Botland](https://botland.com.pl/magnetometry/2722-magnetometr-gy-271-3-osiowy-cyfrowy-i2c-33v-5v-qmc5883l-5903351249621.html) | compass heading (driver written, untried on hardware; see [`navigation.md`](navigation.md)) |
| Seeed L76K GNSS for XIAO | 75,90 | [Botland](https://botland.com.pl/moduly-gps/25377-modul-pozycjonowania-multi-gnss-do-seeed-xiao-l76k-gps-beidou-glonass-qzss-seeedstudio-109100021-5904422386610.html) | position; the BN-880 already owned works on the same pin |
| HLK-LD2410B 24 GHz radar | 33,19 | MSX Elektronika | presence and distance along the boresight (not integrated) |
| 6-wire slip ring, 22 mm | 67,00 | [Botland](https://botland.com.pl/zlacza-slizgowe/7143-pierscien-slizgowy-6-przewodowy-2a-22mm-5904422335533.html) | unlimited pan rotation (needs a different base) |
