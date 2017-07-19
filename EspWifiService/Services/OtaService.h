#ifndef __OTA_SERVICE_H__
#define __OTA_SERVICE_H__

#include "Common/ServicesInterface.h"


class OtaServiceClass : public ServicesInterface {
public:
  OtaServiceClass();
  virtual void init();
  virtual void run();
  virtual void prepareForOta();
  virtual const std::string& getName();
  static const std::string name;

  void configureHttpUpdate(const char* url, const char* name);
  void checkForUpdate();

private:
  const char* update_url;
  const char* firmware_name;
};

extern OtaServiceClass OtaService;

#endif  // __OTA_SERVICE_H__
