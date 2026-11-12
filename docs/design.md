# RadioMicroscope v2: design

Written 2026-11-11 from the code and models in this repository, which govern where this document disagrees with them. Nothing here has been tested on hardware; figures marked *estimate* are calculations, not measurements.

## 1. What v1 got wrong

The v1 prototype (in `archive/v1/`) proved the idea and exposed four limits this design removes:

| v1 | Consequence | v2 |
|---|---|---|
| Azimuth was a hobby servo modified to spin freely, with no position feedback | The firmware never knew where the antenna pointed, so it could not build a map | Every axis reports its true angle from a magnetic encoder |
| One radio served the control page and measured signal strength | Measuring stopped whenever the page was served, and the page was reached through the directional antenna | A separate listening radio behind the antenna; the brain serves the page from its own antenna |
| Signal strength came from a full network scan every 5 s | Too slow to scan a sky or follow anything | The sensor sits on one channel and reports one transmitter several times a second |
| 2.4 GHz only | Half of Wi-Fi invisible | ESP32-C5 covers 2.4 and 5 GHz |

## 2. Architecture

```
                    moving with the antenna (cradle)
   antenna --pigtail--> SENSOR  XIAO ESP32-C5      listens only, reports levels
                        BRAIN   XIAO ESP32-S3 Sense camera, control page, modes
                           |  serial                 |  serial
                           v                         v
                        (sensor link)          MOTOR CONTROLLER  ESP32 + 2 drivers
                                                     |  on the fork arm
                                               pan motor, tilt motor (encoders)
   base (fixed): USB-C PD trigger --12 V, 2 wires through the pan motor's hollow shaft-->
```

Three small processors, each with one job:

- **Sensor** (`firmware/sensor/`). Never joins or serves a network. In *survey* it hops over 13 channels on 2.4 GHz and 25 on 5 GHz, 130 ms each, and lists every transmitter heard. In *stare* it stays on one channel and reports the median level of one transmitter's frames every report period (200 ms by default). It sends a heartbeat every second.
- **Brain** (`firmware/brain/`). Runs the modes, keeps the sky map, serves the control page and camera stills on its own access point (`RadioMicroscope`, address `192.168.4.1`), and sends pointing commands to the drivetrain.
- **Motor controller** (`firmware/motion/`). Closed-loop angle control of both motors with the Simple FOC library, 25 pose reports a second.

The algorithms live in `lib/RMCore/` with no hardware dependencies, so the same code runs in the firmware and in the PC tests.

Optional parts of the brain are switched in `firmware/brain/config.h`: the drivetrain, an RX5808 receiver in place of the sensor radio, navigation sensors and microSD logging.

### Why a separate motor controller

Field-oriented control needs six PWM outputs, an SPI bus with two chip selects and a loop that is never held up by a web server. The XIAO boards have 11 pins. A classic ESP32 board has the pins and gives the control loop a processor to itself.

### Drivetrain options

`DRIVE_BRUSHLESS` in `firmware/brain/config.h` selects the drivetrain:

| | Brushless (1, default) | Bus servos (0) |
|---|---|---|
| Parts | 2 gimbal motors with encoders, 2 drivers, ESP32 board | 2 Waveshare ST3215 servos, bus adapter |
| Cost per axis | about 115 zł, motor price unconfirmed | 105–109 zł, confirmed at Botland |
| Behaviour | silent, no backlash, fast; draws current to hold; head must be balanced | gearbox holds for free; audible; some backlash |
| Risk | control-loop tuning; motors bought from AliExpress | low |

## 3. Wiring

| From | Pin | To | Pin |
|---|---|---|---|
| Brain | D0 (TX) | Motor controller | 16 (RX) |
| Brain | D1 (RX) | Motor controller | 17 (TX) |
| Brain | D2 (RX) | Sensor | D6 (TX) |
| Brain | D3 (TX) | Sensor | D7 (RX) |
| Brain | D7 (RX) | GPS module TX, optional | |
| Brain | D4, D5 | reserved for I2C (compass, power monitor) | |
| Motor controller | 25, 26, 27, enable 22 | Pan driver | IN1–3, EN |
| Motor controller | 32, 33, 13, enable 4 | Tilt driver | IN1–3, EN |
| Motor controller | 18 (SCK), 19 (MISO), 23 (MOSI) | Both encoders | SPI |
| Motor controller | 5 / 21 | Pan / tilt encoder | chip select |

Both serial links run at 460 800 baud with the framing in `lib/RMCore/src/rm_link.h` (two start bytes, length, type, payload, CRC-16). With bus servos, D0/D1 go to the servo adapter at 1 Mbaud instead.

## 4. Power

One USB-C socket in the base. A USB-C Power Delivery trigger board asks the source for a fixed voltage for the motor drivers; a step-down converter on the yoke makes 5 V for the three processor boards.

- The source must support Power Delivery. A plain 5 V power bank will not work: the driver boards are listed as needing at least 8 V.
- Set the trigger to 12 V, or 15 V if the source does not offer 12 V, and set `SUPPLY_VOLTS` in `firmware/motion/config.h` to match.
- *Estimate:* about 12 W worst case with both motors holding hard (each limited to 5 V across a 5.6 Ω winding, about 4.5 W), around 5 W typical with a balanced head; roughly six hours on a 10 000 mAh power bank.

## 5. Mechanics

Model: `cad/radiomicroscope.scad`; printable parts in `cad/stl/`; interactive view built by `tools/build_viewer.py`.

