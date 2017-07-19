#include "LocalIO.h"

LocalIO::LocalIO(uint8_t pin) : pin(pin) {}

bool LocalIO::read() {
  return (digitalRead(this->pin) > 0);
}

void LocalIO::set(bool val) {
  digitalWrite(this->pin, val?1:0);
}

void LocalIO::setMode(uint8_t mode) {
  pinMode(this->pin, mode);
}
