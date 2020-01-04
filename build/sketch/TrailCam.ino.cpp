#line 1 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
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
  
#line 18 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
void setup();
#line 25 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
void DisableBrownOutDetector();
#line 29 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
void InitializeSerial(unsigned long speed);
#line 34 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
void loop();
#line 18 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
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
  camera_fb_t* picture = camera.TakePicture();
  storage.Save(picture->buf, picture->len);
  camera.Release(picture);
  motionSensor.WaitForMotion();
}