- **Size:** 154 mm across the fork, 144 mm tall, 120 mm base. Tilt axis 104 mm above the table.
- **Four printed parts:** base tub, lid, fork yoke, antenna cradle. Each prints without supports in the orientation exported.
- **Pan motor upside down.** Its rotor is screwed to the lid and its stator to the yoke, so every signal wire stays on the moving part and only two power wires pass through the hollow shaft.
- **Fork.** The cradle hangs between two arms, driven by the tilt motor on one side and carried by an M4 pivot screw on the other. Each arm is a channel section because it prints standing up.
- **Balance.** A direct-drive motor has to supply the full torque of any imbalance continuously, and builders report overheating when it is ignored (`papers/aliexpress-brushless/`). The antenna sits just ahead of the tilt axis and the boards just behind; two screw holes take a trim weight.
- **Travel:** pan ±175° (a cable loop, no slip ring), tilt −15° to +95°. The firmware clamps at the stops and never takes the long way round.
- **Not verified:** the motor's screw pattern, the encoder-housing dimensions, and the outlines of the ESP32 board, driver and converter are assumed. Measure the parts before printing.

A trimmed version (narrower camera strip, 90 mm base) comes to 142 × 138 mm. The 90 mm antenna sets that floor: at 2.4 GHz the wavelength is 125 mm and a directional antenna needs most of a wavelength across.

## 6. Antenna

Decision record: `papers/antennas/REPORT.md`.

- **Fitted:** Maple Wireless 2.4 GHz patch, 9 dBi, beam 60° × 65°, linear, 90 × 80 × 10 mm, 17 g or 33 g depending on the shop. All figures are the vendor's.
- **5 GHz swap on the same cradle:** Cyberteam SkyEter13 (13 dBi, 33° beam, 82 × 82 × 12 mm, 80 g, 5.45–5.75 GHz) or GEPRC Triple Feed Patch-1 (9.4 dBi, 55°, circular, 20 g, 5.47–6.13 GHz). Neither covers the lower 5 GHz channels 36–64; no light antenna found does.
- **Resolution is about one beamwidth.** A finer scan grid locates a peak better but does not separate two sources closer than the beam. With a 60° beam the default 10° grid gives six samples per beam, more than the two and a half that sampling theory asks for.
- **Set the beamwidth in the control page.** The tracker uses it to turn a difference in level into an angle; it starts at 40° and should be 60 for the Maple patch.
- **Feed loss:** about 0.5 dB at 2.4 GHz and 0.9 dB at 5.8 GHz for a 10 cm pigtail plus connector. The antenna socket on the radio board is rated for 30 matings, so plug it once and tie the cable down.

## 7. Modes

- **Survey.** The brain collects the sensor's transmitter list; tapping one makes it the target.
- **Scan.** Rows of constant elevation, alternating direction. The azimuth step widens with elevation so points stay evenly spaced on the sky: 848 points for a hemisphere at 5°, 223 at 10°. At each point the head settles, the first report is discarded, and reports are added up until at least three frames have been heard. *Estimate:* a 10° scan takes a few minutes; it depends on how often the target transmits.
- **Track.** Five readings per cycle: the centre and one probe to each side in both axes, half a beamwidth away. Near its peak a beam falls off as a parabola in decibels, so the difference between the two side readings is proportional to the pointing error. The centre moves half of the estimated error each cycle. Three silent cycles count as lost, which starts a new scan followed by tracking.
- In simulation with 2 dB of reading noise and a 40° beam the tracker holds a still source to about 3.5° RMS and follows one moving 1.5° per cycle to about 5° (`make test`). Real indoor reflections will be worse than that noise model.

## 8. Bring-up

1. Flash the three boards (`make flash-sensor`, `flash-brain`, `flash-motion`, each with `PORT=`).
2. On the motor controller's USB console, set the tilt near the middle of its travel and type `cal`. Each axis swings about 30° and back once to find its alignment; the result is stored and later starts are motionless.
3. Point the head straight ahead and level by hand and type `zero`.
4. Join the `RadioMicroscope` network (password in `firmware/brain/config.h`; change it) and open `192.168.4.1`.
5. Set the beamwidth, run a survey, pick a target, scan.

If a motor fails to align, check the pole-pair setting first (GM3506: 11).

## 9. Roadmap

Researched, with sources in `papers/`, not implemented:

1. **Spectrum mode** using the ESP-SDR firmware on the same sensor board: a spectrum per direction for any emitter in about 2.2–2.65 GHz and 5.18–5.8 GHz, not only Wi-Fi. Its gain is not calibrated in decibels and it captures in bursts (`papers/sdr/REPORT.md`).
2. **EasyComm protocol** on a serial or network port, so existing satellite-tracking software can steer the head (`papers/prior-art/REPORT.md`).
3. **Removing the beam shape from maps** on a PC, to separate sources closer than the beam; the first experiment is to scan one fixed beacon, which measures the beam itself (`papers/imaging-science/REPORT.md`).
4. **Compass, IMU, GPS and logging**: written and described in [`navigation.md`](navigation.md), not yet tried on hardware. They give the ground builds true headings and are the basis of the airborne iteration.
5. **A palm-sized 5.8 GHz variant** for analog drone video: drafted in [`palm-5g8.md`](palm-5g8.md), with an RX5808 receiver option already in the brain firmware (`SENSOR_RX5808`).

Considered and set aside: ranging chips (all need a cooperating tag), phase-based imaging (one ESP32's phase is random from packet to packet), ready-made camera gimbals (no angle read-back verified, payload of about 20 g).
