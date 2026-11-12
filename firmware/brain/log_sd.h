// Logging to the microSD card of the XIAO ESP32-S3 Sense. Selected with
// LOG_SD 1 in config.h. Included by brain.ino after its globals.
//
// One CSV file per power-up, /rm_NNN.csv. Two kinds of row:
//   S  one signal-strength reading with position, attitude and direction
//      (position is left empty when the GPS has no current fix)
//   B  one bearing: the strongest direction found by a turn scan
// tools/locate.py reads these files.
#pragma once
#include <SD.h>
#include <SPI.h>

static File g_logFile;
static bool g_logOk = false;
static uint32_t g_logRows = 0;
static char g_logName[16] = "";

static void logBegin() {
    if (!SD.begin(21)) {  // card select pin of the Sense expansion board
        Serial.println("no microSD card: logging off");
        return;
    }
    bool free = false;
    for (int n = 1; n < 1000 && !free; n++) {
        snprintf(g_logName, sizeof(g_logName), "/rm_%03d.csv", n);
        free = !SD.exists(g_logName);
    }
    if (!free) {
        Serial.println("card holds 999 logs already: logging off");  // never overwrite one
        return;
    }
    g_logFile = SD.open(g_logName, FILE_WRITE);
    if (!g_logFile) return;
    g_logFile.println("type,ms,lat,lon,alt_m,sats,nav,heading,pitch,roll,head_az,head_el,world_az,world_el,dbm,frames,channel");
    g_logOk = true;
    Serial.printf("logging to %s\n", g_logName);
}

static void logRow(char type, AzEl world, float dbm, int frames) {
    if (!g_logOk) return;
    g_logFile.printf("%c,%lu,", type, (unsigned long)millis());
    if (gpsFresh()) g_logFile.printf("%.7f,%.7f,%.1f,%u,", g_gps.lat, g_gps.lon, g_gps.alt, g_gps.sats);
    else g_logFile.print(",,,0,");
    // nav = 1 when heading, pitch and roll come from a calibrated compass.
    g_logFile.printf("%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d,%u\n", navOk() ? 1 : 0, g_att.heading, g_att.pitch, g_att.roll,
                     g_now.az, g_now.el, world.az, world.el, dbm, frames, g_targetChannel);
    g_logRows++;
}

// Called every pass of loop(): writes what is buffered to the card every
// two seconds, so a power cut loses little.
static void logPoll() {
    static uint32_t tFlush = 0;
    if (g_logOk && millis() - tFlush >= 2000) {
        tFlush = millis();
        g_logFile.flush();
    }
}
