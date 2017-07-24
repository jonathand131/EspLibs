#ifndef __BASE_ADC_H__
#define __BASE_ADC_H__

#include <stdint.h>

class BaseADC {
public:
  virtual float read() = 0;
  virtual void setRatio(float ratio) = 0;
};

struct IoList {
  uint16_t idx;
  uint8_t pin;
  IoFunc func;
};

#endif  // __BASE_ADC_H__
