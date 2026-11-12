# Gimbal research extracts (pan/tilt for RSSI-vs-direction instrument)

Retrieved 2026-11-11. All files are untrusted downloads, never executed. Quotes are verbatim from the
local file named; page = PDF page (or section/post for web/JSON). "Evidence": [V] = opened at source
and quoted below; [S] = search snippet only (no quote available from an opened page).

Where a claim has no quote here, it is not a claim. See "Not retrieved" at the end.

---------------------------------------------------------------------------------------------------
## 1. Caddx GM3 V2-20 Quick Start Guide V1.1  [V]
- URL: https://www.hobbydrone.cz/user/related_files/gimbal_caddxfpv_gm3_v2-20.pdf (Czech reseller copy of Caddx manual)
- Local: `Caddx_GM3_V2_hobbydrone.pdf` (1 page)
Quotes:
- Intro: "The gimbal supports stabilization and adjustment along the pitch, roll, and yaw axes."
- Camera: "It is compatible with Walksnail Avatar/ Ascent series cameras with a mounting width of 20mm."
- Supply: "Ensure the external power supply to the gimbal is within the specified range (9~25.2V DC, 3S-6S LiPo battery)."
- "The head-tracking UART cannot be controlled simultaneously by other protocols."
- Control: "The three-axis gimbal supports the following four control methods: direct head-tracking connection / S.BUS / CRSF control, PWM control, and Mavlink control. The priority of these control methods decreases in the order listed."
- PWM1: "The channel is used to select the gimbal's working mode. There are three modes available: 1.Translation Mode: Pitch and roll remain level, while the yaw axis follows. 2.Translation Roll Mode: Pitch remains level, while roll and yaw axes follow. 3.Three-Axis Follow Mode: Pitch, roll, and yaw axes all follow."
- PWM3: "This channel controls the gimbal's pitch axis ... You can adjust the gimbal's rotation angle range by modifying the channel travel settings on the remote controller."
- PWM4: "This channel controls the gimbal's yaw axis."
- UART: "Connect the gimbal's UART_Rx and UART_Tx to a UART port's Tx and Rx on the flight controller. The gimbal function can be enabled in the INAV firmware by selecting "gimbal" as the peripheral for that port."
- "Mavlink control is only supported on PX4/ArduPilot firmware"
- Lock: "double-press the lower direction on the 5- way button to enable/disable the gimbal lock. When locked, stabilization is disabled, suitable for takeoff and landing." (head-tracking goggles menu item 8, needs gimbal fw V3.6+)
- PC tool shows (GimbalSetting screenshot text, p1): "EULER ... ACCE ... GYRO ... ANGL" rows with live numbers (indicates the gimbal streams IMU/angle data to the PC tool over the upgrade UART; protocol NOT documented in the manual).
- Firmware/tool: "download the GimBalSetting.exe software from the official website: www.caddxfpv.com" and "Select the CADDX_GimBal_v2.0.bin firmware file".
- Specifications table: "Model GM3 V2-20 / Camera Compatibility Avatar/Ascent Series 19/20mm Camera / Stabilization Accuracy ±0.005° / Maximum Controllable Speed ±1500°/s / Controllable Rotation Range Yaw: ±160° Pitch: ±120° Roll: ±60° / Control Method Uart/ S.bus/ Crsf/ Mavlink/ PWM / Head Tracking Control Supports / Static Power 1.6W / Stall Power 18W / Dimensions 61.5x47x46mm / Weight 48g"
- No payload rating appears anywhere in the manual.
- No documented serial protocol and no statement about reporting angles back appears in the manual.

