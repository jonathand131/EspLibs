#include "PcfRemoteIO.h"


PcfRemoteIO::PcfRemoteIO(uint8_t pin, PCF857xInt &pcf) :
  pin(pin), pcf(pcf), mode(PIN_OUTPUT) {
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
    case PIN_INPUT_PULLUP:
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
  PcfRemoteIOInterruptHandler handler_info = {handler, mode};
  this->handlers.push_back(handler_info);
}

void PcfRemoteIO::interruptHandler(PinChangeStatus status) {
  for(PcfRemoteIOInterruptHandler handler_info : this->handlers) {
    if((handler_info.handler != nullptr) &&
        ((handler_info.interrupt_mode == PIN_CHANGE) ||
        ((handler_info.interrupt_mode == PIN_RISING) && (status == PCF_PIN_RISED)) ||
        ((handler_info.interrupt_mode == PIN_FALLING) && (status == PCF_PIN_FALLED)))) {
      handler_info.handler();
    }
  }
}

uint8_t PcfRemoteIO::getPin() {
  return this->pin;
}

bool PcfRemoteIO::isInput() {
  return ((this->mode == PIN_INPUT) || (this->mode == PIN_INPUT_PULLUP));
}
