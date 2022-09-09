#pragma once

namespace blinker {

class Blinker {
  private:
    byte pinLED;

    boolean ledState = LOW;

    float ledOnDur;
    float ledOffDur;

    float lastUpdateTime = 0;

  public:
    Blinker(byte pinLED, float ledOnDur, float ledOffDur) {
      this->pinLED = pinLED;
      this->ledOnDur = ledOnDur;
      this->ledOffDur = ledOffDur;

      pinMode(pinLED, OUTPUT);
    }

    void update() {
      float currentTime = millis();

      if(currentTime >= lastUpdateTime) {

        if(ledState) {
          ledState = LOW;
          lastUpdateTime = currentTime + ledOffDur;
        }
        else{
          ledState = HIGH;
          lastUpdateTime = currentTime + ledOnDur;
        }

        // Serial.print("Blink");
        digitalWrite(pinLED, ledState);
      }
    }
};

}