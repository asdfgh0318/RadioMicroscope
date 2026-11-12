# EXTRACTS - brushless gimbal motors for a 2-axis antenna head (fetched 2026-11-11)

Tags: [V] = read on a page that was actually fetched and saved here; [S] = search snippet / listing-card only.
All files are untrusted web content converted to text; none executed.

## A. Maker datasheet pages (all [V])

### iFlight shop, GM2804 with AS5048A encoder - ifl_gm2804_enc.txt
URL: https://shop.iflight.com/ipower-gm2804-gimbal-motor-with-as5048a-encoder-pro288
- "Configuration: 12N/14P" / "Motor Height: 25±0.2mm (Included with Encoder housing)"
- "Hollow Shaft(OD): Ф8-0.008/-0.012 mm" / "Hollow Shaft(ID): Ф6.5+0.05/0 mm"
- "Motor Weight: 51±0.2g" / "Load torque(g·cm): 250-350" / "Motor internal resistance: 9Ω±5%"
- "Load current: 0.8 A" "Load volts: 10 V" / "Maximum power: ≤25W" / "Working current: 2-3S" / price on page "$38.99" (USD)
### iFlight shop, GM2804 without encoder - ifl_gm2804_plain.txt
URL: https://shop.iflight.com/ipower-gm2804-gimbal-motor-pro1153
- "Motor Height: 15±0.2mm", "Motor Weight: 42.3±0.2g", "Load torque(g·cm): 250-350", price "$21.99"
### iFlight shop, GM3506 with AS5048A - ifl_gm3506_enc.txt
URL: https://shop.iflight.com/ipower-motor-gm3506-brushless-gimbal-motor-w-as5048a-encoder-pro1155
- "Configuration: 24N/22P"; "Hollow Shaft(OD): Ф12..." ; "Hollow Shaft(ID): Ф8.6+0.05/0 mm"; "Motor Weight: 72±0.2g"
- "Load torque(g·cm): 600-1000"; "Motor internal resistance: 5.6Ω±5%"; "Load current: 1A" at "No-load volts: 16V"; price "$41.90"
### iFlight shop, GM4108H-120T with AS5048A - ifl_gm4108h_enc.txt
URL: https://shop.iflight.com/ipower-motor-gm4108h-120t-gimbal-motor-with-as5048a-encoder-pro243
- "Motor Out Diameter: Ф47±0.05mm" "Configuration: 24N/22P" "Motor Height: 32.3±0.2mm (Included with Encoder housing)"
- "Hollow Shaft(OD): Ф10-0.008/-0.012mm" "Hollow Shaft(ID): 8+0.05/0mm" "Motor Weight: 137±0.5g"
- "Load current: 1.5A" "Load volts: 20V" "Load torque(g·cm): 1200-1800" "Motor internal resistance: 11.1Ω±5%"
- "Maximum power: ≤25W" "Working current: 3-5S"; price "$54.99"
### iFlight shop, GM5208-12 with AS5048A - ifl_gm5208_12_enc.txt
URL: https://shop.iflight.com/ipower-motor-gm5208-12-brushless-gimbal-motor-with-as5048a-encoder-pro248
- "2.5KG/cm Torque" (marketing line); "Configuration: 12N/14P"; "Hollow Shaft(ID): Ф12+0.05/0 mm"; "Motor Weight: 209±0.5g"
- "Load torque(g·cm): 1800-2500"; "Motor internal resistance: 15.2Ω±5%"; "Load current: 1A" "Load volts: 20V"; price "$61.99"
### T-Motor store, GB2208 KV128 - tmotor_goods447_gb2208.txt
URL: https://store.tmotor.com/goods-447-GB2208.html
- "Motor Weight(Incl. Cable) 39.5g" "Hole Size 6mm" "Configuration 12N14P" "Internal Resistance 14.4Ω" "Motor's Torsion（Nm） 0.07" "Rated Voltage (Lipo) 3-4S"
- "GB2208 Gimbal Type 3-4S UAV Drone Motor KV128 ... $25.90"; "for GoPro-class cameras (100-300g)"
Note: iFlight "Load torque" is a g·cm figure measured at the listed load current/voltage; the page does not define the test further.
1 g·cm = 9.807e-5 N·m, so 250-350 -> 0.025-0.034; 600-1000 -> 0.059-0.098; 1200-1800 -> 0.118-0.177; 1800-2500 -> 0.176-0.245 N·m.

