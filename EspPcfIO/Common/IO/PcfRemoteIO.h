#ifndef __PCF_REMOTE_IO_H__
#define __PCF_REMOTE_IO_H__

#include <functional>
#include <list>
#include <Common/IO/BaseIO.h>
#include "PCF857xInt.h"


class PcfRemoteIO : public BaseIO, public PcfIoEventHandler {
public:
  PcfRemoteIO(uint8_t pin, PCF857xInt &pcf);
  ~PcfRemoteIO();
  virtual bool read();
  virtual void set(bool val);
  virtual void setMode(PinMode mode);
  virtual void attachInterruptHandler(std::function<void(void)> handler, InterruptMode mode);
  virtual void interruptHandler(PinChangeStatus status);
  virtual uint8_t getPin();
  virtual bool isInput();

private:
  uint8_t pin;
  PinMode mode;
  PCF857xInt &pcf;
  struct PcfRemoteIOInterruptHandler {
    std::function<void(void)> handler;
    InterruptMode interrupt_mode;
  };
  std::list<PcfRemoteIOInterruptHandler> handlers;
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
