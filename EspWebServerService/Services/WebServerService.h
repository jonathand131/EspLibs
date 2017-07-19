#ifndef __WEB_SERVER_SERVICE_H__
#define __WEB_SERVER_SERVICE_H__

#include <ESPAsyncWebServer.h>
#include "Common/ServicesInterface.h"

#define WEB_SRV_PORT 80


class WebServerServiceClass : public ServicesInterface {
public:
  WebServerServiceClass();
  virtual void init();
  virtual void run();
  virtual void prepareForOta();
  virtual const std::string& getName();
  static const std::string name;

  AsyncWebServer* getAsyncWebServer();
};

extern WebServerServiceClass WebServerService;

#endif  // __WEB_SERVER_SERVICE_H__