## A2. AliExpress (pl.aliexpress.com search pages) - ALL [S]
File: ae_search_snippets_2026-11-11.txt (parsed from the public search-result JSON), raw pages *.html.gz.
- Product pages (pl.aliexpress.com/item/<id>.html) return only an empty JS shell via plain HTTP; m.aliexpress.com search returned 404; after ~28 requests the search endpoint returned a "punish"/captcha page (saved nothing, not bypassed).
- Cards give title, price in PLN, "Darmowa dostawa" (free shipping) tag, sold count. They give NO store name, NO delivery ETA, NO ship-from (the shipFrom field is "CN" on every card), NO phase resistance. Card data has "taxRate":"0.230000" (23%) - whether the shown price already contains VAT is not stated on the card.
- Example verbatim card titles: "IFlight IPower GM4108H-120T 4108 Silnik Gimbala z Enkoderem AS5048A, Φ47mm 24N22P 137g Pusty Wałek..." 219,19 zł (id 1005012808408644); "IPower GM5208-24 – ... 0,39 Nm, 5208, 24N28P, 160 g, enkoder AS5048A..." 181,19 zł (id 1005012986899633); "T-MOTOR GB2208 128KV Silnik Gimbalowy 0.07Nm 12N14P 39.5g 6mm Pusty Wał..." 110,19 zł; "Silnik gimbala IFlight GM2804, moment obrotowy 250g·cm, enkoder AS5048A..." 70,99 zł.
- VAT/IOSS: the AliExpress help page "European Union VAT" (service.aliexpress.com/page/knowledge?...knowledge=1060863305) is a JS app and did NOT render (5 kB shell). The statement "collects VAT at checkout on orders of EUR 150 or less shipped from outside the EU ... AliExpress IOSS number" is therefore only a search-result summary [S], not read at source. The EC IOSS page URLs I tried returned 404.

## B. Documented builds (all [V], saved as text)
1. SimpleFOC forum #3811 (sfoc_forum_3811.txt) https://community.simplefoc.com/t/3811 - frippe75, ESP32 pan/tilt for a 250 g camera.
 "Building a smaller pan/tilt rig for a 250gr SonyHX90 using a 2 BLDC motor gimbal setup." "Running SimpleFoc library 2.3.0 on ESP32 with the SimpleFocMini driver, AS5600 via I2C and a cheap smaller china gimbal motor." "MOT: PP check: fail - estimated pp: 12.34" "Goal is to do a 2-axis pan/tilt head for a DSLR @ 3kg roughly." runger: "just that you were unlucky with the motors you picked". Anthony_Douglas: "14 pole pairs is a lot for a motor of this size."  (his config declared 12N14P with BLDCMotor(7)).
