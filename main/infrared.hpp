#pragma once

namespace hardware::infrared {

// enum class InfraredStates {
//   kBlack,
//   kWhite
// }

class InfraredSensor {
 public:
  explicit InfraredSensor(int pinInput);
  int read();
 private:
  int pinInput;
};

}  // namespace hardware::infrared