---------------------------------------------------------------------------------------------------
## 2. Oscar Liang, "CaddxFPV GM1, GM2, GM3 Camera Gimbals" review  [V]
- URL: https://oscarliang.com/caddxfpv-camera-gimbals
- Local: `Oscarliang_caddx_gimbals.html` (+ `.txt` stripped)
Quotes (section "Specifications"):
- "GM1: Camera Compatibility: 19mm FPV Camera Image Stabilization: ±0.005° Max Controllable Speed: ±1500°/s Max Controlled Rotational Range: Pitch ±120° Size: 32.2×38.1×20.5mm Weight: 16g Control Mode: PWM / UART Head Tracking Control: Supported Voltage: 7~26V Static Power Dissipation: 1.0W"
- "GM2: ... Max Controlled Rotational Range: Pitch ±120°, Roll ±60° Size: 46.7×46.5×26.2mm Weight: 30g Control Mode: PWM / UART ..."
- "GM3: ... Max Controlled Rotational Range: Pitch ±120°, Roll ±60°, Yaw ±160° Size: 50×46.5x53mm Weight: 46g Control Mode: PWM / UART Head Tracking Control: Supported Voltage: 7~26V Static Power Dissipation: 1.5W"
- Compatibility: "these gimbals cannot be used with the V1 VTX, Mini 1S, Nano V3, or the GT VTX. However they are compatible with the V2 VTX, V2 VTX Dual, and Moonlight VTX."
- GM1 = 1 axis (pitch), GM2 = 2 axis (pitch+roll), GM3 = 3 axis: inferred from the listed ranges above (GM1 only pitch, GM2 pitch+roll, GM3 +yaw).

---------------------------------------------------------------------------------------------------
## 3. ArduPilot wiki: CADDX / XFRobot C-20T Gimbals  [V]
- URL: https://ardupilot.org/rover/docs/common-caddx-gimbal.html
- Local: `ArduPilot_CADDX_gimbals.html` (+ `.txt`)
Quotes:
- "CADDX GM1, GM2, GM3 and XFRobot C-20T gimbals are small 1, 2 and 3-axis gimbals weighing between 16g and 46g and can be paired with 19mm x 19mm FPV cameras."
- "Support for these gimbals is available in ArduPilot 4.6 (and higher) and requires the gimbal's firmware be 3.4 (or higher)"
- "SERIAL2_BAUD to "115" for 115200 bps  MNT1_TYPE to "13" ("CADDX") ... MNT1_PITCH_MIN to -90 MNT1_PITCH_MAX to 90 MNT1_YAW_MIN to -170 MNT1_YAW_MAX to 170"
- "RC9_OPTION = 185 ("Mount RP Lock") to switch between three modes of earth frame/body frame locks ... LOW BF BF FPV lock: pitch/roll RC sets locked angle with respect to mount ... HIGH EF EF Horizon lock" (BF = body frame, EF = earth frame): i.e. body-frame (FPV) command exists.
- "setting MNT1_OPTIONS bit 2 (value +4) can be used to for force FPV lock"
- "Ensure the channel drop-downs highlighted in orange above are set to CH01 and then push the "Save Param To Flash" button."
- Config tool: "Download the GimbalConfig windows application and latest gimbal firmware from the CADDXFPV Download Center"; upgrade cable: "Any FTDI to serial adapter connected to a 3 pin .1mm SH cable can also be used."

## 3b. ArduPilot source: AP_Mount_CADDX.cpp / .h  [V]  (open-source Caddx serial driver)
- URL: https://raw.githubusercontent.com/ArduPilot/ardupilot/master/libraries/AP_Mount/AP_Mount_CADDX.cpp (+ .h)
- Local: `ArduPilot_AP_Mount_CADDX.cpp.txt`, `ArduPilot_AP_Mount_CADDX.h.txt`
Quotes:
- "// gimbal does not provide attitude so simply return targets" (in `get_attitude_quaternion`, which returns `mnt_target` angles, not measured ones). => as implemented, the open-source driver has NO angle read-back.
- "#define SET_ATTITUDE_HEADER1 0xA5 / #define SET_ATTITUDE_HEADER2 0x5A / #define SET_ATTITUDE_BUF_SIZE 10 / #define AXIS_MIN 0 / #define AXIS_MAX 4096"
- "// calculate roll, pitch, yaw angles in range 0 to 4096" (12-bit angle over 360 deg, i.e. ~0.088 deg/step)
- "// byte 2's lower 3 bits are mode // lower 5 bits are sensitivity but always left as zero  uint8_t mode = 0; //start with axes in bf"
- "const uint16_t crc16 = crc16_ccitt(set_attitude_cmd_buf, sizeof(set_attitude_cmd_buf) - 2, 0);"
- The driver only writes (`_uart->write`), never reads, a reply. The command is an ABSOLUTE attitude (angle), not a rate.

