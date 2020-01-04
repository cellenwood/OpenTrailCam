#ifndef STORAGE
#define STORAGE

#define EEPROM_SIZE 10 //max file count size

#include "Arduino.h"
#include "FS.h"        // SD Card ESP32
#include "SD_MMC.h"    // SD Card ESP32
#include "EEPROM.h"    // read and write from flash memory

class Storage {
    private:
        int file_number = 0;
        String GetNewFileName(String rootFileName, String extension);
    public:
        void Initialize();
        void Save(String rootFileName, String extension, uint8_t* data, size_t length);
};

#endif