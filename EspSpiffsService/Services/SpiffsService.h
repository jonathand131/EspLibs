#ifndef __SPIFFS_SERVICE_H__
#define __SPIFFS_SERVICE_H__

#include "Common/ServicesInterface.h"


class SpiffsServiceClass : public ServicesInterface {
public:
  SpiffsServiceClass();
  virtual void init();
  virtual void run();
  virtual void prepareForOta();
  virtual const std::string& getName();
  static const std::string name;
};

extern SpiffsServiceClass SpiffsService;

#endif  // __SPIFFS_SERVICE_H__
