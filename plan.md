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

### Pin Map
| Component | Pin Label | GPIO | Protocol |
|-----------|-----------|------|----------|
| Servo Azimuth (360-mod SG90) | D0 | GPIO1 | PWM |
| Servo Elevation (standard SG90) | D1 | GPIO2 | PWM |
| MPU-6050 SDA | SDA/D4 | GPIO5 | I2C |
| MPU-6050 SCL | SCL/D5 | GPIO6 | I2C |
| Directional Antenna | UFL connector | — | — |
| Power (MVP) | USB-C | — | 5V |

**Important**: Use symbolic pin names `D0`, `D1`, `SDA`, `SCL` in code — not raw GPIO numbers.

### Power Budget (MVP — USB-C powered)
| Component | Typical Current |
|-----------|----------------|
| XIAO ESP32S3 (WiFi active) | ~200mA |
| SG90 servo x2 (under load) | ~300mA |
| MPU-6050 | ~4mA |
| **Total** | **~504mA** |

USB-C provides up to 500mA (USB 2.0) or 900mA (USB 3.0). Adequate for MVP. Battery power is a future consideration.

### Servo Notes
- **Azimuth (360-mod)**: Continuous rotation. PWM controls speed/direction, not angle. Center ~1500μs = stop. Trim adjustable via web UI (±50μs).
- **Elevation (standard)**: Position control 0-180°. Standard PWM servo operation.

## Plan
*(to be agreed upon)*
