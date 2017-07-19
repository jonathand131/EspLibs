#ifndef __WIFI_SERVICE_H_
#define __WIFI_SERVICE_H_

#include "Common/ServicesInterface.h"


class WifiServiceClass : public ServicesInterface {
public:
  WifiServiceClass();
  virtual void init();
  virtual void run();
  virtual void prepareForOta();
  virtual const std::string& getName();
  static const std::string name;

  typedef enum : uint8_t  {
    WIFI_SERVICE_MODE_STAY_CONNECTED=0,
    WIFI_SERVICE_MODE_ON_DEMAND,
  } WifiServiceMode;

  void configure(const char* ssid, const char*  password);
  void setMode(WifiServiceMode mode);
  void setCachingStrategy(bool allow);
  void connect();
  void disconnect();
  bool isConnected();

private:
  typedef enum : uint8_t {
    WIFI_SERVICE_STATE_INIT=0,
    WIFI_SERVICE_STATE_NOT_CONNECTED,
    WIFI_SERVICE_STATE_CONNECTING,
    WIFI_SERVICE_STATE_CONNECTED,
  } WifiServiceState;
  WifiServiceState state;
  WifiServiceMode mode;
  const char* ssid;
  const char* password;
  bool allow_caching;
  void updateConnectionState();
};

extern WifiServiceClass WifiService;

#endif  // __WIFI_SERVICE_H_
