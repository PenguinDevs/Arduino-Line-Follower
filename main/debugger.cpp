#include "Arduino.h"
#include "debugger.hpp"

using namespace firmware::debugger;

LoggingMode activeLoggingMode = LoggingMode::kGeneral;

const int kLoggingModeCount = 4;

// TODO: Figure out how to print logging levels depending on logging mode using
// a lookup table.
// // The column size isn't actually 3 :(
// const LoggingLevel LoggingModeLevels[3][3] = {
//   {kInfo, kWarning},
//   {kInfo, kWarning, kDebug},
//   {kInfraredTriadInputWError}
// };


void firmware::debugger::initialise() {
  Serial.begin(9600);

  changeLoggingMode(LoggingMode::kGeneral);
}

void firmware::debugger::log(LoggingLevel loggingLevel, String message) {
  // TODO: Use a lookup table instead of casing and ifs.
  // for (int i = 0; i < kLoggingModeCount; i++) {
  //   Serial.print(String(activeLoggingMode));
  //   Serial.println(String(LoggingModeLevels[static_cast<int>(activeLoggingMode)][i]));
  // }

  switch (activeLoggingMode) {
    case LoggingMode::kGeneral:
      if (
        loggingLevel != LoggingLevel::kInfo &&
        loggingLevel != LoggingLevel::kWarning
      ) {
        return;
      }
      break;
    case LoggingMode::kGeneralWDebug:
      if (
        loggingLevel != LoggingLevel::kInfo &&
        loggingLevel != LoggingLevel::kWarning &&
        loggingLevel != LoggingLevel::kDebug
      ) {
        return;
      }
      break;
    case LoggingMode::kInfrared:
      if (
        loggingLevel != LoggingLevel::kInfraredTriadInputWError
      ) {
        return;
      }
      break;
    case LoggingMode::kMotors:
      if (
        loggingLevel != LoggingLevel::kMotorVelocities
      ) {
        return;
      }
      break;
  }

  Serial.println(message);
}
void firmware::debugger::debug(String message) {
  log(LoggingLevel::kDebug, message);
}
void firmware::debugger::info(String message) {
  log(LoggingLevel::kInfo, message);
}
void firmware::debugger::warn(String message) {
  log(LoggingLevel::kWarning, message);
}

void firmware::debugger::changeLoggingMode(LoggingMode loggingMode) {
  if (loggingMode != activeLoggingMode) {
    activeLoggingMode = loggingMode;
  }
}
void firmware::debugger::nextLoggingMode() {
  changeLoggingMode(
      static_cast<LoggingMode>((activeLoggingMode+1) % kLoggingModeCount));
}
