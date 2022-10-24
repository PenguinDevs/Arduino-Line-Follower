#pragma once

namespace firmware::controller {

class Basic {
 public:
  Basic(float kSensitivity);
  float update(float target);
 private:
  float kSensitivity;
};

class Accumulative {
 public:
  Accumulative(float kSensitivity, float kApproachSpeed);
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
  PID(float kP, float kD, float kI, float upper, float lower, bool resetToZero);
  float update(float target);
 private:
  float kP;
  float kD;
  float kI;
  float upper;
  float lower;
  bool resetToZero;

  long lastUpdated = millis();
  float integral = 0;
  float lastError = 0;
  float lastOutput = 0;

  long getElapsed();
};

}  // namespace firmware::controller
