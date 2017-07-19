#include "Common/SystemManager.h"
#include "Services/SpiffsService.h"
#include <FS.h>


const std::string SpiffsServiceClass::name = "SpiffsService";

SpiffsServiceClass::SpiffsServiceClass() {
}

void SpiffsServiceClass::init() {
  SystemManager.registerService(this);

  if(!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS, formating...");
    SPIFFS.format();
  }
  Serial.println("SPIFFS is ready.");
}

void SpiffsServiceClass::run() {
  /* Nothing to do */
}

void SpiffsServiceClass::prepareForOta() {
  SPIFFS.end();
  Serial.println("SPIFFS unmounted.");
}

const std::string& SpiffsServiceClass::getName() {
  return SpiffsServiceClass::name;
}


SpiffsServiceClass SpiffsService;
