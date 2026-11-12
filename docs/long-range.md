# RadioMicroscope long range 2.4: design note

Written 2026-11-11 from the code and models, which govern where this note disagrees with them. A variant of the desk build for one job: find a distant Wi-Fi network on 2.4 GHz, lock the antenna onto it, and keep it there. Nothing here has been built or tested on hardware.

## Which receiver firmware for which job

The same XIAO ESP32-C5 board can run either. They suit different targets.

| | Wi-Fi sensor firmware (`firmware/sensor/`) | ESP-SDR (`SENSOR_ESPSDR 1`, `ESPSDR_BAND 24`) |
|---|---|---|
| Measures | strength of every frame from one chosen network | total power on one channel, in short bursts |
| Tells networks apart | yes, by transmitter address, even on a shared channel | no: everything on the channel adds up |
| Quiet network (beacons only) | works: it waits for the frames | **mostly sees nothing**: a beacon lasts a millisecond or two, ten times a second, and a burst covers 51 millionths of a second |
| Non-Wi-Fi signals (video links, ovens, jammers) | invisible | visible |
| Default in the firmware | yes | option |

**For locking onto a distant Wi-Fi network, use the Wi-Fi sensor firmware.** It is the default and needs no change. ESP-SDR on 2.4 GHz is the tool for a continuous transmitter or for mapping how busy the band is; with it the firmware keeps the strongest burst of each report period, so a busy network still registers.

## What makes it long range

Distance comes from the antenna, not from the electronics.

- **Antenna:** AntenaBox v2 16, a 16 dBi panel in a weather enclosure: beam 28° by 23°, 194 × 179 × 78 mm, 357 g, RP-SMA plug, 105,78 zł at [Cyberbajt](https://www.cyberbajt.pl/produkt/5035/antenabox-v2-16-rp-sma.html) (page opened; no stock figure shown). The figures are the seller's.
- **It also sharpens the picture:** the beam is less than half as wide as the small patch on the desk build, so the map resolves about twice as finely.
- **Pigtail:** U.FL to RP-SMA socket, 200 mm, 4,68 zł at ABC-RC.

### Expected signal level

My calculation for clear line of sight, not a measurement: an access point radiating 20 dBm (100 mW, assumed), free-space loss at 2437 MHz, antenna gain less 0.5 dB for the pigtail.

| Distance | With the 16 dBi panel | With the 9 dBi patch |
|---|---|---|
| 500 m | −59 dBm | −66 dBm |
| 1 km | −65 dBm | −72 dBm |
| 2 km | −71 dBm | −78 dBm |
| 5 km | −79 dBm | −86 dBm |
| 10 km | −85 dBm | −92 dBm |

- The firmware treats readings below −92 dBm as lost, so on paper the panel has margin at 10 km and the patch has none.
- **Line of sight decides it in practice.** These figures assume nothing in the way. The path also needs clearance around it: about 12 m at the midpoint of a 5 km path and 18 m at 10 km (first Fresnel zone, my calculation). Trees, buildings and the ground in that zone cost far more than the table suggests.
- The receiver's own sensitivity was not looked up; the table shows the level arriving, not whether the C5 decodes it.

## Staying locked

- **Narrow beam, tight tolerance.** With a 25° beam the signal is 1 dB down about 7° off axis. Set the beamwidth to 25 on the control page; the tracker's probe step and the scan spacing follow from it.
- **Quick re-lock.** When the signal drops, the head first searches one beamwidth around where it last was: 44 points in the test, against 316 for the whole sky at this beamwidth. Only if that finds nothing does it scan the whole sky. The page says which search is running.
- **Slow networks need patience.** A network that only beacons gives about ten frames a second. Each measurement waits until three frames are heard, so a tracking cycle of five measurements takes a couple of seconds. A raised dwell time (control page) makes each reading steadier and each cycle slower.
- **In simulation** (a still source, 2 dB of reading noise, 40° beam) the tracker holds to about 3.5° RMS. A narrower beam should scale that down in proportion, which is an expectation and not something the tests measure; real multipath and fading are not in the simulation.

## Mechanics

Model: `cad/longrange24.scad`; printable parts in `cad/stl-longrange24/`; view built with `python3 tools/build_viewer.py longrange24`.

- **Size:** 269 mm across the fork, 262 mm tall, 160 mm base. The antenna sets it.
- **Motors:** two iFlight GM4108H-120T (47 × 32 mm, 137 g, 0.118–0.177 N·m by the maker's page), about 169 zł each on AliExpress, unconfirmed. Set 11 pole pairs in `firmware/motion/config.h`.
- **Balance:** the antenna is set back so its middle lies on the tilt axis. Mounted by its rear face it would hang 357 g about 39 mm forward, around 0.14 N·m, which is the motor's whole rating spent on holding still.
- **Not a finished structure.** The fork arms are about 120 mm long and printed; at this size they need checking for stiffness, and a tripod under the base rather than a desk. The motor screw pattern, encoder housing and board outlines are assumed.

## Parts that differ from the desk build

| Part | Qty | Each | Shop | Status |
|---|---|---|---|---|
| AntenaBox v2 16 antenna | 1 | 105,78 zł | Cyberbajt | page opened; stock not shown |
| U.FL to RP-SMA pigtail, 200 mm | 1 | 4,68 zł | ABC-RC | confirmed, 183 in stock |
| iFlight GM4108H-120T with encoder | 2 | about 169 zł | AliExpress | unconfirmed search-card price |

Everything else is as in [`bom.md`](bom.md). The total comes to roughly 580 zł, of which about 340 (the motors) is unconfirmed; the antenna's stock was not shown on its page.

## Using the link, not just finding it

This instrument only listens: it points the antenna and reports. To carry traffic over the link once it is locked, the antenna has to feed a radio that joins the network. Two ways, neither built:

- Put an ordinary Wi-Fi client or bridge on a splitter with the sensor radio (about 3 dB lost on each path).
- Have the sensor board itself join the network after locking. It then stops being a pure listener, and measuring while connected needs new firmware.
