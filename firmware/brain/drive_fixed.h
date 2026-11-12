// Drivetrain: none. The antenna is fixed to the vehicle at ANT_AZ / ANT_EL
// (config.h) and the vehicle itself does the turning. Selected with
// DRIVE_FIXED 1. Included by brain.ino after its globals.
#pragma once

static const char* const kDriveHelp = "fixed antenna: there are no motors to command";

static void driveBegin() {}
static void driveGoal(AzEl) {}
static void driveFree() {}
static void drivePoll() {
    g_now.az = ANT_AZ;
    g_now.el = ANT_EL;
    g_driveOk = true;
}
static bool driveConsole(const char*) { return false; }
