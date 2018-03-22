#include "PCF857xInt.h"


PCF857xInt::PCF857xInt(
  uint8_t address, TwoWire* UseWire, ArduinoIO& interrupt_pin, bool is8575
): PCF857x(address, UseWire, is8575), interrupt_pin(interrupt_pin) {
  // Initialise interrupt handle data
  this->int_data = this->_data;

  // Register interrupt handler
  auto bound_member_fn = std::bind (&PCF857xInt::interruptHandler, this);
  this->interrupt_pin.attachInterruptHandler(bound_member_fn, PIN_CHANGE);
}

void PCF857xInt::begin(uint16_t defaultValues) {
  PCF857x::begin(defaultValues);

  // Initialise interrupt handle data
  this->int_data = this->_data;
}

void PCF857xInt::registerIo(PcfIoEventHandler* io) {
  this->io_list.push_back(io);
}

void PCF857xInt::unregisterIo(PcfIoEventHandler* io) {
  this->io_list.remove(io);
}

void PCF857xInt::interruptHandler() {
  uint16_t previous_data = this->int_data;
  uint16_t new_data;
  uint8_t nb_pin;

  if(this->_is8575) {
    new_data = this->read16();
  } else {
    new_data = this->read8();
  }

  for(PcfIoEventHandler* io : this->io_list) {
    if(io == nullptr) {
      continue;
    }
    if(!io->isInput()) {
      continue;
    }

    uint8_t pin = io->getPin();
    uint16_t old_val = (previous_data & (1u << pin)) >> pin;
    uint16_t new_val = (new_data & (1u << pin)) >> pin;
    if(old_val != new_val) {
      io->interruptHandler((new_val > 0u) ? PcfIoEventHandler::PCF_PIN_RISED : PcfIoEventHandler::PCF_PIN_FALLED);
    }
  }

  // Update interrupt handler data
  this->int_data = new_data;
}
