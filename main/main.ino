#include "pins.hpp"
#include "infrared.hpp"
#include "motor.hpp"

#include "debugger.hpp"
#include "serial_command.hpp"
#include "controller.hpp"

hardware::infrared::InfraredSensor sensorL(hardware::pins::kPinInfraredL);
hardware::infrared::InfraredSensor sensorC(hardware::pins::kPinInfraredC);
hardware::infrared::InfraredSensor sensorR(hardware::pins::kPinInfraredR);
hardware::infrared::InfraredSensorsTriad sensorsTriad(
    sensorL,
    sensorC,
    sensorR);

hardware::motor::Motor motorL(
    hardware::pins::kPinMotorL1,
    hardware::pins::kPinMotorL2,
    hardware::pins::kPinMotorLPWM,
    false);
hardware::motor::Motor motorR(
    hardware::pins::kPinMotorR1,
    hardware::pins::kPinMotorR2,
    hardware::pins::kPinMotorRPWM,
    false);
hardware::motor::MotorPair motorPair(motorL, motorR);

// firmware::controller::Basic controller(1);  // 150 val, * 0.4 error
// firmware::controller::Basic controller(1);  // 200 val, * 0.45 error

// firmware::controller::Accumulative controller(0.4, 0.005); // 200 vel

// firmware::controller::PID controller(0.11, 0, 0, 1, -1, false);  // 150 vel, * 0.4 error WIDE TURNS
// firmware::controller::PID controller(0.2, 0, 0, 1, -1, true);  // 200 vel, * 0.4 error SPEED
// firmware::controller::PID controller(0.31, 0, 0, 1, -1, true);  // 200 vel, * 0.4 error SPEED
// firmware::controller::PID controller(0.15, 0, 0, 1, -1, true);  // 220 vel, * 0.55 error SPEED INACCURATE
// firmware::controller::PID controller(0.5, 0, 0, 1, -1, true);  // 100 vel, * 0.25 error SMOOTH
// firmware::controller::PID controller(0.008, 0, 0, 1, -1, true);  // 100 vel, * 0.55 error SMOOTH FAIL
// firmware::controller::PID controller(0.31, 0, 10, 1, -1, false);  // 200 vel, * 0.4 error SPEED
// firmware::controller::PID controller(0.31, 0, 10, 1, -1, false);  // 255 vel, * 0.45 error MAX SPEED
// firmware::controller::PID controller(0.5, 0, 0, 1, -1, true);  // 100 vel, * 0.14 error SMOOTH
// firmware::controller::PID controller(0.5, 0, 0, 1, -1, true);  // 160 vel, * 0.185 error SMOOTH
// firmware::controller::PID controller(0.375, 0, 0, 1, -1, true);  // 200 vel, * 0.2 error SMOOTH
// firmware::controller::PID controller(0.325, 0, 0, 1, -1, true);  // 255 vel, * 0.21 error FAST SMOOTH * 2.5 out
// firmware::controller::PID controller(0.6, 0, 0, 1, -1, true);  // 100 vel, * 0.08 error FAST SMOOTH * 3.5 out NEW BATTERY
firmware::controller::PID controller(0.325, 0, 0, 1, -1, true);  // 255 vel, * 0.21 error FAST SMOOTH * 2.5 out NEW BATTERY




void setup() {
  firmware::debugger::initialise();
  firmware::debugger::changeLoggingMode(
      firmware::debugger::LoggingMode::kMotors);
}

void loop() {
  float error = sensorsTriad.getDirection();

  motorPair.setSteer(controller.update(error * 0.19));
//   motorPair.setSteer(error * 0.4);

  motorPair.setVelocity(120);

  firmware::command::pollSerial();
  delay(0);
}
