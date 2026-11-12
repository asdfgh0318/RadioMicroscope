// RadioMicroscope v2 - motor controller build settings.
// Board: any classic ESP32 DevKit (ESP32-WROOM-32), two SimpleFOC Mini
// (DRV8313) drivers, two gimbal motors with AS5048A encoders on SPI.
#pragma once

// --- Motors ------------------------------------------------------------
// Pole pairs = magnet poles / 2. iFlight GM3506 and GM4108H: 22 poles = 11.
// GM2804 and GM5208: 14 poles = 7.
#define PAN_POLE_PAIRS 11
#define TILT_POLE_PAIRS 11

#define SUPPLY_VOLTS 12.0f
// Largest drive voltage for a motor. This sets the peak torque and the
// heat: at standstill the current is roughly volts / winding resistance
// (GM3506: 5.6 ohm, so 5 V is about 0.9 A and 4.5 W). Raise it only if the
// head cannot hold its load, and balance the head first. Must not exceed
// half the supply.
#define PAN_VOLT_LIMIT 5.0f
#define TILT_VOLT_LIMIT 5.0f
// Voltage used for the one-time alignment move ("cal" on the console).
#define ALIGN_VOLTS 3.0f

#define MAX_SPEED_DEG_S 120.0f

// --- Travel, mechanical degrees ----------------------------------------
// Keep these equal to PAN_MIN.. / TILT_MIN.. in firmware/brain/config.h.
#define PAN_MIN -175.0f
#define PAN_MAX 175.0f
#define PAN_DIR 1    // -1 if the head turns the wrong way
#define TILT_MIN -15.0f
#define TILT_MAX 95.0f
#define TILT_DIR 1   // -1 if the head tilts the wrong way

// --- Pins --------------------------------------------------------------
#define PAN_PWM_A 25
#define PAN_PWM_B 26
#define PAN_PWM_C 27
#define PAN_ENABLE 22

#define TILT_PWM_A 32
#define TILT_PWM_B 33
#define TILT_PWM_C 13
#define TILT_ENABLE 4

// Both encoders share the SPI bus (SCK 18, MISO 19, MOSI 23).
#define PAN_ENCODER_CS 5
#define TILT_ENCODER_CS 21

// Link to the brain: brain D0 (TX) -> pin 16, brain D1 (RX) <- pin 17.
#define LINK_RX_PIN 16
#define LINK_TX_PIN 17
