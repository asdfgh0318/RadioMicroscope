# Breitband-Vivaldi-Antenne (Broadband Vivaldi Antenna Design)

![Status](https://img.shields.io/badge/status-in%20progress-yellow) ![Type](https://img.shields.io/badge/type-university%20project-blue) ![License](https://img.shields.io/badge/license-MIT-lightgrey)

> **Status note:** This repository documents an ongoing university project (Hochschule Hannover, course project under Prof. Dr.-Ing. J. Passoke). It currently contains **documentation only** — the OpenEMS/Octave scripts, KiCad layout files, and measurement report will be added here once the project is finalized and submitted.

![Architecture](docs/architecture.svg)

## Overview

Design and electromagnetic field simulation of a planar broadband Vivaldi antenna operating from **850 MHz upward**, built on low-cost FR4 substrate with a 50 Ω SMA-compatible feed. The project covers the full pipeline from electromagnetic simulation to physical fabrication and RF measurement.

## Objective

- Design a tapered-slot Vivaldi antenna for wideband, directional radiation.
- Simulate the design in OpenEMS (open-source FDTD solver) via Octave.
- Translate the simulated geometry into a manufacturable PCB layout.
- Fabricate the antenna and validate it with real RF measurements.

## Technologies

| Category | Tools |
|---|---|
| EM Simulation | OpenEMS, GNU Octave |
| PCB Design | KiCad |
| Substrate | FR4 (εr = 4.3, tan δ = 0.023, 1 mm thickness) |
| Fabrication | PCB milling (faculty lab) |
| Measurement | Vector Network Analyzer, SMA / 50 Ω |
| Visualization | Octave, ParaView |

## Technical Concepts

- Tapered-slot (Vivaldi) antenna geometry for broadband, directional radiation
- Balun design for unbalanced-to-balanced (coax-to-antenna) impedance matching
- FDTD electromagnetic field simulation
- Return loss (S11) and radiation pattern optimization
- Gerber file generation and PCB milling workflow

## Approach

1. **Simulation** — Model the antenna in OpenEMS, driven by Octave scripts; iterate geometry to optimize S11 and radiation pattern across the target band.
2. **PCB Layout** — Translate the simulated geometry into a manufacturable layout in KiCad; lay out the SMA footprint for a clean 50 Ω transition.
3. **Manufacturing** — Mill the antenna on FR4; mount an SMA end-launch connector.
4. **Measurement** — Verify return loss (S11) at 50 Ω with a vector network analyzer and compare against simulation.

## Challenges

- Balancing simulation accuracy against computation time in OpenEMS.
- Designing a balun that correctly matches impedance across the full target band.
- Translating a simulated geometry into a physically millable PCB layout without degrading performance.

## Skills Demonstrated

- Electromagnetic field simulation (OpenEMS/Octave)
- RF/antenna design fundamentals
- PCB layout (KiCad) and Gerber file generation
- RF measurement methodology (VNA, S-parameters)

## Possible Extensions

- Add a metal reflector or director to increase directivity/gain.
- Extend the design to a phased-array configuration.
- Integrate the antenna into a small UAV telemetry/RC link demonstrator.

## License

MIT — see [LICENSE](LICENSE).

## Author

**Abdellatif Ali** — B.Sc. Elektro- und Informationstechnik, Hochschule Hannover
[LinkedIn](https://linkedin.com/in/abdellatif-ali-b34295362)
