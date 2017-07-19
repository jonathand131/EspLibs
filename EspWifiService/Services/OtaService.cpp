#include "Common/SystemManager.h"
#include "Services/OtaService.h"
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoOTA.h>


const std::string OtaServiceClass::name = "OtaService";

OtaServiceClass::OtaServiceClass(): update_url(nullptr), firmware_name(nullptr) {
}

void OtaServiceClass::init() {
  SystemManager.registerService(this);

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("OTA Start");
    SystemManager.prepareForOta();
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}

void OtaServiceClass::run() {
  ArduinoOTA.handle();
}

void OtaServiceClass::prepareForOta() {
}

const std::string& OtaServiceClass::getName() {
  return OtaServiceClass::name;
}

void OtaServiceClass::configureHttpUpdate(const char* url, const char* name) {
  this->update_url = url;
  this->firmware_name = name;
}

void OtaServiceClass::checkForUpdate() {
  if((this->update_url == nullptr) || (this->firmware_name == nullptr)) {
    return;
  }

  t_httpUpdate_return ret = ESPhttpUpdate.update(this->update_url, this->firmware_name);
  switch(ret) {
    case HTTP_UPDATE_FAILED:
    {
      Serial.println("[update] Update failed.");
      break;
    }

    case HTTP_UPDATE_NO_UPDATES:
    {
      Serial.println("[update] Update no Update.");
      break;
    }

    case HTTP_UPDATE_OK:
    {
      Serial.println("[update] Update ok."); // may not called we reboot the ESP
      break;
    }
  }
}

OtaServiceClass OtaService;
