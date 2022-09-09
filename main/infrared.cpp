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
