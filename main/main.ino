#include "pins.hpp"
#include "infrared.hpp"
#include "motor.hpp"

#include "debugger.hpp"
#include "serial_command.hpp"

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
    true);
hardware::motor::MotorPair motorPair(motorL, motorR);


void setup() {
  firmware::debugger::initialise();
  firmware::debugger::changeLoggingMode(
      firmware::debugger::LoggingMode::kGeneralWDebug);
}

void loop() {
  hardware::infrared::InfraredState* infraredTriadData = sensorsTriad.read();
  firmware::debugger::log(
      firmware::debugger::LoggingLevel::kInfraredTriadInputWError,
      String(infraredTriadData[0])
      + String(infraredTriadData[1])
      + String(infraredTriadData[2]));

//   if (infraredTriadData[0] == hardware::infrared::kWhite) {
//     motorR.changeState(hardware::motor::Forward);
//   } else {
//     motorR.changeState(hardware::motor::Off);
//   }
//   if (infraredTriadData[2] == hardware::infrared::kWhite) {
//     motorR.changeState(hardware::motor::Forward);
//   } else {
//     motorR.changeState(hardware::motor::Off);
//   }


//   for (int i=-255; i < 256; i++) {
//     motorL.setVelocity(i);
//     motorR.setVelocity(-i);
//     delay(50);
//   }
//   for (int i=255; i > -256; i--) {
//     motorL.setVelocity(i);
//     motorR.setVelocity(-i);
//     delay(50);
//   }


  motorPair.setVelocity(255);


//   firmware::debugger::nextLoggingMode();
  firmware::command::pollSerial();
  delay(100);
}
