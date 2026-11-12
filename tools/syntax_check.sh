#!/usr/bin/env bash
# Compile-check a sketch with the ESP32 Arduino core already installed in
# ~/.arduino15, without arduino-cli. Checks syntax and types only: nothing
# is linked, so it cannot catch a missing library or a too-large image.
#
# Usage: tools/syntax_check.sh brain|sensor|motion
set -euo pipefail
A="$HOME/.arduino15/packages/esp32"
CORE=$(ls -d "$A"/hardware/esp32/*/ | sort -V | tail -1)
VER=$(basename "$CORE")
ROOT=$(cd "$(dirname "$0")/.." && pwd)
USERLIBS="$HOME/Arduino/libraries"

case "${1:-}" in
  brain)  MCU=esp32s3; BOARD=XIAO_ESP32S3; GXX=$(ls "$A"/tools/esp-x32/*/bin/xtensa-esp32s3-elf-g++); MEM=qio_opi
          EXTRA="-DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=0" ;;
  sensor) MCU=esp32c5; BOARD=XIAO_ESP32C5; GXX=$(ls "$A"/tools/esp-rv32/*/bin/riscv32-esp-elf-g++); MEM=qio_qspi
          EXTRA="-DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=1" ;;
  motion) MCU=esp32; BOARD=esp32; GXX=$(ls "$A"/tools/esp-x32/*/bin/xtensa-esp32-elf-g++); MEM=dio_qspi
          EXTRA="-DARDUINO_USB_CDC_ON_BOOT=0"
          # Simple FOC is not bundled: point SIMPLEFOC at a checkout of
          # github.com/simplefoc/Arduino-FOC, or install it as an Arduino library.
          SIMPLEFOC="${SIMPLEFOC:-$HOME/Arduino/libraries/Simple_FOC}"
          [ -d "$SIMPLEFOC/src" ] || { echo "motion: Simple FOC library not found at $SIMPLEFOC (set SIMPLEFOC=...)" >&2; exit 3; } ;;
  *) echo "usage: $0 brain|sensor|motion" >&2; exit 2 ;;
esac
SDK="$A/tools/$MCU-libs/$VER"

INC=(-I"$CORE/cores/esp32" -I"$CORE/variants/$BOARD" -I"$ROOT/lib/RMCore/src" -I"$ROOT/firmware/$1")
for l in "$CORE"/libraries/*/src "$USERLIBS"/*/src "$USERLIBS"/*/; do INC+=(-I"$l"); done
[ -n "${SIMPLEFOC:-}" ] && INC+=(-I"$SIMPLEFOC/src")

# An .ino file is C++ with <Arduino.h> implied; the sketches declare
# everything before use, so no prototype generation is needed.
# Arduino boards are named after their variant, upper-cased for the macro.
BOARDDEF=$(echo "$BOARD" | tr a-z A-Z)
[ "$BOARD" = esp32 ] && BOARDDEF=ESP32_DEV
"$GXX" -fsyntax-only -x c++ -w @"$SDK/flags/cpp_flags" \
  -DF_CPU=240000000L -DARDUINO=10607 -DARDUINO_$BOARDDEF -DARDUINO_ARCH_ESP32 \
  -DARDUINO_BOARD="\"$BOARD\"" -DARDUINO_VARIANT="\"$BOARD\"" -DESP32=ESP32 -DCORE_DEBUG_LEVEL=0 \
  -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 $EXTRA \
  @"$SDK/flags/defines" -iprefix "$SDK/include/" @"$SDK/flags/includes" -I"$SDK/$MEM/include" \
  "${INC[@]}" -include Arduino.h "$ROOT/firmware/$1/$1.ino"
echo "$1: compiles for $BOARD (core $VER, syntax and types only)"
