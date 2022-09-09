#include "Arduino.h"
#include "debugger.hpp"

using namespace firmware::debugger;

void firmware::debugger::initialise() {
  Serial.begin(9600);
}

void firmware::debugger::log(LoggingLevel loggingLevel, String message) {
  Serial.print(message);
};
void firmware::debugger::debug(String message) {
  log(LoggingLevel::kDebug, message);
};
void firmware::debugger::info(String message) {
  log(LoggingLevel::kInfo, message);
};
