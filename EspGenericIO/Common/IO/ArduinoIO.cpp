#include "ArduinoIO.h"

ArduinoIO::ArduinoIO(uint8_t pin) : pin(pin) {}

bool ArduinoIO::read() {
  return (digitalRead(this->pin) > 0);
}

void ArduinoIO::set(bool val) {
  digitalWrite(this->pin, val?1:0);
}

void ArduinoIO::setMode(uint8_t mode) {
  pinMode(this->pin, mode);
}
