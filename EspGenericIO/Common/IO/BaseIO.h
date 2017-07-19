#ifndef __BASE_IO_H__
#define __BASE_IO_H__

#include <stdint.h>

enum IoFunc : uint8_t {
  NOT_USED=0,
  LOCAL_IO,
  REMOTE_IO,
  SPECIAL_IO,
};

class BaseIO {
public:
  virtual bool read() = 0;
  virtual void set(bool val) = 0;
  virtual void setMode(uint8_t mode) = 0;
};

struct IoList {
  uint16_t idx;
  uint8_t pin;
  IoFunc func;
};

#endif  // __BASE_IO_H__
