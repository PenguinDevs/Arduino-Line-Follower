#pragma once

namespace firmware::debugger {

void initialise();

enum LoggingLevel {
  kDebug,
  kInfo,
  kWarning,
  // Data from the 3 infrared sensors, plus the error value from reaching a
  // straight line.
  kInfraredTriadInputWError
};
void log(LoggingLevel loggingLevel, String message);
void debug(String message);
void info(String message);
void warn(String message);

enum LoggingMode {
  kGeneral,
  kGeneralWDebug,
  kInfrared
};

// extern enum LoggingMode activeLoggingMode;

void changeLoggingMode(LoggingMode loggingMode);
void nextLoggingMode();

}  // namespace firmware::debugger
