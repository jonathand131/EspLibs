#include <Arduino.h>
#include "ArduinoADC.h"

ArduinoADC::ArduinoADC(uint8_t pin) : pin(pin), ratio(1.0f) {}

float ArduinoADC::read() {
  return (((float)analogRead(this->pin)) / 1024.0f * this->ratio);
}

void ArduinoADC::setRatio(float ratio) {
  this->ratio = ratio;
}
