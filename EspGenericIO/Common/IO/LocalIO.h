#ifndef __LOCAL_IO_H__
#define __LOCAL_IO_H__

#include <Arduino.h>
#include "BaseIO.h"


class LocalIO : public BaseIO {
public:
  LocalIO(uint8_t pin);
  virtual bool read();
  virtual void set(bool val);
  virtual void setMode(uint8_t mode);

private:
  uint8_t pin;
};

#endif  // __LOCAL_IO_H__
