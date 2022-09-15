#pragma once

namespace firmware::debugger {

void initialise();

void led_blink(int amount);

// Severity of a particular log.
enum LoggingLevel {
  kDebug,
  kInfo,
  kWarning,
  // Data from the 3 infrared sensors, plus the error value from reaching a
  // straight line.
  kInfraredTriadInputWError,
  kMotorVelocities
};
void log(LoggingLevel loggingLevel, String message);
void debug(String message);
void info(String message);
void warn(String message);


// Type of output to display from Serial.
enum LoggingMode {
  kGeneral,
  kGeneralWDebug,
  kInfrared,
  kMotors
};

// extern enum LoggingMode activeLoggingMode;

void changeLoggingMode(LoggingMode loggingMode);
void nextLoggingMode();

}  // namespace firmware::debugger
