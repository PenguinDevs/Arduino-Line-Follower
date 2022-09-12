#include "Arduino.h"
#include "motor.hpp"

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

  switch (motorState) {
    case MotorState::Off:
      digitalWrite(pinInput1, LOW);
      digitalWrite(pinInput2, LOW);
      break;
    case MotorState::Forward:
      Serial.println("FORWARD" + String(pinInput1) + String(pinInput2));
      digitalWrite(pinInput1, HIGH);
      digitalWrite(pinInput2, LOW);
      break;
    case MotorState::Backward:
      digitalWrite(pinInput1, LOW);
      digitalWrite(pinInput2, HIGH);
      break;
  }
  lastState = motorState;
}

void Motor::setVelocity(unsigned int velocity) {
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

void MotorPair::setVelocity(unsigned int velocity) {
  if (velocity == this->velocity) {return;}

  this->velocity = velocity;

  setMovement();
}

void MotorPair::setSteer(float direction) {
  if (direction == this->direction) {return;}

  this->direction = direction;

  setMovement();
}

void MotorPair::setMovement() {
  motorL.setVelocity(velocity * (1+direction));
  motorR.setVelocity(velocity * (1-direction));
}
