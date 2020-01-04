#include "MotionSensor.h"

void MotionSensor::Initialize() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void MotionSensor::WaitForMotion() {
  esp_sleep_enable_ext0_wakeup(static_cast<gpio_num_t>(WAKEUP_PIN), 0);
  Serial.println("Waiting for motion");
  esp_deep_sleep_start();
}
