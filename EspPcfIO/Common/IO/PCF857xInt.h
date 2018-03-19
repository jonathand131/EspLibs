#ifndef __PCF857x_INT_H__
#define __PCF857x_INT_H__

#include <stdint.h>
#include <list>
#include <Wire.h>
#include <pcf8574_esp.h>
#include <Common/IO/BaseIO.h>
#include <Common/IO/ArduinoIO.h>


class PcfIoEventHandler {
public:
  typedef enum : uint8_t {
    PCF_PIN_FALLED = 0u,
    PCF_PIN_RISED
  } PinChangeStatus;
  virtual void interruptHandler(PinChangeStatus status) = 0;
  virtual uint8_t getPin() = 0;
  virtual bool isInput() = 0;
};


class PCF857xInt : public PCF857x {
public:
  PCF857xInt(uint8_t address, TwoWire* UseWire, ArduinoIO& interrupt_pin, bool is8575 = false);
  void registerIo(PcfIoEventHandler* io);
  void unregisterIo(PcfIoEventHandler* io);

private:
  void interruptHandler();
  uint16_t int_data;
  ArduinoIO& interrupt_pin;
  std::list<PcfIoEventHandler*> io_list;
};


#endif  // __PCF857x_INT_H__
