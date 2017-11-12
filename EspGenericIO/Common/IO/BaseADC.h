#ifndef __BASE_ADC_H__
#define __BASE_ADC_H__

class BaseADC {
public:
  virtual float read() = 0;
  virtual void setRatio(float ratio) = 0;
};

#endif  // __BASE_ADC_H__
