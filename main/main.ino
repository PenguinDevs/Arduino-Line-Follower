#include "pins.hpp"
#include "infrared.hpp"
#include "debugger.hpp"

hardware::infrared::InfraredSensor sensorL(hardware::pins::kPinInfraredL);
hardware::infrared::InfraredSensor sensorC(hardware::pins::kPinInfraredC);
hardware::infrared::InfraredSensor sensorR(hardware::pins::kPinInfraredR);
hardware::infrared::InfraredSensorsTriad sensorsTriad(
    sensorL,
    sensorC,
    sensorR);

void setup() {
  firmware::debugger::initialise();
  firmware::debugger::changeLoggingMode(
      firmware::debugger::LoggingMode::kGeneralWDebug);
}

void loop() {
  hardware::infrared::InfraredState* infraredTriadData = sensorsTriad.read();
  firmware::debugger::debug(
      String(infraredTriadData[0])
      + String(infraredTriadData[1])
      + String(infraredTriadData[2]));

  // firmware::debugger::nextLoggingMode();
  delay(100);
}
