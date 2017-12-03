#include <FunctionalInterrupt.h>
#include "ArduinoIO.h"


ArduinoIO::ArduinoIO(uint8_t pin) : pin(pin) {}

bool ArduinoIO::read() {
  return (digitalRead(this->pin) > 0);
}

void ArduinoIO::set(bool val) {
  digitalWrite(this->pin, val?1:0);
}

void ArduinoIO::setMode(PinMode mode) {
  switch(mode) {
    case PIN_OUTPUT:
    {
      pinMode(this->pin, OUTPUT);
      break;
    }

    case PIN_INPUT:
    {
      pinMode(this->pin, INPUT);
      break;
    }

    default:
    {
      // Unknown mode
      break;
    }
  }
}

void ArduinoIO::attachInterruptHandler(std::function<void(void)> handler, InterruptMode mode) {
  int arduino_mode;

  switch(mode) {
    case PIN_CHANGE:
    {
      arduino_mode = CHANGE;
      break;
    }

    case PIN_RISING:
    {
      arduino_mode = RISING;
      break;
    }

    case PIN_FALLING:
    {
      arduino_mode = FALLING;
      break;
    }

    default:
    {
      arduino_mode = CHANGE;
      break;
    }
  }

  attachInterrupt(this->pin, handler, arduino_mode);
}
