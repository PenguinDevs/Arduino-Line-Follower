#pragma once

namespace hardware::infrared {

enum InfraredState {
  kBlack,
  kWhite
};

class InfraredSensor {
 public:
  explicit InfraredSensor(int pinInput);
  InfraredState read();
 private:
  int pinInput;
};

}  // namespace hardware::infrared
