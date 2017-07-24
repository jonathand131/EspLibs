#ifndef __ARDUINO_IO_H__
#define __ARDUINO_IO_H__

#include <Arduino.h>
#include "BaseIO.h"


class ArduinoIO : public BaseIO {
public:
  ArduinoIO(uint8_t pin);
  virtual bool read();
  virtual void set(bool val);
  virtual void setMode(uint8_t mode);

private:
  uint8_t pin;
};

#endif  // __ARDUINO_IO_H__