## 3c. INAV source: gimbal_serial.h  [V]
- URL: https://raw.githubusercontent.com/iNavFlight/inav/master/src/main/io/gimbal_serial.h
- Local: `INAV_gimbal_serial.h.txt`, `INAV_gimbal_serial.c.txt`
Quotes:
- "uint8_t sync[2]; //data synchronization 0xA5, 0x5A / uint8_t mode:3; //Gimbal Mode [0~7] [Only 0 1 2 modes are supported for the time being] / int16_t sensibility:5; // Stabilization sensibility [-16~15] / int32_t roll:12; //Roll angle [-2048~2047] => [-180~180] / int32_t tilt:12; //Pich angle [-2048~2047] => [-180~180] / int32_t pan:12; //Yaw angle [-2048~2047] => [-180~180] / uint8_t crch; uint8_t crcl;"
- The .c file contains one `serialWriteBuf(gimbalPort, (uint8_t *)&attitude, sizeof(gimbalHtkAttitudePkt_t));` and no reply parser for gimbal angles (only a head-tracker receive path).

## 3d. ArduPilot forum threads  [V]
- "[APPROVED] HeadTracker Serial Driver for CADDX 3 axis gimbal" https://discuss.ardupilot.org/t/approved-headtracker-serial-driver-for-caddx-3-axis-gimbal/121196  -> `ArduPilot_forum_headtracker_serial_driver_caddx.json`
  - post 11 (rmackay9, 2024-12-20): "I've received the packet format from Caddx and I'm pretty confident that I'm sending what the gimbal wants but it never responds. I think the gimbal needs to be running version 3.4"
  - post 16 (rmackay9, 2024-12-21): "angle reporting doesn't work. I think the gimbal provides feedback but I'm not sure yet"
  - post 8 (hwurzburg): "the driver uses iNavs gimbal driver's packet format and CRC"
- "Caddx GM3 does not work with firmware > 3.4" https://discuss.ardupilot.org/t/caddx-gm3-does-not-work-with-firmware-3-4/137918 -> `ArduPilot_forum_caddx_gm3_fw34.json`
  - post 12 (Adam_Borowski): "setting CH01 fixes this issue. I can again control gimbal over uart."
