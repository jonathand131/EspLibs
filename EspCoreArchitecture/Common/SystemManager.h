#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#include <list>
#include "ApplicationsInterface.h"
#include "ServicesInterface.h"


class SystemManagerClass {
public:
  void run();
  void prepareForOta();
  void registerService(ServicesInterface *srv);
  void registerApplication(ApplicationsInterface *app);
  ServicesInterface* getServiceByName(std::string name);
  ApplicationsInterface* getApplicationByName(std::string name);
  void dispatchEvent(uint8_t event);

private:
  std::list<ServicesInterface*> _srv_list;
  std::list<ApplicationsInterface*> _app_list;
};

extern SystemManagerClass SystemManager;

#endif  // __SYSTEM_MANAGER_H__
