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

## MVP Implementation (completed 2026-03-09)

### Architecture
- **WiFi**: `WIFI_AP_STA` mode — AP ("RadioMicroscope") for web UI, STA for RSSI scanning
- **Web server**: AsyncWebServer + AsyncWebSocket at `/ws`
- **Web UI**: Dark theme, mobile-first, single HTML in PROGMEM (`include/web_ui.h`)
- **Sensors**: MPU-6050 (pitch/roll), async WiFi scan every 5s (non-blocking)
- **Control**: WebSocket JSON protocol, 20Hz throttled

### WebSocket Protocol
**Client → ESP32:** `{"type":"control","azimuth":N,"elevation":N,"trim":N}`
- azimuth: -100 (CCW) to +100 (CW), 0=stop
- elevation: 0-180 degrees
- trim: ±50μs azimuth center offset

**ESP32 → Client (200ms):** `{"type":"sensors","pitch":N,"roll":N,"networks":[...]}`

### Servo Control
- **Azimuth**: `writeMicroseconds(1500 + trim + speed*500/100)`, dead zone ±5%
- **Elevation**: `write(angle)` direct 0-180 mapping
- Safety watchdog: azimuth stops if no WS message for 2s

### File Structure
```
platformio.ini          # PlatformIO config for XIAO ESP32S3
src/main.cpp            # All firmware logic
include/web_ui.h        # HTML/CSS/JS as PROGMEM string
```

### Libraries
ESP32Servo, ESPAsyncWebServer, AsyncTCP, ArduinoJson, Adafruit MPU6050

---

## Future Phases
- **Phase 2**: Automated scan sweep, RSSI heatmap / 3D plot (Az vs El vs dBm)
- **Phase 3**: Lock/follow mode — track strongest RSSI, rescan on loss
- **Phase 4**: BN-880 GPS + compass for true heading, encoder for azimuth feedback
- **Phase 5**: Camera stream (OV2640), audio, battery power, touch pin wake
