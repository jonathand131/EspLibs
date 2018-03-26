#include "Common/SystemManager.h"
#include "Services/WifiService.h"
#include <ESP8266WiFi.h>


const std::string WifiServiceClass::name = "WifiService";

WifiServiceClass::WifiServiceClass() :
    state(WIFI_SERVICE_STATE_INIT),
    mode(WIFI_SERVICE_MODE_STAY_CONNECTED),
    ssid(nullptr), password(nullptr),
    allow_caching(false) {
}

void WifiServiceClass::init() {
  SystemManager.registerService(this);
}

void WifiServiceClass::run() {
  switch(this->state) {
    case WIFI_SERVICE_STATE_INIT:
    {
      if(this->mode == WIFI_SERVICE_MODE_STAY_CONNECTED) {
        WiFi.setAutoReconnect(true);
      } else {
        WiFi.mode(WIFI_OFF);
        WiFi.setAutoReconnect(false);
      }
      WiFi.persistent(this->allow_caching);
      this->state = WIFI_SERVICE_STATE_NOT_CONNECTED;
      break;
    }

    case WIFI_SERVICE_STATE_NOT_CONNECTED:
    {
      if(this->mode == WIFI_SERVICE_MODE_STAY_CONNECTED) {
        this->connect();
      }
      break;
    }

    case WIFI_SERVICE_STATE_CONNECTING:
    {
      this->updateConnectionState();
      if (this->state == WIFI_SERVICE_STATE_CONNECTED) {
        Serial.println("Connected.");
      } else if (this->state == WIFI_SERVICE_STATE_NOT_CONNECTED) {
        Serial.println("Connection failed.");
      }
      break;
    }

    case WIFI_SERVICE_STATE_CONNECTED:
    {
      // Ensure we are still connected
      this->updateConnectionState();
      break;
    }

    default:
    {
      // Unknown connection state
      break;
    }
  }
}

void WifiServiceClass::prepareForOta() {
  // Ensure to not disable the WiFi
  this->setMode(WIFI_SERVICE_MODE_STAY_CONNECTED);
}

const std::string& WifiServiceClass::getName() {
  return WifiServiceClass::name;
}

void WifiServiceClass::configure(const char* ssid, const char*  password) {
  this->ssid = ssid;
  this->password = password;
}

void WifiServiceClass::setMode(WifiServiceMode mode) {
  this->mode = mode;

  if(this->mode == WIFI_SERVICE_MODE_STAY_CONNECTED) {
    WiFi.setAutoReconnect(true);
  } else {
    WiFi.setAutoReconnect(false);
  }
}

void WifiServiceClass::setCachingStrategy(bool allow) {
  this->allow_caching = allow;
  WiFi.persistent(this->allow_caching);
}

void WifiServiceClass::connect() {
  if(this->state == WIFI_SERVICE_STATE_CONNECTED) {
    return;
  }

  this->state = WIFI_SERVICE_STATE_CONNECTING;
  WiFi.mode(WIFI_STA);

  Serial.println("Connecting...");
  WiFi.begin(this->ssid, this->password);
}

void WifiServiceClass::disconnect() {
  if(this->mode == WIFI_SERVICE_MODE_STAY_CONNECTED) {
    return;
  }

  Serial.println("Disconnecting...");
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  this->state = WIFI_SERVICE_STATE_NOT_CONNECTED;
  Serial.println("Disconnected.");
}

bool WifiServiceClass::isConnected() {
  // this->updateConnectionState();

  return (this->state == WIFI_SERVICE_STATE_CONNECTED);
}

void WifiServiceClass::updateConnectionState() {
  int status = WiFi.status();

  switch(status) {
    case WL_CONNECTED:
    {
      if(this->state != WIFI_SERVICE_STATE_CONNECTED) {
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
      }
      this->state = WIFI_SERVICE_STATE_CONNECTED;
      break;
    }

    case WL_CONNECT_FAILED:
    case WL_CONNECTION_LOST:
    case WL_DISCONNECTED:
    {
      if(this->state != WIFI_SERVICE_STATE_CONNECTING) {
        this->state = WIFI_SERVICE_STATE_NOT_CONNECTED;
      }
      break;
    }

    case WL_IDLE_STATUS:
    {
      // Still connecting
      this->state = WIFI_SERVICE_STATE_CONNECTING;
      break;
    }

    default:
    {
      // Another state...
      break;
    }
  }
}

WifiServiceClass WifiService;
