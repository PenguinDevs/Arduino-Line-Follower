#include "Arduino.h"
#include "infrared.hpp"

hardware::infrared::InfraredSensor::InfraredSensor(int pinInput) {
  this->pinInput = pinInput;

  pinMode(pinInput, INPUT);
}

int hardware::infrared::InfraredSensor::read() {
  return digitalRead(pinInput);
}
