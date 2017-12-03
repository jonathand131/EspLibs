#include "PcfRemoteIO.h"


PcfRemoteIO::PcfRemoteIO(uint8_t pin, PCF857xInt &pcf) :
  pin(pin), pcf(pcf), mode(PIN_OUTPUT), interrupt_mode(PIN_CHANGE) {
  this->pcf.registerIo(this);
}

PcfRemoteIO::~PcfRemoteIO() {
  this->pcf.unregisterIo(this);
}

bool PcfRemoteIO::read() {
  return (pcf.read(this->pin) > 0u);
}

void PcfRemoteIO::set(bool val) {
  if(this->mode == PIN_OUTPUT) {
    pcf.write(this->pin, val?1u:0u);
  }
}

void PcfRemoteIO::setMode(PinMode mode) {
  switch(mode) {
    case PIN_INPUT:
    {
      this->mode = mode;
      pcf.write(this->pin, 1u);
      break;
    }

    case PIN_OUTPUT:
    {
      this->mode = mode;
      break;
    }

    default:
    {
      // Not handled, leave mode unchanged
      break;
    }
  }
}

void PcfRemoteIO::attachInterruptHandler(std::function<void(void)> handler, InterruptMode mode) {
  this->handler = handler;
  this->interrupt_mode = mode;
}

void PcfRemoteIO::interruptHandler(PinChangeStatus status) {
  if((this->handler) &&
      ((this->interrupt_mode == PIN_CHANGE) ||
      ((this->interrupt_mode == PIN_RISING) && (status == PCF_PIN_RISED)) ||
      ((this->interrupt_mode == PIN_FALLING) && (status == PCF_PIN_FALLED)))) {
    this->handler();
  }
}

uint8_t PcfRemoteIO::getPin() {
  return this->pin;
}
