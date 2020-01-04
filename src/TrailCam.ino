#include "Arduino.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"
#include "MotionSensor.h"
#include "Camera.h"
#include "Storage.h"
#include "EspConstants.h"
 
RTC_DATA_ATTR int bootCount = 0;

MotionSensor motionSensor;
Camera camera;
Storage storage;

#define uS_TO_S_FACTOR 1000000
  
void setup() {
  DisableBrownOutDetector();
  InitializeSerial(115200);
  camera.Initialize();
  storage.Initialize();
} 

void DisableBrownOutDetector(){
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void InitializeSerial(unsigned long speed) {
  Serial.begin(speed);
  Serial.setDebugOutput(true);
}
 
void loop() {
  picture* picture = camera.TakePicture();
  storage.Save("picture", ".jpg", picture->buf, picture->len);
  camera.Release(picture);
  motionSensor.WaitForMotion();
}
