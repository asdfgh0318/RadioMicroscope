# RadioMicroscope v2
#   make test      host tests of the core and of tools/locate.py (needs g++ and python3)
#   make check     compile-check both sketches with the installed ESP32 core,
#                  no arduino-cli needed (syntax and types only, no linking)
#   make web       regenerate firmware/brain/web_ui.h from web/index.html
#   make brain     compile the ESP32-S3 firmware   (needs arduino-cli)
#   make sensor    compile the ESP32-C5 firmware   (needs arduino-cli)
#   make motion    compile the motor-controller firmware (needs arduino-cli
#                  and the "Simple FOC" library)
#   make flash-brain PORT=/dev/ttyACM0   (likewise flash-sensor, flash-motion)
#
# make check needs the Simple FOC sources for the motor controller: install
# the library in ~/Arduino/libraries/Simple_FOC or pass SIMPLEFOC=/path/to/Arduino-FOC.

CXX ?= g++
ACLI ?= arduino-cli
BRAIN_FQBN ?= esp32:esp32:XIAO_ESP32S3:PSRAM=opi
SENSOR_FQBN ?= esp32:esp32:XIAO_ESP32C5
MOTION_FQBN ?= esp32:esp32:esp32
PORT ?= /dev/ttyACM0

# The check and build targets regenerate web_ui.h first.
.PHONY: test check web brain sensor motion flash-brain flash-sensor flash-motion clean

test:
	@mkdir -p build
	$(CXX) -std=c++17 -Wall -Wextra -O1 -fsanitize=address,undefined \
		-Ilib/RMCore/src tests/test_core.cpp -o build/test_core
	./build/test_core
	python3 tests/test_locate.py

check: web
	tools/syntax_check.sh sensor
	tools/syntax_check.sh brain
	tools/syntax_check.sh motion

web: firmware/brain/web_ui.h
firmware/brain/web_ui.h: web/index.html tools/embed_web.py
	python3 tools/embed_web.py web/index.html $@

brain: web
	$(ACLI) compile --fqbn $(BRAIN_FQBN) --library lib/RMCore --build-path build/brain firmware/brain

sensor:
	$(ACLI) compile --fqbn $(SENSOR_FQBN) --library lib/RMCore --build-path build/sensor firmware/sensor

motion:
	$(ACLI) compile --fqbn $(MOTION_FQBN) --library lib/RMCore --build-path build/motion firmware/motion

flash-brain: brain
	$(ACLI) upload --fqbn $(BRAIN_FQBN) --input-dir build/brain --port $(PORT) firmware/brain

flash-sensor: sensor
	$(ACLI) upload --fqbn $(SENSOR_FQBN) --input-dir build/sensor --port $(PORT) firmware/sensor

flash-motion: motion
	$(ACLI) upload --fqbn $(MOTION_FQBN) --input-dir build/motion --port $(PORT) firmware/motion

clean:
	rm -rf build
