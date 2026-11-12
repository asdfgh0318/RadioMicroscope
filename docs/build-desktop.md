# Building the desktop RadioMicroscope

Written 2026-11-11 from the code, the model and that day's shop checks, which govern where this guide disagrees with them. **Nobody has built this yet.** The steps are the intended order of work; expect to adjust them, above all the motor tuning. Stages are arranged so each one proves something before the next adds risk.

## 1. Order

Prices are gross PLN, re-checked on 2026-11-11 unless marked.

**Botland** (shipping from 8,99)

| Part | Qty | Each |
|---|---|---|
| [Seeed XIAO ESP32-C5](https://botland.com.pl/xiao/28890-seeed-xiao-esp32-c5-wifibluetoothzigbeethreadmatter-seeedstudio-100010048-5902186335752.html) (sensor radio) | 1 | 30,90 |

**MSX Elektronika** (shipping not checked)

| Part | Qty | Each |
|---|---|---|
| [ESP32 board, ESP-WROOM-32, 38 pins, USB-C](https://sklep.msalamon.pl/produkt/esp32-plytka-z-esp-wroom-32-38-pin-z-ukladem-cp2102-usb-c/) (motor controller) | 1 | 29,69 |

**Gotronik** (shipping from 11,99)

| Part | Qty | Each |
|---|---|---|
| [SimpleFOC Mini driver, DRV8313](https://www.gotronik.pl/modul-sterownika-silnika-simplefoc-mini-na-ukladziedrv8313-p-14252.html) | 2 | 25,00 |
| [USB-C PD trigger, 5–20 V by switch](https://www.gotronik.pl/wyzwalacza-szybkiego-ladowania-pd-usb-c-p-13295.html) | 1 | 12,00 |
| [1/4" tripod screw](https://www.gotronik.pl/sruba-statywowa-gwint-14-fotograficzna-14-cala-165-x-8-x-5-mm-p-13875.html) | 1 | 7,45 |

**ABC-RC** (shipping from 7,90, free from 100 zł)

| Part | Qty | Each |
|---|---|---|
| [Step-down converter to 5 V, MP1584EN](https://abc-rc.pl/pl/products/przetwornica-dc-dc-mp1584en-max-3a-5v-micro-2-gramy-step-down-do-fpv-19861.html) | 1 | 4,90 |
| [U.FL to RP-SMA socket pigtail, 200 mm](https://abc-rc.pl/pl/products/przejscie-u-fl-ipex-na-rp-sma-jack-adapter-prosty-z-przewodem-200mm-20555.html) (for the Rotorama antenna) | 1 | 4,68 |

**Antenna: not available in Poland today**

| Part | Qty | Each |
|---|---|---|
| [Maple Wireless 2.4 GHz 9 dBi patch, RP-SMA](https://www.rotorama.com/product/maple-wireless-2-4g-9dbi-smerova-antena) at Rotorama (Czech) | 1 | €13,19 plus €4,99 shipping |

Both versions at ht-dron (73,00) were out of stock, and no other small 2.4 GHz patch was found in stock at a Polish shop. If you wait for ht-dron's SMA version, buy the [SMA pigtail](https://abc-rc.pl/pl/products/przejscie-u-fl-ipex-na-sma-jack-adapter-prosty-z-przewodem-200mm-9838.html) (7,32) instead.

**AliExpress: price unconfirmed**

| Part | Qty | Each |
|---|---|---|
| iFlight GM3506 gimbal motor with AS5048A encoder (item 1005011728866518) | 2 | about 90 |

The listing could not be opened by the checker; the price is from a search card and may not include VAT. Confirm that the listing says "with AS5048A encoder".

**Already owned:** the Seeed XIAO ESP32-S3 Sense (brain and camera).

**Also needed, not priced:** filament, a 1/4" nut, M3 screws (motor mounting, lid), one M4 screw about 20 mm (cradle pivot), thin stranded wire, a USB-C PD power bank or charger of 18 W or more.

**Sum:** Polish parts 139,62; antenna about 77 (at an assumed 4,25 zł per euro); motors about 180, unconfirmed. About 397 zł before shipping, which adds roughly 29 zł for three of the four Polish shops.

## 2. Print

Files in `cad/stl/`, each already in its print orientation; none needs supports as drawn.

| File | Part |
|---|---|
| `tub.stl` | base tub |
| `lid.stl` | base lid, carries the pan motor |
| `yoke.stl` | deck and both fork arms |
| `cradle.stl` | antenna plate and side plates |

**Before printing, measure the real parts** and correct `cad/radiomicroscope.scad`, then run `python3 tools/build_viewer.py desk` to regenerate the files:

- the motor's mounting screw circle and screw size (`mot_bolt_circle`, `mot_bolt_d`), on both faces of the motor;
- the encoder housing's diameter and height (`mot_enc_d`, `mot_enc_h`);
- the driver board outline, so you know where it will sit on the left arm.

Material and settings are your call; nothing here has been printed. The arms carry the load, so more perimeters there are worth more than infill.

## 3. Stage one: radio and brain on the desk, no motors

Proves the sensor, the link and the control page before anything can move.

1. Install `arduino-cli`, the ESP32 core (3.3.5 or newer) and the libraries ESPAsyncWebServer, AsyncTCP and ArduinoJson.
2. Change `AP_PASSWORD` in `firmware/brain/config.h`.
3. `make flash-sensor PORT=...` for the XIAO ESP32-C5 and `make flash-brain PORT=...` for the XIAO ESP32-S3 Sense (board option PSRAM: OPI, already set in the Makefile).
4. Wire four wires between them:

| Brain (S3) | Sensor (C5) |
|---|---|
| D2 | D6 |
| D3 | D7 |
| 5V | 5V |
| GND | GND |

5. Plug the antenna into the C5's socket through the pigtail. The socket is rated for about 30 matings: plug it once and tie the cable down.
6. Power the brain over USB, join the Wi-Fi network `RadioMicroscope`, open `192.168.4.1`.
7. **Expect:** the *link* and *sensor* marks turn green; *Survey all channels* lists networks within about ten seconds; tapping one shows its level changing as you turn the antenna by hand.

The *motors* mark stays red in this stage. That is correct.

## 4. Stage two: motors on the bench

Proves the drivetrain with nothing attached to it.

1. Install the Simple FOC library, then `make flash-motion PORT=...` for the ESP32 board.
2. Wire each driver to the motor controller:

| Motor controller pin | Pan driver | Tilt driver |
|---|---|---|
| PWM A, B, C | 25, 26, 27 | 32, 33, 13 |
| Enable | 22 | 4 |

   Both encoders share SCK 18, MISO 19, MOSI 23; chip select is 5 for pan and 21 for tilt; they take 3.3 V and ground from the controller. The drivers' pin names are not printed in the shop listing: follow the markings on the board.
3. Set the PD trigger to 12 V, check its output with a meter **before** connecting anything, then power the drivers from it. The controller board stays on USB for now.
4. Open the controller's USB console at 115 200 baud. Type `status`: both angles should follow the motors as you turn them by hand, even before alignment.
5. Type `cal`. Each motor swings about 30° and back. Both should report *ready*. If one reports *FAILED*, check the pole-pair setting (11 for GM3506) and the three motor wires.
6. Type `hold`: the motors should resist being turned and stay cool. If they sing or get warm, stop with `free` and lower `PAN_VOLT_LIMIT` / `TILT_VOLT_LIMIT`.

## 5. Stage three: assemble

1. Base: tripod nut into the tub floor, PD trigger inside with its socket at the opening, two wires for 12 V up through the lid's centre hole.
2. Pan motor upside down: rotor screwed to the lid, stator to the underside of the yoke deck with the encoder housing sitting in the deck's recess. The two power wires pass through the hollow shaft.
3. Tilt motor: stator on the inside of the right arm with its encoder housing through the arm; rotor screwed to the cradle's right side plate. The M4 screw through the left arm is the cradle's other pivot.
4. Boards: motor controller and both drivers on the outside of the left arm, 5 V converter on the deck, brain and sensor behind the cradle plate with the camera looking through its hole.
5. Add the serial link between brain and motor controller:

| Brain (S3) | Motor controller |
|---|---|
| D0 | 16 |
| D1 | 17 |
| GND | GND |

6. **Balance the cradle** before powering the motors: with the motors free it should stay at any tilt you leave it. Add a screw and nuts at the trim holes until it does.
7. Leave a slack loop in the wires that cross the tilt axis, and check by hand that the cradle swings from 15° below level to straight up without pulling anything.

## 6. First run

1. Power from the PD source. On the controller console: `free`, point the head straight ahead and level by hand, `zero`.
2. On the control page all three marks should be green. Nothing moves until you ask.
3. Tap an arrow: the head should move 5° that way. If an axis goes the wrong way, flip `PAN_DIR` or `TILT_DIR` in `firmware/motion/config.h`.
4. Set the beamwidth to 60 (the Maple patch) and press *Apply*.
5. *Survey*, pick a strong network, *Scan*. The map fills in a few minutes and the head turns to the strongest direction.
6. *Track*. Carry the transmitter (a phone hotspot will do) around the room; the head should follow. If it is lost the page says it is searching nearby, then the whole sky.

## What to expect to go wrong

- **Motor tuning.** The control gains in `firmware/motion/motion.ino` are starting values from the library's examples, not tuned for these motors. Slow motion may be jerky; builders of similar heads report the same.
- **Wrong reflections indoors.** Indoors the strongest direction is often a wall. That is real, not a fault; try outdoors or with line of sight for a first test.
- **Levels jumping.** A network that only beacons gives about ten frames a second; raise the dwell time on the control page for steadier readings.
- **Anything in this guide.** It was written from the design, not from a build. Corrections from the first build belong here.
