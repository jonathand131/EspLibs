#ifndef __PCF_REMOTE_IO_H__
#define __PCF_REMOTE_IO_H__

#include "BaseIO.h"
#include <pcf8574_esp.h>


class PcfRemoteIO : public BaseIO {
public:
  PcfRemoteIO(uint8_t pin, PCF857x *pcf);
  virtual bool read();
  virtual void set(bool val);
  virtual void setMode(uint8_t mode);

private:
  uint8_t pin;
  PCF857x *pcf;
};

struct TwoWireBusList {
  uint16_t idx;
  uint8_t sda_pin_idx;
  uint8_t scl_pin_idx;
};

struct PcfExtenderList {
  uint16_t idx;
  uint16_t twowire_bus_idx;
  uint16_t address;
};

struct PcfIoList {
  uint16_t idx;
  uint16_t pcf_extender_idx;
  uint8_t pin;
};

#endif  // __PCF_REMOTE_IO_H__
