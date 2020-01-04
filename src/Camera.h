#ifndef CAMERA
#define CAMERA

#include "Arduino.h"
#include "EspConstants.h"
#include "driver/rtc_io.h"
#include "esp_camera.h"

typedef camera_fb_t picture;

class Camera {
    private:
        void TurnOffFlash();
    public:
        void Initialize();
        picture* TakePicture();
        void Release(picture* picture);
};

#endif