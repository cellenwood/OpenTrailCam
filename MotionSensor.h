#ifndef MOTION_SENSOR
#define MOTION_SENSOR

#include "Arduino.h"
#include "EspConstants.h"

class MotionSensor {
  public:
    void WaitForMotion();
};

#endif
