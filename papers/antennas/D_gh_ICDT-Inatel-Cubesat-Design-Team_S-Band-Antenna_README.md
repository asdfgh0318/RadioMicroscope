<div align="center">
  <img src="https://raw.githubusercontent.com/ICDT-Inatel-Cubesat-Design-Team/.github/refs/heads/main/profile/assets/icdt-logo.png" alt="ICDT Logo" style="width: 128px;"/>
</div>
<h1 align="center">S-Band RHCP 2.45 GHz Antenna</h1>

<p align="center">
    <a href="#"><img alt="Static Badge" src="https://img.shields.io/badge/status-testing-yellow"></a>
    <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/releases"><img alt="GitHub Release" src="https://img.shields.io/github/v/release/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna"></a>
    <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/issues"><img alt="GitHub Issues or Pull Requests" src="https://img.shields.io/github/issues/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna"></a>
    <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/pulls"><img alt="GitHub Issues or Pull Requests" src="https://img.shields.io/github/issues-pr/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna"></a>
    <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna"></a>
</p>

<p align="center">
    <a href="#overview">Overview</a> •
    <a href="#repository-organization">Repository Organization</a> •
    <a href="#releases">Releases</a> •
    <a href="#references">References</a> •
    <a href="#license">License</a>
</p>


## Overview
This project involves the development of an S-band antenna tailored for a 1U CubeSat platform. The system is engineered to handle both uplink and downlink capabilities using LoRa technology, specifically optimized for integration with the E80-900M2213S module.

<p align="center">
    <img src="docs/pictures/Antenna-Front.png" width="400">&nbsp;&nbsp;&nbsp;<img src="docs/pictures/Antenna-Back.png" width="400">
</p>

**Technical Parameters**
- Center Frequency: 2.45 GHz
- Axial Ratio Bandwidth: 14 MHz (2443 – 2457 MHz for AR < 3 dB)
- Peak Realized Gain: 7.58 dBi
- Polarization: Right-Hand Circular Polarization (RHCP)
- Connector Type: Right-Angle SMA

## Repository Organization

* `docs`: Technical documentation and datasheets.
* `hardware`: Core hardware files.
    * `3D`: 3D models (.step).
    * `Fabrication`: BOM and Gerber files for JLCPCB manufacturing.
    * `PCB`: KiCad schematics and layout design.
* `simulation`: Ansys HFSS simulation and data files.

## Releases

<table>
  <thead>
    <tr>
      <th>Render</th>
      <th>Board Name</th>
      <th>Status</th>
      <th>Latest Release</th>
      <th>Date</th>
      <th>Datasheet</th>
      <th>BOM</th>
      <th>Ordering Info</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><img src="docs/pictures/Antenna-3D.png" alt="render" height="100px" style="height: 100px;"/></td>
      <td>S-Band Antenna v1</td>
      <td>🧪 Testing</td>
      <td><a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/S-Band-Antenna/releases/tag/v1.0">v1.0</a></td>
      <td>05-06-2026</td>
      <td><a href="docs/Datasheet S-Band RHCP 2.45 GHz Antenna.pdf">PDF</a></td>
      <td>Yes</td>
      <td><a href="hardware/Fabrication/GERBER-Antenna.zip">GERBER</a> (JLCPCB)</td>
    </tr>
  </tbody>
</table>

## References

This project was based on the SpaceLab UFSC [S-Band Antenna Project](https://github.com/spacelab-ufsc/sband-antenna/), with special thanks to [Lucas Ryan](https://github.com/SPHINXLRC) (SpaceLab) and [Yunior Alcantara](https://github.com/yag0x1) (SpaceLab) for their assistance with the SMA connectors.

**Missions Associated with this Project**

<p>
  <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/"><img src="https://raw.githubusercontent.com/ICDT-Inatel-Cubesat-Design-Team/.github/refs/heads/main/profile/assets/projects/karawara.png" width="72"></a>
  <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/"><img src="https://raw.githubusercontent.com/ICDT-Inatel-Cubesat-Design-Team/.github/refs/heads/main/profile/assets/projects/samauma.png" width="72"></a>
  <a href="https://github.com/ICDT-Inatel-Cubesat-Design-Team/"><img src="https://raw.githubusercontent.com/ICDT-Inatel-Cubesat-Design-Team/.github/refs/heads/main/profile/assets/projects/wanderlust.png" width="72"></a>
<p>

## License

This project is licensed under the permissive, weakly-reciprocal **[CERN-OHL-W-2.0](LICENSE)** open-hardware license. You are free to modify and distribute these files, provided downstream hardware design modifications remain under the same terms.