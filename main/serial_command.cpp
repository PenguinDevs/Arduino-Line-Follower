#include "Arduino.h"
#include "serial_command.hpp"
#include "motor.hpp"
#include "debugger.hpp"

using namespace firmware::command;

hardware::motor::MotorPair extern motorPair;

void firmware::command::pollSerial() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();

    String command = input.substring(0, 3);
    String param = input.substring(4);

    firmware::debugger::info("SERIAL RECEIVED: " + command + param);

    // Unfortunately I cannot use a string to compare in a switch case. :/
    // TODO: Figure out a way for ^, maybe somehow retrieve unicode from
    // string characters.
    if (command == "dir") {  // Steer direction
        float direction = param.toFloat();
        motorPair.setSteer(direction);

        firmware::debugger::info(
            "Motor pair direction set to " + String(direction));
    }
  }
}
