# 1 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino"
# 2 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 3 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 4 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 5 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 6 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 7 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 8 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2
# 9 "c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino" 2

__attribute__((section(".rtc.data"))) int bootCount = 0;

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
  ({ do { if (__builtin_constant_p(!(((((0x3ff48000 + 0xd4))) >= 0x3ff00000) && (((0x3ff48000 + 0xd4))) <= 0x3ff13FFC)) && !(!(((((0x3ff48000 + 0xd4))) >= 0x3ff00000) && (((0x3ff48000 + 0xd4))) <= 0x3ff13FFC))) { extern __attribute__((error("(Cannot use WRITE_PERI_REG for DPORT registers use DPORT_WRITE_PERI_REG)"))) void failed_compile_time_assert(void); failed_compile_time_assert(); } (("(Cannot use WRITE_PERI_REG for DPORT registers use DPORT_WRITE_PERI_REG)" && (!(((((0x3ff48000 + 0xd4))) >= 0x3ff00000) && (((0x3ff48000 + 0xd4))) <= 0x3ff13FFC))) ? (void)0 : __assert_func ("c:\\Users\\fun2x\\Documents\\Arduino\\TrailCam\\TrailCam.ino", 26, __PRETTY_FUNCTION__, "\"(Cannot use WRITE_PERI_REG for DPORT registers use DPORT_WRITE_PERI_REG)\" && (!(((((0x3ff48000 + 0xd4))) >= 0x3ff00000) && (((0x3ff48000 + 0xd4))) <= 0x3ff13FFC))")); } while(0);; (*((volatile uint32_t *)((0x3ff48000 + 0xd4)))) = (uint32_t)(0); });
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
