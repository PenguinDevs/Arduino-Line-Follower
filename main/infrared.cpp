#include "Arduino.h"
#include "infrared.hpp"
#include "debugger.hpp"

using namespace hardware::infrared;

InfraredSensor::InfraredSensor(int pinInput) {
  this->pinInput = pinInput;

  pinMode(pinInput, INPUT);
}

InfraredState InfraredSensor::read() {
  switch (digitalRead(pinInput)) {
    case HIGH:
      return InfraredState::kWhite;
    case LOW:
      return InfraredState::kBlack;
  }
}


InfraredSensorsTriad::InfraredSensorsTriad(
    const InfraredSensor &sensorInfraredL,
    const InfraredSensor &sensorInfraredC,
    const InfraredSensor &sensorInfraredR
) {
  this->sensorInfraredL = sensorInfraredL;
  this->sensorInfraredC = sensorInfraredC;
  this->sensorInfraredR = sensorInfraredR;
}

InfraredState* InfraredSensorsTriad::read() {
  // static InfraredState triadData[3] = {
  //   sensorInfraredL.read(),
  //   sensorInfraredC.read(),
  //   sensorInfraredR.read()
  // };
  static InfraredState triadData[3];
  triadData[0] = sensorInfraredL.read();
  triadData[1] = sensorInfraredC.read();
  triadData[2] = sensorInfraredR.read();

  return triadData;
}

float InfraredSensorsTriad::getDirection() {
  hardware::infrared::InfraredState* infraredTriadData = read();

  firmware::debugger::log(
      firmware::debugger::LoggingLevel::kInfraredTriadInputWError,
      String(infraredTriadData[0])
      + String(infraredTriadData[1])
      + String(infraredTriadData[2])
      +"|"
      + String(lastBlackSensed));

  // if (infraredTriadData[1] == InfraredState::kBlack) {
  //   // Middle sensor detects black.
  //   // The middle sensor is what we care the most, so it is the first condition
  //   // that we want to check for.
  //   lastBlackSensed = 0;
  // } else if (infraredTriadData[0] == InfraredState::kBlack) {
  //   // Left sensor detects black.
  //   lastBlackSensed = -1;
  // } else if (infraredTriadData[2] == InfraredState::kBlack) {
  //   // Right sensor detects black.
  //   lastBlackSensed = 1;
  // }  // else ignore and leave lastBlackSensed the way it is.

  if (infraredTriadData[1] == InfraredState::kBlack) {
    // Middle sensor detects black.
    lastBlackSensed = 0;
    return 0;
  } else if (infraredTriadData[0] == InfraredState::kBlack) {
    // Left sensor detects black.
    lastBlackSensed = -1;
    return -1;
  } else if (infraredTriadData[2] == InfraredState::kBlack) {
    // Right sensor detects black.
    lastBlackSensed = 1;
    return 1;
  } else {
    return lastBlackSensed * 3;
  }
}
