#include "Arduino.h"
#include "driver/rtc_io.h"
#include "MotionSensor.h"
#include "Camera.h"
#include "PictureRepo.h"
#include "EspConstants.h"
 
RTC_DATA_ATTR int bootCount = 0;

MotionSensor motionSensor;
Camera camera;
PictureRepo repo;

#define uS_TO_S_FACTOR 1000000
  
void setup() {
  InitializeSerial(115200);
  motionSensor.Initialize();
  camera.Initialize();
  repo.Initialize();
}

void InitializeSerial(unsigned long speed) {
  Serial.begin(speed);
  Serial.setDebugOutput(true);
}
 
void loop() {
  picture* picture = camera.TakePicture();
  repo.SavePictureToSSD("picture", ".jpg", picture->buf, picture->len);
  repo.SendPictureToHost(picture->buf, picture->len);
  camera.Release(picture);
  motionSensor.WaitForMotion();
}
