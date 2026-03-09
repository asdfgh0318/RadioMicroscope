#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include "web_ui.h"

void setup() {
    Serial.begin(115200);
    Serial.println("RadioMicroscope booting...");
}

void loop() {
}
