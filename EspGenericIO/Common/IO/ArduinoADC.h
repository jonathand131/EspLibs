#ifndef __ARDUINO_ADC_H__
#define __ARDUINO_ADC_H__

#include <stdint.h>
#include "BaseADC.h"


class ArduinoADC : public BaseADC {
public:
  ArduinoADC(uint8_t pin);
  virtual float read();
  virtual void setRatio(float ratio);

private:
  uint8_t pin;
  float ratio;
};

#endif  // __ARDUINO_ADC_H__
