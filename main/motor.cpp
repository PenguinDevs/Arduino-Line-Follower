#include "Arduino.h"
#include "motor.hpp"
#include "debugger.hpp"

using namespace hardware::motor;

Motor::Motor(int pinInput1, int pinInput2, int pinPWM, bool invert) {
  if (invert) {
    this->pinInput1 = pinInput1;
    this->pinInput2 = pinInput2;
  } else {
    this->pinInput1 = pinInput2;
    this->pinInput2 = pinInput1;
  }
  this->pinPWM = pinPWM;
  this->invert = invert;  // Not needed, can be removed.

  pinMode(pinInput1, OUTPUT);
  pinMode(pinInput2, OUTPUT);
}

void Motor::changeState(MotorState motorState) {
  if (motorState == lastState) {return;}
  lastState = motorState;

  switch (motorState) {
    case MotorState::Off:
      digitalWrite(pinInput1, LOW);
      digitalWrite(pinInput2, LOW);
      break;
    case MotorState::Forward:
      digitalWrite(pinInput1, HIGH);
      digitalWrite(pinInput2, LOW);
      break;
    case MotorState::Backward:
      digitalWrite(pinInput1, LOW);
      digitalWrite(pinInput2, HIGH);
      break;
  }
}

void Motor::setVelocity(int velocity) {
  if (velocity == this->velocity) {return;}
  velocity = constrain(velocity, -255, 255);

  if (velocity == 0) {
    changeState(MotorState::Off);
  } else if (velocity > 0) {
    changeState(MotorState::Forward);
  } else if (velocity < 0) {
    changeState(MotorState::Backward);
  }

  analogWrite(pinPWM, abs(velocity));
}


MotorPair::MotorPair(
    const Motor &motorL,
    const Motor &motorR
) {
  this->motorL = motorL;
  this->motorR = motorR;
}

void MotorPair::setVelocity(int velocity) {
  if (velocity == this->velocity) {return;}
  this->velocity = velocity;

  setMovement();
}

void MotorPair::setSteer(float direction) {
  if (direction == this->direction) {return;}
  this->direction = constrain(direction, -1, 1);

  setMovement();
}

void MotorPair::setMovement() {
  int velocityL = static_cast<int>(velocity * (1+direction*2));
  int velocityR = static_cast<int>(velocity * (1-direction*2));

  motorL.setVelocity(velocityL);
  motorR.setVelocity(velocityR);

  firmware::debugger::log(
      firmware::debugger::LoggingLevel::kMotorVelocities,
      "L:"+String(velocity)+"\tR:"+String(velocityR));
}
