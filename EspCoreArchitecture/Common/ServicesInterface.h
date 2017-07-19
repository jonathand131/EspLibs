#ifndef __SERVICES_INTERFACE_H__
#define __SERVICES_INTERFACE_H__

#include "CommonInterface.h"


class ServicesInterface : public CommonInterface {
public:
  virtual void init() = 0;
};

#endif  // __SERVICES_INTERFACE_H__
