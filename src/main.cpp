#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include "web_ui.h"

// === Configuration ===
const char* AP_SSID = "RadioMicroscope";
// Pin definitions (use symbolic names for XIAO ESP32S3)
#define SERVO_AZ_PIN D0   // GPIO1 - Azimuth (360-mod continuous rotation)
#define SERVO_EL_PIN D1   // GPIO2 - Elevation (standard 0-180)
// I2C uses default SDA=D4(GPIO5), SCL=D5(GPIO6)

// Timing intervals (ms)
#define IMU_READ_INTERVAL 100
#define WS_PUSH_INTERVAL 200
#define WIFI_SCAN_INTERVAL 5000
#define WATCHDOG_TIMEOUT 2000

// === Global Objects ===
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Servo azimuthServo;
Servo elevationServo;
Adafruit_MPU6050 mpu;
bool mpuReady = false;

// === State ===
float pitch = 0, roll = 0;
int azimuthSpeed = 0;     // -100 to +100
int elevationAngle = 90;  // 0-180
int azimuthTrim = 0;      // ±50 μs

unsigned long lastIMURead = 0;
unsigned long lastWsPush = 0;
unsigned long lastScanTrigger = 0;
unsigned long lastControlMsg = 0;

// Cached scan results
String cachedRssiJson = "[]";

// === Forward Declarations ===
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void setAzimuth(int speedPercent, int trimUs);
void setElevation(int degrees);
void readIMU();
String buildSensorJSON();
void handleScanResults();

// === Setup ===
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("RadioMicroscope booting...");

    // I2C for MPU-6050
    Wire.begin();  // Uses default SDA/SCL on XIAO ESP32S3
    if (mpu.begin()) {
        mpuReady = true;
        mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
        mpu.setGyroRange(MPU6050_RANGE_250_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
        Serial.println("MPU-6050 initialized");
    } else {
        Serial.println("MPU-6050 not found — continuing without IMU");
    }

    // Servos
    azimuthServo.attach(SERVO_AZ_PIN);
    elevationServo.attach(SERVO_EL_PIN);
    azimuthServo.writeMicroseconds(1500);  // stop
    elevationServo.write(90);              // center
    Serial.println("Servos attached");

    // WiFi AP + STA (STA needed for scanning)
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(AP_SSID);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());

    // WebSocket
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    // HTTP: serve web UI
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", WEB_UI_HTML);
    });

    server.begin();
    Serial.println("Web server started");

    // First WiFi scan
    WiFi.scanNetworks(true);
    lastScanTrigger = millis();
}

// === Loop ===
void loop() {
    ws.cleanupClients();
    unsigned long now = millis();

    // Read IMU
    if (mpuReady && now - lastIMURead >= IMU_READ_INTERVAL) {
        lastIMURead = now;
        readIMU();
    }

    // Check WiFi scan completion
    int scanResult = WiFi.scanComplete();
    if (scanResult >= 0) {
        handleScanResults();
        WiFi.scanDelete();
    }

    // Trigger new scan
    if (scanResult == WIFI_SCAN_FAILED && now - lastScanTrigger >= WIFI_SCAN_INTERVAL) {
        WiFi.scanNetworks(true);
        lastScanTrigger = now;
    }

    // Push sensor data via WebSocket
    if (now - lastWsPush >= WS_PUSH_INTERVAL) {
        lastWsPush = now;
        if (ws.count() > 0) {
            String json = buildSensorJSON();
            ws.textAll(json);
        }
    }

    // Safety watchdog: stop azimuth if no control for 2s
    if (azimuthSpeed != 0 && now - lastControlMsg > WATCHDOG_TIMEOUT) {
        azimuthSpeed = 0;
        setAzimuth(0, azimuthTrim);
        Serial.println("Watchdog: azimuth stopped");
    }
}

// === WebSocket Event Handler ===
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.printf("WS client #%u connected\n", client->id());
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.printf("WS client #%u disconnected\n", client->id());
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if (info->opcode == WS_TEXT) {
            // Parse JSON control message
            JsonDocument doc;
            DeserializationError err = deserializeJson(doc, data, len);
            if (err) {
                Serial.printf("JSON parse error: %s\n", err.c_str());
                return;
            }

            const char* type = doc["type"];
            if (type && strcmp(type, "control") == 0) {
                lastControlMsg = millis();

                if (doc["azimuth"].is<int>()) {
                    azimuthSpeed = constrain((int)doc["azimuth"], -100, 100);
                }
                if (doc["elevation"].is<int>()) {
                    elevationAngle = constrain((int)doc["elevation"], 0, 180);
                }
                if (doc["trim"].is<int>()) {
                    azimuthTrim = constrain((int)doc["trim"], -50, 50);
                }

                setAzimuth(azimuthSpeed, azimuthTrim);
                setElevation(elevationAngle);
            }
        }
    }
}

// === Servo Control ===
void setAzimuth(int speedPercent, int trimUs) {
    int center = 1500 + trimUs;
    int pulse;
    if (abs(speedPercent) < 5) {
        pulse = center;  // dead zone — full stop
    } else {
        pulse = center + (speedPercent * 500 / 100);
    }
    pulse = constrain(pulse, 500, 2500);
    azimuthServo.writeMicroseconds(pulse);
}

void setElevation(int degrees) {
    elevationServo.write(constrain(degrees, 0, 180));
}

// === IMU ===
void readIMU() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    pitch = atan2(a.acceleration.y,
                  sqrt(a.acceleration.x * a.acceleration.x +
                       a.acceleration.z * a.acceleration.z)) * 180.0 / PI;
    roll = atan2(-a.acceleration.x, a.acceleration.z) * 180.0 / PI;
}

// === WiFi Scan Results ===
void handleScanResults() {
    int n = WiFi.scanComplete();
    if (n <= 0) {
        cachedRssiJson = "[]";
        return;
    }

    // Sort indices by RSSI (strongest first)
    int indices[n];
    for (int i = 0; i < n; i++) indices[i] = i;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
                int tmp = indices[i];
                indices[i] = indices[j];
                indices[j] = tmp;
            }
        }
    }

    // Build JSON array, cap at 5
    JsonDocument doc;
    JsonArray arr = doc.to<JsonArray>();
    int limit = min(n, 5);
    for (int i = 0; i < limit; i++) {
        JsonObject net = arr.add<JsonObject>();
        net["ssid"] = WiFi.SSID(indices[i]);
        net["rssi"] = WiFi.RSSI(indices[i]);
        net["ch"] = WiFi.channel(indices[i]);
    }

    cachedRssiJson = "";
    serializeJson(doc, cachedRssiJson);
}

// === Build Sensor JSON ===
String buildSensorJSON() {
    JsonDocument doc;
    doc["type"] = "sensors";
    doc["pitch"] = round(pitch * 10.0) / 10.0;
    doc["roll"] = round(roll * 10.0) / 10.0;

    // Parse cached RSSI into the document
    JsonDocument rssiDoc;
    deserializeJson(rssiDoc, cachedRssiJson);
    doc["networks"] = rssiDoc.as<JsonArray>();

    String output;
    serializeJson(doc, output);
    return output;
}
