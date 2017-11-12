#include "PcfRemoteIO.h"


PcfRemoteIO::PcfRemoteIO(uint8_t pin, PCF857x *pcf) :
  pin(pin), pcf(pcf), mode(PCF_PIN_MODE_INVALID) {}

bool PcfRemoteIO::read() {
  return (pcf->read(this->pin) > 0);
}

void PcfRemoteIO::set(bool val) {
  if(this->mode == PCF_PIN_MODE_OUTPUT) {
    pcf->write(this->pin, val?1:0);
  }
}

void PcfRemoteIO::setMode(uint8_t mode) {
  switch(mode) {
    case PCF_PIN_MODE_INVALID:
    {
      this->mode = PCF_PIN_MODE_INVALID;
      break;
    }

    case PCF_PIN_MODE_INPUT:
    {
      this->mode = PCF_PIN_MODE_INPUT;
      pcf->write(this->pin, 1);
      break;
    }

    case PCF_PIN_MODE_OUTPUT:
    {
      this->mode = PCF_PIN_MODE_OUTPUT;
      break;
    }

    default:
    {
      this->mode = PCF_PIN_MODE_INVALID;
      break;
    }
  }
}
