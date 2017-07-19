#include "PcfRemoteIO.h"


PcfRemoteIO::PcfRemoteIO(uint8_t pin, PCF857x *pcf) : pin(pin), pcf(pcf) {}

bool PcfRemoteIO::read() {
  return (pcf->read(this->pin) > 0);
}

void PcfRemoteIO::set(bool val) {
  pcf->write(this->pin, val?1:0);
}

void PcfRemoteIO::setMode(uint8_t mode) {
  // NOP
}
