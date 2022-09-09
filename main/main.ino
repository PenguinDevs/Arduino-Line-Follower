#include "hardware/pins.hpp"
#include "hardware/infrared.hpp"

hardware::infrared::InfraredSensor sensorL(hardware::pins::kInfraredLPin);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print(sensorL.read());
  delay(100);
}
