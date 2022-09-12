#pragma once

namespace hardware::motor {

enum MotorState {
  Off,
  Forward,
  Backward
};

class Motor {
 public:
  Motor() = default;
  explicit Motor(int pinInput1, int pinInput2, int pinPWM, bool invert);
  void changeState(MotorState motorState);
  void setVelocity(unsigned int velocity);
 private:
  int pinInput1;
  int pinInput2;
  int pinPWM;
  bool invert;

  int velocity;
  MotorState lastState;
};

class MotorPair {
 public:
  MotorPair(const Motor &motorL, const Motor &motorR);
  void setVelocity(unsigned int velocity);
  void setSteer(float direction);
 private:
  // How??? https://stackoverflow.com/questions/47897253/error-no-matching-function-to-call-for-with-class-as-attribute-c
  Motor motorL;
  Motor motorR;

  int velocity;
  float direction;
  void setMovement();
};

}  // namespace hardware::motor
