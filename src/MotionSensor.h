#ifndef MOTION_SENSOR
#define MOTION_SENSOR

#include "Arduino.h"
#include "EspConstants.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

class MotionSensor {
  public:
    void Initialize();
    void WaitForMotion();
};

#endif
