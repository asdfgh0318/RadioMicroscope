# RadioMicroscope — Project Plan

## Raw Notes (from handwritten notebook, 2026-03-08)

### Note 1 — System Overview & Description
- RadioMicroscope will be a **2-DOF tracker** with a **directional antenna** connected to the micro UFL of the XIAO ESP32S3 Sense
- A **camera** will point the same way as the antenna, collecting simultaneously **video stream, audio, and wifi**
- Will **map direction (heading vs elevation) vs signal strength on a 3D plot**
- Sketch: camera + antenna on pan servo, sitting on yaw servo (360 deg mod)
- Two **9g servos**: yaw (PWM2) and pan/tilt (PWM1)
- Connected to **XIAO ESP32S3 Sense** with onboard camera
- Tasks: figure out wiring/pinouts, propose power supply (batt vs DC in)

### Note 2 — Features & Considerations
- Wake / toggle modes using **Touch Pins** (double click)
- Plan wiring considering best voltage from official XIAO site docs
- Download 3D models of XIAO and SG servos — test AI 3D modelling capabilities
- Consider using **encoder** for precise azimuth data
- **Scan mode**: scan all directions, output RSSI vs Elevation vs Azimuth plot
- **Lock/follow mode**: lock onto specific WiFi RSSI direction, track RSSI, if lost — rescan and lock again
- Consider adding **BN-880** (GPS + compass) — needs UART and I2C

### Prototype Photo
- Current assembly: Seeed Studio XIAO board + SG90 micro servo + small breakout board (IMU?) on a white cylindrical base, wired together on a metal/PCB mounting plate

---

## Hardware Setup
*(to be filled after Q&A)*

## Plan
*(to be agreed upon)*
