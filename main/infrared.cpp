#include "Arduino.h"
#include "infrared.hpp"

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

// Not sure how to return a tuple let alone an array, so a string with the
// content will be returned instead.
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

  // return String(sensorInfraredL.read())
  //     + String(sensorInfraredC.read())
  //     + String(sensorInfraredR.read());
}
