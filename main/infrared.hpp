#pragma once

namespace hardware::infrared {

enum InfraredState {
  kBlack,
  kWhite
};

class InfraredSensor {
 public:
  InfraredSensor() = default;
  explicit InfraredSensor(int pinInput);
  InfraredState read();
 private:
  int pinInput;
};

class InfraredSensorsTriad {
 public:
  InfraredSensorsTriad(
      const InfraredSensor &sensorInfraredL,
      const InfraredSensor &sensorInfraredC,
      const InfraredSensor &sensorInfraredR);
  InfraredState* read();
  int getError();
 private:
  // How??? https://stackoverflow.com/questions/47897253/error-no-matching-function-to-call-for-with-class-as-attribute-c
  InfraredSensor sensorInfraredL;
  InfraredSensor sensorInfraredC;
  InfraredSensor sensorInfraredR;

  int lastBlackSensed;
};

}  // namespace hardware::infrared
