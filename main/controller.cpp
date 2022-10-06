#include "Arduino.h"
#include "controller.hpp"

using namespace firmware::controller;

Basic::Basic(float kSensitivity, float kApproachSpeed) {
  this->kSensitivity = kSensitivity;
  this->kApproachSpeed = kApproachSpeed;
}

float Basic::update(float target) {
  long elapsed = getElapsed();

  float error = target * kSensitivity - lastOutput;

  lastOutput += (elapsed*kApproachSpeed)/error;

  return lastOutput;
}

long Basic::getElapsed() {
  long currentTime = millis();
  long elapsed = currentTime - lastUpdated;
  lastUpdated = millis();

  return elapsed;
}

PID::PID(float kP, float kI, float kD, float upper, float lower) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->upper = upper;
  this->lower = lower;
}

float PID::update(float target) {
  long elapsed = getElapsed();

  float error = target - lastOutput;

  float p = kP * error;

  // Prevent further accumulation of the integral beyond the set upper and lower
  // limits.
  if ((lastOutput >= lower) && (lastOutput <= upper)) {
    integral += elapsed * error;
  }
  float i = kI * integral;

  float d = kD * (error - lastError)/elapsed;

  float output = constrain(p + i + d, lower, upper);
  lastOutput = output;

  return output;
}

long PID::getElapsed() {
  long currentTime = millis();
  long elapsed = currentTime - lastUpdated;
  lastUpdated = millis();

  return elapsed;
}
