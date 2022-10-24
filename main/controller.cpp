#include "Arduino.h"
#include "controller.hpp"
#include "debugger.hpp"

using namespace firmware::controller;

Basic::Basic(float kSensitivity) {
  this->kSensitivity = kSensitivity;
}

float Basic::update(float target) {
  return target*kSensitivity;
}

Accumulative::Accumulative(float kSensitivity, float kApproachSpeed) {
  this->kSensitivity = kSensitivity;
  this->kApproachSpeed = kApproachSpeed;
}

float Accumulative::update(float target) {
  long elapsed = getElapsed();

  float error = target * kSensitivity - lastOutput;

  if (error == 0.0 || error == -0.0) {
    return lastOutput;
  }
  
  debugger::info(String(lastOutput));

  lastOutput += (elapsed * kApproachSpeed) * error;

  return lastOutput;
}

long Accumulative::getElapsed() {
  long currentTime = millis();
  long elapsed = currentTime - lastUpdated;
  lastUpdated = millis();

  return elapsed;
}

PID::PID(float kP, float kI, float kD, float upper, float lower, bool resetToZero) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->upper = upper;
  this->lower = lower;
  this->resetToZero = resetToZero;
}

float PID::update(float target) {
  long elapsed = getElapsed();
  
  if (elapsed <= 0) {
    return lastOutput;
  }

  if (resetToZero) {
    if (target > 0 && lastOutput < 0) {
      lastOutput = 0;
    } else if (target < 0 && lastOutput > 0) {
      lastOutput = 0;
    } else if (target == 0) {
      lastOutput = 0;
    }
  }

  float error = target - lastOutput;

  float p = kP * error;

  // Prevent the integral from further accumulating its area if it is exceeds
  // its set range.
  if ((lastOutput > lower) && (lastOutput < upper)) {
    integral += elapsed * error;
  }
  float i = kI * integral;

  float d = kD * ((error - lastError) / elapsed);

  float output = p + i + d;
  lastOutput += output;

  debugger::info(String(lastOutput));

  return lastOutput;
}

long PID::getElapsed() {
  long currentTime = millis();
  long elapsed = currentTime - lastUpdated;
  lastUpdated = millis();

  return elapsed;
}