2. SimpleFOC #4631 (sfoc_forum_4631.txt) - Mike_Braun: "Im using one iPower Motor GM3506 with AS5048 encoder on a Arduino Nano ESP32 and SimpleFOC Mini. With one 12V power supply"; "motor.voltage_limit = 6;" "It will have to move slow, so that the webcam can pickup the image, but I would like to have maximum torque".
3. SimpleFOC #869 (sfoc_forum_869.txt) - Cc1924, 3-axis gimbal, "motor - Arduino, magnetic encoder - AS5600 ... IMU (MPU6050)"; "Method 1: ... angle mode ... the response speed is relatively slow"; runger: "The AS5600 is not the most accurate sensor, you'll probably have to smooth the output".
4. SimpleFOC #6779 (sfoc_forum_6779.txt) - awo: "mini camera gimbal project using two GB1105 motors (6 PP, 12V, 12.5Ω phase to phase) with the DRV8313 motor driver and AS5048A encoders"; runger: "Changing the sensor is where I see most potential gains ... most time is lost to 3x sensor readings."
5. SimpleFOC #5392 (sfoc_forum_5392.txt) - 2-axis 1 kg DSLR pod. runger: "I think balance is very important, otherwise the motor will be continuously 'lifting' the camera to hold it in place - this will make the gimbal use far more power, with accompanying heat generation problems."; "Motor Tuning: unless you use sliprings everywhere, a camera gimbal cannot be rotated freely at 360°, because of the wires. This makes tuning the motors ... under load difficult."
6. SimpleFOC #4252 (sfoc_forum_4252.txt): "The load has to be balanced, so the motors have to work only when moving the camera, and not so much when holding it."; "I use similar sized motors and they can't handle more than about 400 mA of current if they are standing still."; "If it's not moving, it's all waste heat!"
7. SimpleFOC #8306 (sfoc_forum_8306.txt) - GM6208 + AS5048A + SimpleFOC Mini v1.0: "(around 32 Ω phase resistance)" "as the commanded movement becomes very slow, I get increasingly noticeable stop/start or 'cogging/stiction'-like behaviour." dekutree64 suggests angle_nocascade and deadtime compensation.
8. SimpleFOC #6761 (sfoc_forum_6761.txt) cogging: "I don't think it's possible to eliminate cogging in open loop mode, unless you purchase a 'slotless' (ironless windings) motor."
9. SimpleFOC #4330 (sfoc_forum_4330.txt): runger "the ones from eMax or iPower are quite nice"; Owen_Williams: "you'd be paying about $15 for the as5048a, another $1 for the magnet"; "Some start with the very cheap as5600 ($3) but it is much slower/less accurate than as5048a resulting in it being hard to tune PIDs closed loop."
10. ODrive forum #12720 (odrive_forum_12720.txt) - louise 2025: "I have a small project that need to have a hollow shaft motor with slipring ... Later I found out that ODrive is not that suitable for low current high resistance gimbal motor." Motor GM5208-12, "Driver: ODrive S1", "Encoder: AS5048A", "Procedure error NO_RESPONSE".
11. ODrive forum #11315 (odrive_forum_11315.txt): "When setting the target velocity to values below 0.1 turn/s the rotation becomes unstable." solomondg: "this may be due to cogging torque - running anticogging may help."
12. ODrive forum #13734: "I don't think we can support non-ODrive products. However, you could absolutely use the ODrive Micro with CAN wiring!"
13. Hackaday.io Smart Antenna Tracker log (hackaday_2150_log15812.txt) https://hackaday.io/project/2150/log/15812-re-imagined-smart-tracker - plan only (2015): "I plan to use a brushless design much like the go-pro gimbals used for FPV." "Brushless gimbals heavily depend on well balanced systems. So a counter weight is necessary." "Hopefully, I can send power through the slip ring".
14. ArduPilot forum #10048 (ardupilot_storm32_antennatracker_10048.txt) - only a question: "Is it possible to use a brushless gimbal with a STorM32 controller as an AntennaTracker?" no confirmed build.
15. ArduPilot forum #143335 (ardupilot_tracker_143335.txt) - servo-based tracker, not brushless; context only.
16. BaseCam app note (basecam_cable_routing_appnote.pdf/.txt) - slip ring types: "Capsule slip ring; Through hole or through bore slip ring; Pancake or PCB slip rings"; "the motors will require additional power to bend the cable".
17. OlliW, "Brushless Gimbal Direct Drive: Theory and Experiment" (olliw_direct_drive.txt) - theory: "If the torque is too large, the motor will slip, since the sine function is bounded."
18. SimpleFOC #6913 (sfoc_forum_6913.txt) GM6208-150T on MKS Dual FOC + ESP32 + AS5048A SPI (pin wiring thread); #7675, #1985 saved as background.

## Not retrieved
- AliExpress product pages, store names, delivery ETAs, ship-from, 12-wire capsule slip ring, AS5600/AS5048A/MT6701 breakout and 6x2.5 mm magnet search pages (rate-limited / captcha); DJI/Feiyu/RCTimer/DYS/Tarot/Mitoot dedicated searches were blocked (only titles seen inside other searches).
- AliExpress official VAT/IOSS help page (JS-only). iFlight EU shop (iflight-rc.eu) returned HTTP 429. T-Motor GB36-1/2, GB4106, GB54 not searched.
- Reddit threads (r/robotics, r/amateurradio, r/RTLSDR, r/fpv): not reachable by the search tool; no Reddit build cited.
