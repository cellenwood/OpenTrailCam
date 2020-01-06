#ifndef PICTURE_REPO
#define PICTURE_REPO

#define EEPROM_SIZE 1 //max file count size

#include "Arduino.h"

//SD Card
#include "FS.h"
#include "SD_MMC.h"

//Flash Memory
#include "EEPROM.h"

//Wifi
#include "WiFi.h"
#include "WiFiMulti.h"
#include "HTTPClient.h"

typedef uint8_t* PictureData;

class PictureRepo {
    private:
        String GetNewFileName(String rootFileName, String extension);
    public:
        void Initialize();
        void SavePictureToSSD(String rootFileName, String extension, PictureData data, size_t length);
        void SendPictureToHost(PictureData data, size_t length);
};

#endif