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

}  // namespace firmware::debugger
