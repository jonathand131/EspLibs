#ifndef __BASE_IO_H__
#define __BASE_IO_H__

#include <stdint.h>
#include <functional>


enum IoFunc : uint8_t {
  NOT_USED=0,
  LOCAL_IO,
  REMOTE_IO,
  SPECIAL_IO,
};

typedef enum : uint8_t {
  PIN_INPUT = 0u,
  PIN_OUTPUT
} PinMode;

typedef enum : uint8_t {
  PIN_CHANGE = 0u,
  PIN_RISING,
  PIN_FALLING
} InterruptMode;


class BaseIO {
public:
  virtual bool read() = 0;
  virtual void set(bool val) = 0;
  virtual void setMode(PinMode mode) = 0;
  virtual void attachInterruptHandler(std::function<void(void)> handler, InterruptMode mode) = 0;
};

struct IoList {
  uint16_t idx;
  uint8_t pin;
  IoFunc func;
};

#endif  // __BASE_IO_H__
