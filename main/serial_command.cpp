#include "Arduino.h"
#include "serial_command.hpp"
#include "motor.hpp"

using namespace firmware::command;

hardware::motor::MotorPair extern motorPair;

void firmware::command::pollSerial() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    Serial.println("RAW" + input);

    String command = input.substring(0, 3);
    String param = input.substring(4);

    // Unfortunately I cannot use a string to compare in a switch case. :/
    // TODO: Figure out a way for ^, maybe somehow retrieve unicode from
    // string characters.
    if (command == "dir") {  // Steer direction
        float direction = param.toFloat();
        motorPair.setSteer(direction);
    }

    Serial.println(command + param);
  }
}