- "Gimbals Caddx/XF mode control" https://discuss.ardupilot.org/t/gimbals-caddx-xf-mode-control/139824 -> `ArduPilot_forum_caddx_xf_mode_control.json`
  - post 8 quotes GitHub issue: "CADDX GM3 Gimbal does not follow the 3 axis lock mode ... the gimbal view is always self levelled" (feature to command FPV/body-frame being added via PR #31461, post 9).
  - post 1: "The new configurator and firmware version for these gimbals though needs a mode set for each of the options on the mode chan" (modes are configured in the Caddx tool; behaviour with UART is fiddly).

## 3e. Paparazzi module gimbal_caddx_gm3  [V, trivial]
- URL: https://paparazzi-uav.readthedocs.io/en/latest/modules/gimbal_caddx_gm3.html -> `Paparazzi_gimbal_caddx_gm3.html`
- "Caddx gm3 gimbal control. Can be used with actuators SBUS (1 wire) or PWM (multiple wires)." (output only)

---------------------------------------------------------------------------------------------------
## 4. XFRobot C-20T (Caddx-compatible, same UART protocol)  [V for specs via Rotorama; protocol via ArduPilot]
- Rotorama (CZ, non-Polish): https://www.rotorama.com/product/xf-c-20t-3-axis-analog -> `Rotorama_XF_C-20T_analog.html`
  - "Range: Pitch -105° to +145°, Roll ±60°, Yaw ±160°  Maximum steering speed: 1500°/s  Maximum camera weight: 20 g (up to 19 mm wide, analog FPV cameras)"
  - "Weight: 49g ... Control: Headtracker XF, S.BUS, CRSF, PWM"
  - Price as shown 2026-11-11: "In Stock € 121,99"
- ArduPilot XFRobot page: https://ardupilot.org/rover/docs/common-xfrobot-gimbal.html -> `ArduPilot_XFRobot_gimbals.html`: "MNT1_TYPE to "14" ("XFRobot") for most gimbals, "13" ("CADDX") for the C-20T" (so C-20T uses the Caddx protocol).

---------------------------------------------------------------------------------------------------
## 5. SIYI Gimbal Camera External SDK Protocol Document (update log V0.1.1, 2025-02-26)  [V]
- URL: https://siyi.biz/siyi_file/A8 mini/SIYI_Gimbal_Camera_External_SDK_Protocol_Update_Log V0.1.1.pdf (siyi.biz now serves an HTML app for this path; the PDF was obtained via the Wayback Machine copy)
- Local: `SIYI_SDK_protocol_wayback.pdf` (110 pp)
Quotes:
- p3: "0x6655: starting mark. Low byte in the front"; CRC16 trailer; fields STX, CTRL, Data_len, SEQ, CMD_ID, DATA, CRC16.
- p51: "1. TTL Serial Port  Baud Rate: 115200  Data Bits: 8 bits  Stop Bits: 1 bit  Parity: None"
- p12 (0x0D Request Gimbal Attitude Data): ACK = "int16_t yaw / int16_t pitch / int16_t roll / int16_t yaw_velocity / int16_t pitch_velocity / int16_t roll_velocity". Notes: "The actual angle values are obtained by dividing the received data by 10, with a precision of one decimal place. It is recommended to use command 0x25 to set the data transmission frequency, allowing attitude data to be sent continuously at a specified interval. The rotation sequence follows Yaw axis -> Roll axis -> Pitch axis, and the coordinate system follows the NED (North-East-Down) convention. The yaw angle is derived from a magnetic encoder."
- p13 (0x0E Set Gimbal Attitude Angles): send "int16_t yaw Target yaw angle / int16_t pitch Target pitch angle"; ACK "Current yaw angle / Current pitch angle / Current roll angle". "yaw: A2 mini: Fixed, non-rotatable  A8 mini: -135.0° to 135.0°  ZR10: Same as A8 mini  ZR30: -270.0° to 270.0°  ZT30: Unlimited  pitch: A2 mini: -90.0° to 25.0°  A8 mini: -90.0° to 25.0°". "The control angle precision is one decimal place. For example, if specifying a yaw of 60.5°, the yaw field should be set to 605."
- p9 (0x07 Gimbal Rotation): "-100 ~ 0 ~ 100: Negative/positive values indicate direction ... rotation speed" (rate control, int8 turn_yaw / turn_pitch).
- p10 (0x19 Request Current Gimbal Mode): "0: Lock mode  1: Follow mode  2: FPV mode (First Person View)"
- 0x25 Request Gimbal to Send Data Stream: data_type "1: Attitude Data ... 3: Magnetic Encoder Angle Data ... 4: Motor Voltage Data", frequencies "2Hz ... 50Hz".

## 5b. SIYI A8 mini User Manual v1.6 (March 2024)  [V]
- URL: https://siyi.biz/siyi_file/A8 mini/A8 mini User Manual v1.6.pdf (Wayback copy)
- Local: `SIYI_A8mini_User_Manual_v1.6.pdf` (161 pp), also `SIYI_A8mini_User_Manual_v1.5.pdf` (107 pp, not quoted)
Quotes (p8 spec table):
- "Weight 95 g"; "Dimension 55 x 55 x 70 mm"; "Working Voltage 11 ~ 25.2 V (3S to 6S)"; "Power Consumption Average 5 W Summit 12 W"
- "Controllable Pitch Angle -135° ~ +45°  Controllable Yaw Angle -160° ~ +160°  Rotatable Roll Angle -30° ~ +30°"
- "Control Signal Input Port UART  Ethernet UDP / TCP"; output "S.Bus"
- Safety page: "it is forbidden to disassemble the gimbal or to change its mechanical structure. And don't add more payload to the gimbal other than its own camera."
- Spec page cross-check (WebFetch of https://siyi.biz/en/product/tri-axis-single-camera-gimbal/a8-mini/spec/): "95 g", "-135° ~ +45°", "-160° ~ +160°".
- ArduPilot Siyi page (`ArduPilot_Siyi.html`): "The Siyi A2 is not supported"; "MNT1_PITCH_MIN to -90 MNT1_PITCH_MAX to 25 MNT1_YAW_MIN to -135 MNT1_YAW_MAX to 135".
- Open-source SDK: https://github.com/mzahana/siyi_sdk (README saved as `mzahana_siyi_sdk_README.md`; not analysed further).

---------------------------------------------------------------------------------------------------
## 6. BaseCam SimpleBGC32 Serial API protocol specification (last updated Nov 5 2026)  [V]
- URL: https://www.basecamelectronics.com/files/SimpleBGC_2_6_Serial_Protocol_Specification.pdf
- Local: `SimpleBGC_2_6_Serial_Protocol.pdf` (193 pp)
Quotes:
- p1: "Board can work on different serial baud rates, adjustable by the parameters, with the 115200 as default value."
- p5/p47 CMD_GET_ANGLES (#73) "Information about actual gimbal control state": "IMU_ANGLE 2s IMU angles in 14-bit resolution per full turn Units: 0,02197265625 degree / TARGET_ANGLE 2s Target angles ..."
- p48 CMD_GET_ANGLES_EXT (#61): "FRAME_CAM_ANGLE 4s Relative angle of joints between two arms of gimbal structure, measured by encoder or 2nd IMU. Value 0 corresponds to normal position of a gimbal. This angle does not overflow after multiple turns. Units: 0,02197265625 degree"
- p65 CMD_CONTROL (#67): "MODE_ANGLE=2 ... Gimbal travels to the given Euler angle with the automatically calculated speed ... MODE_ANGLE: gimbal travels to the new absolute setpoint angle, making multiple turns if needed, but limiting a rotation by ±720° per command"; "MODE_ANGLE_SHORTEST=8 ... shortest path, taking into account the software limits of encoders"; "MODE_SPEED=1 ... Gimbal travels with the given speed"; "MODE_ANGLE_REL_FRAME=5 First, the neutral point of a camera relative to a frame is found in the Euler coordinates for a given axis. Than, the given angle (in ±360° range) is added to this point".
- p67: "The optimal rate of sending this command is 50..125 Hz."
- Also p1: "The controller parses incoming command queue each 8ms".
- Note: the IMU angle is Euler (inertial), only FRAME_CAM_ANGLE is the encoder-measured joint angle ("measured by encoder or 2nd IMU"). For a pan/tilt that must report true motor angles use the encoder variant.

## 6b. ArduPilot wiki pages for other controllers  [V]
- SimpleBGC: https://ardupilot.org/copter/docs/common-simplebgc-gimbal.html -> `ArduPilot_SimpleBGC.html`: "For 3-axis gimbals with 360 degrees of yaw set MNT1_YAW_MIN, MNT1_YAW_MAX to -180 and 180 respectively"; "The SimpleBGC controller and accompanying 2-axis and 3-axis gimbals can be purchased from basecamelectronics.com and many other retailers."
- STorM32: `ArduPilot_Storm32.html`: "The STorM32-BGC is a relatively low-cost 3-axis brushless gimbal controller ... MAVLink or a proprietary serial protocol." Driver source `ArduPilot_Mount_SimpleBGC_cpp.txt` (actually AP_Mount_SToRM32_serial.cpp) builds the attitude from `_current_angle` (it parses replies) - not independently verified against the STorM32 spec (spec not retrieved).
- Gremsy: `ArduPilot_Gremsy.html`: "MIO gimbals are unable to communication with ArduPilot."
- ViewPro: `ArduPilot_ViewPro.html`: custom serial protocol, "MNT1_TYPE = 11 (Viewpro)". No angle-feedback statement found.

---------------------------------------------------------------------------------------------------
## 7. Gremsy Mio specification  [V]
- URL: https://docs.gremsy.com/gimbals/mio/getting-started/specification -> `Gremsy_Mio_spec.html`
- "Mio's Weight 0.53 lbs / 240 g ... Maximum Payload 0.88 lbs / 400 g  Input Voltage Gimbal 12V / 5A ... Gremsy Specialized Gimbal Drive Motors with Encoders ... Supported Connections USB 2.0, CAN, UART, S-bus, PPM, Bluetooth 4.0."
- Price: A$3,399 / US$1,199 (two-axis) from search snippet only [S].

## 8. DJI Osmo Mobile BLE reverse engineering  [V for README only]
- URL: https://github.com/alkersan/om-research -> `om-research_README.md`
- "This repository explores the Bluetooth Low Energy (BLE) protocol used by the Osmo Mobile series of gimbals." "Tested on: OM2, OM3, OM4." Scripts: `duml.py`, `gimbal.py`, `rotate.py` ("issues several roration commands"). README says nothing about reading angles back. Pan range and payload of the phone gimbals not checked.

---------------------------------------------------------------------------------------------------
## 9. Prices in Poland (PLN gross) and other shops, seen 2026-11-11
| Item | Shop | URL | Price | Stock as shown | Evidence |
|---|---|---|---|---|---|
| Caddx GM3 (V1, 3-axis) | megadron.pl (PL) | https://megadron.pl/pl/products/-31485.html | "Cena brutto: 679,00 zł" (netto 552,03 zł) | "Dostępny"; JSON-LD InStock | [V] |
| Caddx GM3 V2-20 | ht-dron.pl (PL) | https://www.ht-dron.pl/CaddxFPV-GM3-V2-20-3-FPV-Walksnail-Avatar--p10360/s_lang/en | JSON-LD "price": "695.00" (PLN, shop currency PLN) | OutOfStock | [V] (page source JSON-LD; gross/net not stated) |
| SIYI A8 mini | ht-dron.pl (PL) | https://www.ht-dron.pl/SIYI-A8-mini-4K-Mini-Zoom-Gimbal-HD-6x-p6013/pa/3 | JSON-LD "price": "1425.00" | OutOfStock | [V] (same caveat) |
| Caddx GM2 (2-axis) | rotorama.com (CZ, non-Polish) | https://www.rotorama.com/product/gm2 | € 77,99 | In Stock | [V] |
| Caddx GM3 V2 | rotorama.com (CZ) | https://www.rotorama.com/product/gm3-2 | € 140,59 | In Stock | [V] |
| Caddx GM3 (V1) | rotorama.com (CZ) | https://www.rotorama.com/product/gm3 | € 144,39 | Discontinued | [V] |
| XF C-20T analog | rotorama.com (CZ) | https://www.rotorama.com/product/xf-c-20t-3-axis-analog | € 121,99 | In Stock | [V] |
| Caddx GM3 V2-20 | hobbydrone.cz (CZ) | https://www.hobbydrone.cz/en/fpv-gimbal-caddxfpv-gm3-v2-20/ | 137,80 EUR (113,90 excl. VAT) | "sold out" | [V] |
| SIYI A8 mini | bzbuas.com (shop country unverified) | https://bzbuas.com/en/shop/233835678-siyi-a8-mini-523 | 1 104,87 zł excl. VAT (search snippet) | n/a | [S] |
| Caddx GM2 | bzbuas.com | https://www.bzbuas.com/shop/c0ca-gm200-caddx-gm2-dual-axis-gimbal-3216 | 291,87 zł excl. VAT, "Contact to order" (snippet) | n/a | [S] |
| SimpleBGC 32-bit Extended | basecamelectronics.com / iFlight EU / UpgradeRC | https://shop.basecamelectronics.com/ | 2-IMU set about EUR 289-313; GM2804 combo EUR 344,90 (iFlight EU, snippet; encoder AS5048A per snippet) | n/a | [S] (iflight page returned HTTP 429, not opened) |
| DJI Osmo Mobile 3 Combo | rcpro.pl | https://rcpro.pl/product-pol-16374-Gimbal-Reczny-DJI-Osmo-Mobile-3-Combo.html | 599 PLN (snippet) | n/a | [S] (rcpro.pl returns HTTP 403 to curl) |
Polish shops tried but not usable: rcpro.pl (403), fpvracing.pl, dronelab.pl, gimmik.pl (connection failed / no result), abc-rc.pl, dronestore.pl (domain parked), botland.com.pl search (no FPV micro-gimbal found, only unrelated handheld/mechanical items). kamami.pl / tme.eu not queried (known 403): any value from them would be "snippet only".

---------------------------------------------------------------------------------------------------
## 10. NOT RETRIEVED / unverified (please fetch if needed)
1. Caddx official GM1/GM2/GM3 user manuals and product pages: caddxfpv.com returned HTTP 429 for every request, and manuals.plus returned 403. The V1 GM3 / GM2 / GM1 specs above come from Oscar Liang's review and the V2-20 quick start only. Ask Adam to drop in: https://www.caddxfpv.com/products/caddxfpv-gm1-gm2-gm3 and the "GM Gimbal" manual PDF, plus the "Firmware / GM Gimbal Firmware" download (GimbalConfig + `.cahf` release notes) from the Caddx Download Center.
2. Caddx serial protocol spec: rmackay9 says Caddx supplied "the packet format" privately; it is not public. Only the command packet (INAV/ArduPilot source) is verified. Whether the gimbal sends angle packets back on its UART is UNVERIFIED (ArduPilot dev: "I think the gimbal provides feedback but I'm not sure yet"; GimbalSetting shows EULER/ANGL live values to a PC over the upgrade port, so some telemetry exists). Needs a logic-analyser capture or a request to support@caddxfpv.com.
3. No newer Caddx/Walksnail gimbal (2025-2026) found: a search found only "GM030 (upgraded from GM2/GM3)" as a Banggood listing, which is the GM3 V2 part number (C0CA-GM030); no GM4 / successor found. Not conclusive.
4. Caddx teardown / spare motors / driver IC / encoder IC: nothing found (only a coax cable replacement guide, not opened). No evidence of motors sold as spares.
5. Walksnail / RunCam / Hawkeye / Foxeer / BetaFPV micro gimbals: searches found nothing; not researched further.
6. ViewPro mini gimbals: no angle-feedback statement and no Z-1 mini weight/price found; XF Robot Z-1 mini datasheet not opened.
7. STorM32 serial protocol spec, SimpleBGC GUI manual, Basecam shop pages: not downloaded (only the Serial API PDF). iFlight GM2804 combo page: HTTP 429. Motor / encoder claims there are [S].
8. Phone gimbals (DJI Osmo Mobile, Zhiyun Smooth, Feiyu): only the om-research README read; angle read-back, pan range, payload, and protocol of Zhiyun/Feiyu not researched. DJI RS2 etc. not researched.
9. Gremsy Mio price and the Gremsy serial/MAVLink docs: price is [S]; protocol not read.
10. Pan range of GM3 (yaw ±160 deg) is as stated by Caddx's table; no source says it can rotate continuously.
