#ifndef __COMMON_INTERFACE_H__
#define __COMMON_INTERFACE_H__

#include <string>


class CommonInterface {
public:
  virtual void run() = 0;
  virtual void prepareForOta() = 0;
  virtual const std::string& getName() = 0;
  virtual void handleEvent(uint8_t event);
};

#endif  // __COMMON_INTERFACE_H__
