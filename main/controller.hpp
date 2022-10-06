#pragma once

namespace firmware::controller {

class Basic {
 public:
  Basic(float kSensitivity, float kApproachSpeed);
  float update(float target);
 private:
  float kSensitivity;
  float kApproachSpeed;

  long lastUpdated = millis();
  float lastOutput = 0;

  long getElapsed();
};

class PID {
 public:
  PID(float kP, float kD, float kI, float upper, float lower);
  float update(float target);
 private:
  float kP;
  float kD;
  float kI;
  float upper;
  float lower;

  long lastUpdated = millis();
  float integral = 0;
  float lastError = 0;
  float lastOutput = 0;

  long getElapsed();
};

}  // namespace firmware::controller
