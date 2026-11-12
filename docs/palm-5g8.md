# RadioMicroscope handheld 5.8: design note

Written 2026-11-11. A palm-sized, carried sibling of the desk build for analog drone video on 5.8 GHz. It is a working draft: the model and the firmware option exist and nothing has been built. Evidence is in `papers/vrx-5g8/` (`REPORT.md`, `EXTRACTS.md`); those govern where this note disagrees with them.

## What it is for

A small head that keeps a 5.8 GHz patch antenna pointed at a drone's analog video transmitter by signal strength alone, with no GPS or telemetry from the drone. It can also scan and map 5.8 GHz video transmitters around it, like the desk build does for Wi-Fi.

It is **carried in the hand, next to the pilot**: the head follows the pilot's own drone and feeds a cleaner video signal to goggles or a monitor. A unit carried on a drone is parked; its plan is kept at the end of this note.

## The "new analog VRX ESP"

The best match found is **C5VRX** (github.com/Twotoz/C5VRX, GPL-3.0, repository created 2026-08-30): a Seeed XIAO ESP32-C5 and seven resistors that receive analog 5.8 GHz video and output a composite signal for goggles or a monitor. A second project, ESPsoup, shows the picture on a phone or PC instead.

Both run today and both are experimental. C5VRX's own README says its demodulator "has one positive NTSC check; PAL, weak-signal behaviour and range still need hardware validation", and warns against relying on it as the only video path. For that reason this design does not depend on it:

| Receiver | Video out | Signal strength | Maturity | Use here |
|---|---|---|---|---|
| RX5808 module | yes, to goggles | analog pin, read by the brain | mature; used by lap timers and diversity receivers | **primary** |
| XIAO ESP32-C5 with C5VRX | yes, through a 7-resistor DAC | built-in meter | experimental | optional second video path, on its own board |
| XIAO ESP32-C5 with ESPsoup | phone or PC only, black and white | "Find" mode | beta, lab-tested | bench tool |

## Receiver: two options in the firmware

| | ESP-SDR on a XIAO ESP32-C5 | RX5808 module |
|---|---|---|
| Setting in `firmware/brain/config.h` | `SENSOR_ESPSDR 1` | `SENSOR_RX5808 1` |
| Signal strength for steering | yes: mean power of short sample bursts | yes: voltage on its RSSI pad |
| Picture for goggles | **no** | yes |
| Other signals | anything in about 2.2–2.65 GHz and 5.18–5.8 GHz | 5.8 GHz video channels only |
| Board | the 30,90 zł C5 already in the desk build | no Polish price found |
| Wires to the brain | two (serial), as for the Wi-Fi sensor | four, plus video out |
| Maturity | ESP-SDR is new community firmware; this client for it is untried | module is mature; this driver is untried |

**ESP-SDR is the receiver you asked for on the handheld.** The brain tunes it by frequency, takes bursts of 1 024 samples at 20 MS/s (about the width of one video channel), and uses their mean power as the level. Several bursts per report are reduced to their median.

What that choice costs and leaves open:

- **No picture.** ESP-SDR hands over samples, not video. For a picture in goggles, add an RX5808 on the same antenna, or use C5VRX, which is a different firmware for the same board and cannot run at the same time as ESP-SDR.
- **Levels are relative.** ESP-SDR's gain is not calibrated in decibels. A survey measures the no-signal floor as the third-quietest channel among those the chip is known to receive, and stores it; levels are then decibels above that floor. Run the first survey with the transmitter off.
- **Fixed gain.** Automatic gain would hide the very changes the head steers by, so the gain is set once (middle of the chip's range by default). If a nearby transmitter reads the same at every angle, lower `ESPSDR_GAIN`.
- **Channels above 5800 MHz are unconfirmed.** The published reception table for the C5 ends at 5800 MHz; 20 of the 48 video channels lie above it.
- **Reviewed once, never run.** An independent review found that the first version would have re-synchronised after almost every burst; that and its other findings are fixed (see [`navigation.md`](navigation.md)).
- **Reply formats are partly assumed.** The capture reply is documented exactly; for the gain and frequency commands the documentation gives no reply text, so any reply that is not an error is accepted.

## Architecture

```
  5.8 GHz patch --> XIAO ESP32-C5 with ESP-SDR --serial, 2 Mbaud--> BRAIN  XIAO ESP32-S3
                                                                      |  serial
                                                                      v
                                              MOTOR CONTROLLER  ESP32 + 2 drivers --> motors
  compass + IMU on the grip --I2C--> BRAIN
```

- The separate Wi-Fi sensor firmware of the desk build is not used here; the same C5 board is flashed with ESP-SDR instead (its project provides a browser flasher).
- The scan, track and control-page code is the same as the desk build. A survey steps through the 48 analog video channels and lists each with its level; tapping one makes it the target.
- The motor controller firmware is unchanged; set the pole pairs to 7 for GM2804 motors.

## Mechanics

Model: `cad/palm58.scad` (the desk model with different inputs); printable parts in `cad/stl-palm58/`; view built with `python3 tools/build_viewer.py palm58`.

- **Size:** head 81 mm across the fork and 104 mm tall on an 80 mm base, plus a 115 mm grip below.
- **Antenna:** Foxeer Echo 2, 5.5–6.0 GHz, 9 dBi, 40 × 22 mm, 8 g, circular polarisation. Buy the right-hand (RHCP) version: analog video transmitters normally use it, and mixing the two hands costs a lot of signal.
- **Motors:** two iFlight GM2804 (35 × 25 mm, 51 g, 0.025–0.034 N·m). The cradle carries about 12 g, so torque is not the limit; the motors themselves now set the size.
- **Boards:** receiver behind the antenna (drawn as an RX5808; the C5 board is smaller); brain, both drivers and the 5 V converter flat on the deck under the cradle; motor controller on the left arm; USB-C trigger in the base.
- **Assumed, not measured:** antenna thickness, motor screw pattern and encoder housing, board outlines.

## What existing trackers teach

- The documented signal-strength-only trackers compare two or three fixed antennas aimed slightly apart and turn toward the stronger. They are yaw-only, and a review of one said "the response could be snappier".
- This design uses one antenna and probes around the target instead. No published build of that method on 5.8 GHz video was found, so its tracking speed against a fast drone is unknown. Each tracking cycle is five readings with a move between each; a drone crossing close by will outrun it.
- A wider antenna beam is more forgiving for tracking; the Echo 2's wide beam suits this better than a narrow array would.

## Parts

| Part | Qty | Price | Shop | Status |
|---|---|---|---|---|
| Foxeer Echo 2 RHCP patch | 1 | 121 zł | [ht-dron](https://www.ht-dron.pl/Foxeer-Echo-2-5-8G-9dBi-RHCP-SMA-FPV-p9191) | confirmed; out of stock when checked |
| RX5808 receiver module | 1 | €7,49 | Rotorama (Czech; marked discontinued) | confirmed there; **no Polish price found** |
| Seeed XIAO ESP32-S3 (brain) | 1 | 37,90 zł | Botland | listing read; orderable |
| Classic ESP32 board (motor controller) | 1 | about 30 zł | — | not checked; my estimate |
| SimpleFOC Mini driver | 2 | 25,00 zł | Gotronik | confirmed, in stock |
| iFlight GM2804 with AS5048A encoder | 2 | about 72 zł | AliExpress | unconfirmed search-card price |
| USB-C PD trigger, 5 V converter, tripod screw | 1 each | 12,00 + 4,90 + 7,45 zł | Gotronik, ABC-RC | confirmed |

Roughly 450 zł, about half of it unconfirmed. The Sense board you already own can be the brain instead of a new XIAO.

## Carrying it

- **Grip.** A printed grip, 115 mm long, screws to the tripod thread in the base (`cad/stl-palm58/grip.stl`). The power cable runs down its centre to a USB-C PD power bank in a pocket or strapped below.
- **Compass and IMU at the bottom of the grip**, about 13 cm from the motors. That distance is the reason they go there: the motor magnets would swamp a compass mounted on the head. Their four wires run up through the grip and the pan motor's hollow shaft with the two power wires.
- **Holding direction while you move.** With `NAV_SENSORS 1`, `NAV_TURNS_WITH_PAN 0` and `HOLD_WORLD 1` in `firmware/brain/config.h`, the head turns against your hand so the antenna keeps facing the same way in the world, and the tracker's remembered direction turns with it. In simulation, with the hand swinging the base 5° per tracking cycle, the tracker holds a still source to 3.4° RMS with this on and 6.9° without.
- **What it does not do:** it corrects turning about the vertical only. Tilting the grip moves the antenna until the tracker catches up. A scan still needs the grip held still.
- **Weight**, my estimate, not weighed: motors 102 g, boards about 25 g, antenna and receiver 12 g, printed parts about 160 g; roughly 300 g without the power bank.

Settings for the handheld build: `SENSOR_ESPSDR 1` (or `SENSOR_RX5808 1`), `NAV_SENSORS 1`, `NAV_TURNS_WITH_PAN 0`, `HOLD_WORLD 1`, and in `firmware/motion/config.h` 7 pole pairs for the GM2804 motors.

## Video receiver wiring

For a picture in goggles the handheld needs an RX5808 (ESP-SDR gives none). The RX5808 does two jobs on one antenna: it gives the picture and it tells the brain how strong the signal is. With `SENSOR_RX5808 1` the brain steers by it; with `SENSOR_ESPSDR 1` only its power and video pads are used.

| RX5808 pad | Goes to | Purpose |
|---|---|---|
| Antenna | the patch antenna, through its SMA connector | |
| +5 V, ground | 5 V converter | power, about 170 mA |
| Video | goggles or monitor AV input (with ground) | the picture |
| RSSI | brain D2 | signal strength as a voltage |
| CH1 | brain D9 | tuning data |
| CH2 | brain D3 | tuning select |
| CH3 | brain D8 | tuning clock |

- **The module must accept serial tuning (the "SPI mod").** Some are sold that way; others need the small hardware change described by the rx5808-pro-diversity project (page saved as `papers/vrx-5g8/D_sheaivey_spimod.html`; I could not extract its text, so check it before buying). The pad-to-pin assignment above follows the PhobosLT lap timer.
- **Set the two voltages** `RX5808_RSSI_MIN_MV` and `RX5808_RSSI_MAX_MV` in `firmware/brain/config.h` from a meter on the RSSI pad: transmitter off, then transmitter a metre away. The values in the file are placeholders.
- **Goggles:** the video pad and ground go to the goggles' AV input.
- A level within 3 dB of the "transmitter off" voltage counts as nothing heard, so the head does not chase noise.

The same receiver works on the desk build: set `SENSOR_RX5808 1` there and fit a 5.8 GHz antenna to its cradle.

## Decisions (2026-11-11)

1. **Focus:** the desktop build, this handheld build, and the video-receiver path. The airborne unit is parked.
1. **Handheld receiver:** ESP-SDR on the XIAO ESP32-C5.
2. **Handheld means this motorised head, carried**, not a motor-less wand.
3. **C5VRX is planned, not built.** Plan below.
4. **Brushless stays.** No servo version.

Still open: a Polish source and price for the RX5808.

## Plan: C5VRX as a second video path

Goal: a picture from the ESP32-C5 alongside the RX5808, to judge whether C5VRX can replace the receiver module later.

1. **Bench test before any integration.** Flash C5VRX on a spare XIAO ESP32-C5, build its seven-resistor output (pin order matters: 8.2 kΩ on D4 up to 240 Ω on D9, 200 Ω to ground), run its built-in DAC self-test, then compare its picture with the RX5808's from the same transmitter at 1 m, 10 m and through a wall. This answers the question its README leaves open: range and weak-signal behaviour.
2. **Share the antenna.** Either a two-way splitter (about 3 dB lost on both paths; no part was sourced) or a second small patch beside the first. A second patch costs 8 g and no signal, and is the simpler start.
3. **Mount.** The board is 21 × 17.8 mm and fits behind the cradle plate next to the RX5808. It needs 5 V and ground only; its video goes to a second input on the goggles or to a switch.
4. **Decide.** If C5VRX holds a picture as far as the RX5808 does, the next step is to make it report signal strength to the brain, so one board does both jobs. That means changing C5VRX itself, which is GPL-3.0: the change would have to be published under the same licence.

Nothing in the brain firmware changes for steps 1–3.

## Parked: airborne iteration with GPS, compass and IMU

Goal: carry the receiver on a drone and locate 5.8 GHz transmitters on the ground, instead of only pointing at them.

**Why the three sensors.** On the ground the head knows where it points because it stands still. In the air every reading must be tagged with where the drone was (GPS), which way it faced (compass) and how it was tilted (IMU). A reading then becomes a bearing line from a known point, and bearing lines taken from several points cross at the transmitter.

**Mechanism.** The two-motor head is the wrong tool in the air: 102 g of motors on a small quad, and the drone can already turn. The plan is:

- Fix the patch antenna to the airframe, tilted down toward the ground ahead.
- Scan by yawing the drone through a full turn while hovering; the drone is the pan axis.
- If a tilt axis proves necessary, add one brushless motor for tilt only, using the motor controller as it is.

**Hardware.** Receiver 3.6 g, antenna 8 g, brain 3 g, plus sensors:

| Sensor | Part | Status |
|---|---|---|
| GPS and compass | BN-880, already owned | both read by the firmware (GPS on pin D7, compass on I2C) |
| IMU | MPU-6050, already owned (from v1) | read by the firmware, with a tilt filter |
| Logging | microSD slot on the XIAO ESP32-S3 Sense, already owned | written to by the firmware |

An alternative worth checking first: most flight controllers already have all three sensors and can send position, heading and attitude over a serial port. Reading that would need no extra sensors at all.

**Firmware work.** Steps 1 to 5 below are written and described in [`navigation.md`](navigation.md); they pass PC tests or a compile check and have not run on hardware.

1. Compass driver on the I2C pins (D4, D5), with calibration by turning a full circle. *Written.*
2. IMU driver and a tilt estimate, combined with the compass for a heading that stays correct when the drone leans. *Written.*
3. Convert each reading from "antenna direction on the drone" to a bearing on the map. *Written.*
4. Log every reading to the microSD card. *Written.*
5. A PC tool that crosses the bearing lines. *Written:* `tools/locate.py` prints the position and can write the lines as GeoJSON for a map.
6. Bench test on the ground, carried by hand. *Not done.*
7. Optional live results over the telemetry link. *Not started.*

**Known risks.**

- A compass close to motors and power wires reads badly. Mount the BN-880 on a mast, and cross-check against the GPS direction of travel when moving.
- Signal strength from the RX5808 is relative, so position must come from crossing bearings, not from strength as a distance.
- Vibration, mass limits for a given quad, and the rules on flying with extra payload were not researched.
- The whole chain can be tried on the ground by carrying the unit around, before anything flies.

