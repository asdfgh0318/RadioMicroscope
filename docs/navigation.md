# Navigation layer: compass, IMU, turn scan, logging, locating

Written 2026-11-11 from the code, which governs where this note disagrees with it. This is the plan that was set for the airborne iteration and what was done against it. The airborne unit itself is now parked; the same code serves the desk and handheld builds. Everything here passes PC tests or a compile check; **none of it has run on hardware**.

## Plan and status

| # | Step | Status | Where |
|---|---|---|---|
| 1 | Maths: tilt, tilt-compensated heading, compass calibration, antenna direction to world bearing, crossing bearing lines | done, tested on the PC | `lib/RMCore/src/rm_attitude.h`, `rm_locate.h` |
| 2 | Drivers for the MPU-6050 and the HMC5883L / QMC5883L compass | written, compile-checked | `firmware/brain/nav.h` |
| 3 | Drivetrain option with no motors, for a fixed antenna on a vehicle | written, compile-checked | `firmware/brain/drive_fixed.h` |
| 4 | Turn scan: one bearing per full turn of the vehicle | written, compile-checked | `firmware/brain/brain.ino` (`startTurn`, `onSample`) |
| 5 | Logging every reading to microSD | written, compile-checked | `firmware/brain/log_sd.h` |
| 6 | PC tool that crosses the logged bearings | done, tested on a synthetic log | `tools/locate.py` |
| 7 | Independent review, findings fixed | done: 8 defects and 14 of 16 improvements fixed | see "Review" below |
| 8 | Bench test on the ground build, carried around by hand | **not done: needs hardware** | |
| 9 | Flight | **not done** | |

## What it gives each build

- **Desk and palm (ground):** true compass headings instead of a north offset typed in by hand, and logs of every reading.
- **Airborne:** a fixed antenna on the drone, a turn scan at each hover point, and a transmitter position from the crossing of the bearings.

## Settings

All in `firmware/brain/config.h`:

| Setting | Meaning |
|---|---|
| `NAV_SENSORS 1` | read the IMU and compass on pins D4 (SDA) and D5 (SCL) |
| `NAV_TURNS_WITH_PAN` | 1 if the sensor board rides on the turning yoke, 0 if it is fixed to the base or the vehicle |
| `MAG_DECLINATION` | local magnetic declination in degrees, east positive; left at 0, look it up for your location |
| `MAG_MOUNT_YAW`, `MAG_FLIP_Y` | how the compass chip sits relative to the IMU |
| `HOLD_WORLD 1` | keep the antenna facing the same way in the world while the base is turned by hand; needs `NAV_TURNS_WITH_PAN 0` |
| `LOG_SD 1` | write the log to the microSD card of the XIAO ESP32-S3 Sense |
| `DRIVE_FIXED 1` | no motors; the antenna is fixed at `ANT_AZ`, `ANT_EL` relative to the vehicle |
| `SENSOR_RX5808 1` | RX5808 video receiver instead of the Wi-Fi sensor radio |

Airborne build: `DRIVE_FIXED 1`, `SENSOR_RX5808 1`, `NAV_SENSORS 1`, `NAV_TURNS_WITH_PAN 0`, `LOG_SD 1`. The receiver's clock and data lines then move to pins D0 and D1, because the card uses D8 to D10. On a motorised build, logging together with the RX5808 stops the build with a message, since both want D8 and D9.

## Wiring

| Part | Pins on the brain |
|---|---|
| MPU-6050 and compass | D4 (SDA), D5 (SCL), 3.3 V, ground |
| GPS (BN-880) | its TX to D7 |
| microSD | on the Sense board (D8, D9, D10 and an internal select pin) |

Mount the IMU with its X arrow toward the antenna's zero direction and its top side up.

## Using it

1. **Keep still at power-up.** The gyroscope's resting reading is measured for half a second.
2. **Calibrate the compass once:** press *Calibrate compass* on the control page and turn the whole unit through at least one full circle within 30 seconds. The result is stored. A turn of only part of a circle is rejected.
3. **Check the direction:** turn the unit clockwise seen from above. The heading on the page must rise. If it falls, set `MAG_FLIP_Y 1`.
4. **Check the tilt:** without turning it, tilt the unit about 20° forward and to each side. The heading must stay within a few degrees. If it swings, the compass chip is mounted upside down or turned relative to the IMU: correct the mounting or `MAG_MOUNT_YAW`. `MAG_FLIP_Y` does not cover an upside-down chip.
5. **Ground builds:** the north offset is now measured; the box on the page shows it and no longer accepts typing.
6. **Turn scan:** pick a target, press *Turn scan*, and turn the vehicle slowly through a full circle. When five sixths of the circle has been covered, the strongest direction is logged as one bearing and the next turn starts.
7. **Locate:** take turn scans from several clearly different places, then run `python3 tools/locate.py /path/to/rm_001.csv`. It prints the estimated position, how far the bearing lines miss it, and a warning for bearings that point away from it. `--geojson out.json` writes the lines and the result for a map.

