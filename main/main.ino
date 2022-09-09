#include "pins.hpp"
#include "infrared.hpp"
#include "debugger.hpp"

hardware::infrared::InfraredSensor sensorL(hardware::pins::kInfraredLPin);
hardware::infrared::InfraredSensor sensorC(hardware::pins::kInfraredCPin);
hardware::infrared::InfraredSensor sensorR(hardware::pins::kInfraredRPin);

void setup() {
  firmware::debugger::initialise();
}

void loop() {
  firmware::debugger::debug(String(sensorL.read()));
  delay(100);
}
