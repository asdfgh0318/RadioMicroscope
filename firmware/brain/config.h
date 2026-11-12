// RadioMicroscope v2 - brain build settings (Seeed XIAO ESP32-S3 Sense).
#pragma once

// Wi-Fi access point that serves the control page at http://192.168.4.1
#define AP_SSID "RadioMicroscope"
#define AP_PASSWORD "radiomicroscope"  // at least 8 characters; change it
// The control network transmits a few centimetres from the measuring
// antenna. Keep it at least five channels away from a 2.4 GHz target
// (1, 6 or 11); it does not disturb 5 GHz targets.
#define AP_CHANNEL 11

// --- Drivetrain --------------------------------------------------------
// 1 = brushless gimbal motors behind the motor controller (firmware/motion)
// 0 = two Waveshare ST3215 serial bus servos on a bus servo adapter
#define DRIVE_BRUSHLESS 1
// 1 = no motors at all: the antenna is fixed to a vehicle that does the
// turning (airborne use). Overrides DRIVE_BRUSHLESS. The antenna then looks
// ANT_AZ degrees right of the nose and ANT_EL degrees above the deck.
#define DRIVE_FIXED 0
#define ANT_AZ 0.0f
#define ANT_EL -30.0f

// --- Sensor ------------------------------------------------------------
// 0 = Seeed XIAO ESP32-C5 sensor radio on the serial link (Wi-Fi, 2.4 + 5 GHz)
// 1 = RX5808 analog video receiver wired to this board (5.8 GHz FPV video)
#define SENSOR_RX5808 0

// 1 = Seeed XIAO ESP32-C5 running the ESP-SDR firmware, on the same two
// wires as the Wi-Fi sensor: measures the power of any signal on a chosen
// frequency (analog video included). Gives signal strength only, no
// picture and no list of Wi-Fi networks.
#define SENSOR_ESPSDR 0
#if SENSOR_ESPSDR && SENSOR_RX5808
#error "choose one of SENSOR_ESPSDR and SENSOR_RX5808"
#endif
// Band for ESP-SDR: 58 = the 48 analog video channels on 5.8 GHz,
// 24 = the 13 Wi-Fi channel centres on 2.4 GHz.
#define ESPSDR_BAND 58
// Receiver gain index for ESP-SDR; -1 picks the middle of the chip's range.
// Lower it if a nearby transmitter reads the same at every angle.
#define ESPSDR_GAIN -1
// Burst power with no signal, in the chip's own decibels. A survey with the
// transmitter off measures and stores the real value; this is only the
// starting guess.
#define ESPSDR_FLOOR_DB 10.0f

// RX5808 pins (used only with SENSOR_RX5808 1). RSSI and select take the
// place of the sensor link. Clock and data use the drivetrain pins when
// there are no motors, otherwise the microSD card pins.
#define RX5808_RSSI_PIN D2   // module RSSI output; must be an ADC pin
#define RX5808_CS_PIN D3     // module CH2 pad after the SPI mod
#if DRIVE_FIXED
#define RX5808_CLK_PIN D0    // module CH3 pad
#define RX5808_DATA_PIN D1   // module CH1 pad
#else
#define RX5808_CLK_PIN D8
#define RX5808_DATA_PIN D9
#endif
// RSSI pin voltage with no transmitter, and with one a metre away. Measure
// both on your module: no two modules read the same.
#define RX5808_RSSI_MIN_MV 500
#define RX5808_RSSI_MAX_MV 1100

// --- Pins --------------------------------------------------------------
#define DRIVE_TX_PIN D0  // to the motor controller RX (pin 16) or the servo adapter RX
#define DRIVE_RX_PIN D1  // from the motor controller TX (pin 17) or the servo adapter TX
#define LINK_RX_PIN D2   // from sensor D6 (TX)
#define LINK_TX_PIN D3   // to sensor D7 (RX)
// D4 / D5: I2C, reserved for a compass or power monitor
#define GPS_RX_PIN D7    // from the GPS module TX (optional)
// D8..D10 carry the microSD card of the Sense expansion board.

// --- Bus servos (DRIVE_BRUSHLESS 0 only) -------------------------------
#define SERVO_BAUD 1000000
#define PAN_ID 1
#define TILT_ID 2

// Speed in encoder steps per second (4096 per turn) and acceleration in
// units of 100 steps/s^2.
#define SERVO_SPEED 1500
#define SERVO_ACC 40

// --- Mechanical travel, degrees ----------------------------------------
// Pan 0 = straight ahead, tilt 0 = horizon. Without a slip ring the pan
// axis stops short of a full turn so the cable loop is not wound up.
// With the brushless drivetrain keep these equal to the limits in
// firmware/motion/config.h; PAN_DIR and TILT_DIR are then set there.
#define PAN_MIN -175.0f
#define PAN_MAX 175.0f
#define PAN_DIR 1    // -1 if the head turns the wrong way
#define TILT_MIN -15.0f
#define TILT_MAX 95.0f
#define TILT_DIR 1   // -1 if the head tilts the wrong way

// --- Navigation sensors --------------------------------------------------
// 1 = MPU-6050 IMU and a compass (HMC5883L or QMC5883L) on the I2C pins
// D4 (SDA) and D5 (SCL). Gives true headings on the ground and makes the
// turn scan and bearing logging possible.
#define NAV_SENSORS 0
// 1 = the sensor board turns with the pan axis (as when it rides on the
// yoke), so the compass heading already includes the pan angle.
// 0 = it is fixed to the base or the vehicle.
#define NAV_TURNS_WITH_PAN 1
// 1 = keep the antenna facing the same way in the world while the base is
// turned, as when the head is carried in the hand. Needs the sensors fixed
// to the base or grip (NAV_TURNS_WITH_PAN 0).
#define HOLD_WORLD 0
// Local magnetic declination in degrees, east positive (look it up for
// your location); added to the compass heading to give true north.
#define MAG_DECLINATION 0.0f
// How the compass chip sits relative to the IMU: degrees its X arrow is
// turned clockwise (seen from above) from the IMU's X arrow, and whether
// its Y arrow points right instead of left. Check after wiring: turning
// the unit clockwise must make the heading rise; if it falls, set
// MAG_FLIP_Y to 1.
#define MAG_MOUNT_YAW 0.0f
#define MAG_FLIP_Y 0

// --- Logging ---------------------------------------------------------------
// 1 = write every reading to the microSD card of the Sense board.
#define LOG_SD 0
#if LOG_SD && SENSOR_RX5808 && !DRIVE_FIXED
#error "LOG_SD and the RX5808 both need pins D8 and D9: move RX5808_CLK_PIN and RX5808_DATA_PIN"
#endif

// --- Options -----------------------------------------------------------
#define RM_CAMERA 1        // boresight camera of the XIAO ESP32-S3 Sense
#define GPS_BAUD 9600