## Log format

One CSV file per power-up, `/rm_NNN.csv`:

- `S` rows: one reading: time, GPS position, whether the compass was valid (`nav`), heading, pitch, roll, head angles, world direction, level, frames, channel.
- `B` rows: one bearing from a turn scan, in the same columns.

The position columns are empty when the GPS has no fix from the last three seconds; `locate.py` ignores bearings without a position.

## What the tests show, and what they do not

- 45 simulated attitudes are recovered exactly from simulated sensor readings, at the 67° magnetic dip of Poland.
- A compass shifted and stretched by nearby iron goes from 167° of worst-case heading error to none after calibration.
- A vehicle tilted 10° and turning at 30°/s keeps its tilt estimate.
- Five bearings with 5° of noise place a transmitter about 360 m away to within 11 m; six at about 500 m to within 21 m.

These are simulations with clean noise. Real compass errors near motors, reflections of the signal, and the GPS's own few metres of error are not in them.

## Limits to know before building

- **Compass placement decides everything.** The gimbal motors' magnets sit a few centimetres from every board on the ground builds and move relative to a compass on the yoke; no calibration removes that. The compass needs a mast or a place on the base (`NAV_TURNS_WITH_PAN 0`), which on the present design means running four wires across the pan axis.
- **Turn slowly.** Readings arrive five times a second by default, and the heading is smoothed. Above about 20° per second the bearing is pulled against the direction of turn. Alternating the direction of successive turns averages most of that out.
- **Signal strength is not a distance.** Position comes only from crossing bearings.
- **Elevation of a fixed antenna below −15°** is recorded as −15° in the map; the azimuth, and so the position, is unaffected.
- **Encoder faults are not detected** by the motor controller, and a pan axis turned by hand past ±180° while unpowered is taken to be within ±180° at the next start.
- **Not researched:** vibration, payload limits for a given drone, and the rules for flying it.

## Review

An independent review of everything written after the first review found eight defects and sixteen improvements. All eight defects are fixed:

| Found | Fix |
|---|---|
| Motor controller crashed on `free` or `zero` before the first alignment | the driver is started once at power-up on every path |
| Angles were frozen before alignment, and a zero taken then was lost | angles and the zero now come straight from the encoder |
| North offset was undefined with the antenna near the zenith and flipped beyond it | computed at the horizon |
| *Track* and map taps after a turn scan mixed world directions with head angles | converted in the firmware and on the page |
| A late "motors free" report could cancel a move that had just started | such reports are ignored for 300 ms after a command |
| Compass mounting angle was applied after tilt compensation | applied to the field vector first; a mirrored chip can be set too |
| With the RX5808, noise was logged as bearings | a level within 3 dB of the floor counts as nothing heard |
| A typed north offset was overwritten and a stale one saved | the typed value is kept separately and used only without a compass |

Improvements made: correct drive-voltage headroom, alignment that can be repeated, a tilt filter that stays right on a turning vehicle, gyroscope bias removal, less heading lag during a turn, turn-scan coverage at higher turn rates, video receiver armed after a restart, compass reachable on combined boards, out-of-range compass readings rejected, movement commands refused on a fixed antenna, log files never overwritten, stale GPS positions not logged, a safer enable pin, and non-numeric targets rejected.

Left as limits (listed above): encoder fault detection and the pan turn count across a power cycle.

### Third review

A third review covered what was written after the second: the motor controller's rewrite, the ESP-SDR client, the hold-direction feature and the re-lock search. It confirmed six of the eight earlier fixes as fully correct and two as partly fixed, and found seven new defects. All are fixed:

| Found | Fix |
|---|---|
| ESP-SDR client re-synchronised after almost every burst, because a time taken before reading was compared with one taken during it | the clock is read afresh at the comparison; sample bytes are now read in blocks |
| Hold-direction also ran during a turn scan, so the scan could never complete | it is off during scans and turn scans |
| Hold-direction swung the head when the compass came back from calibration | the first pass after the compass becomes valid only records the new north |
| After *Track* from a turn-scan peak the map and peak were still treated as world directions | the map is cleared and the peak is in head angles from then on |
| Hold-direction left the remembered peak behind when the base turned | the peak turns with it |
| A fixed antenna's direction on the vehicle (`ANT_AZ`) was ignored with the default sensor placement | a fixed antenna always uses its own direction |
| A peak too weak to track could start an endless lose-and-search loop | such a peak is not locked onto; the search widens, then stops |

Also made: hold-direction corrections capped at 10° per step; out-of-range readings of the second compass type rejected; gyroscope bias taken only if the unit was still; a failed pole-pair check during alignment reported instead of stored; a failed alignment no longer erases a good one; the ESP-SDR noise floor taken from the third-quietest channel the chip can receive; saved targets tagged by receiver so one build does not reuse another's; the page naming the receiver in use.

Not changed, by choice: a re-lock search clears the map on screen, and the hold-direction feature gives up the world direction at the pan travel limits.
