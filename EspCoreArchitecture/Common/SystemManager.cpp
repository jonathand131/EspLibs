#include "SystemManager.h"


void SystemManagerClass::run() {
  for(ServicesInterface *srv : this->_srv_list) {
    srv->run();
  }
  for(ApplicationsInterface *app : this->_app_list) {
    app->run();
  }
}

void SystemManagerClass::prepareForOta() {
  for(ApplicationsInterface *app : this->_app_list) {
    app->prepareForOta();
  }
  for(ServicesInterface *srv : this->_srv_list) {
    srv->prepareForOta();
  }
}

void SystemManagerClass::registerApplication(ApplicationsInterface *app) {
    this->_app_list.push_back(app);
}

void SystemManagerClass::registerService(ServicesInterface *srv) {
    this->_srv_list.push_back(srv);
}

ServicesInterface* SystemManagerClass::getServiceByName(std::string name) {
  for(ServicesInterface *srv : this->_srv_list) {
    if(name == srv->getName()) {
      return srv;
    }
  }

  return nullptr;
}

ApplicationsInterface* SystemManagerClass::getApplicationByName(std::string name) {
  for(ApplicationsInterface *app : this->_app_list) {
    if(name == app->getName()) {
      return app;
    }
  }

  return nullptr;
}

void SystemManagerClass::dispatchEvent(uint8_t event) {
  for(ServicesInterface *srv : this->_srv_list) {
    srv->handleEvent(event);
  }
  for(ApplicationsInterface *app : this->_app_list) {
    app->handleEvent(event);
  }
}


SystemManagerClass SystemManager;
