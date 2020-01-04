#include "Storage.h"

void Storage::Initialize() {
    Serial.println("Starting SD Card");

    if(!SD_MMC.begin()){
        Serial.println("SD Card Mount Failed");
        return;
    }

    uint8_t cardType = SD_MMC.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No SD Card attached");
        return;
    }

    EEPROM.begin(EEPROM_SIZE);
}

void Storage::Save(String rootFileName, String extension, uint8_t* data, size_t length) {
    String path = GetNewFileName(rootFileName, extension);
    
    fs::FS &fs = SD_MMC;
    File file = fs.open(path.c_str(), FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file in writing mode");
        return;
    }

    file.write(data, length);
    file.close();

    Serial.printf("Saved file to path: %s\n", path.c_str());
}

String Storage::GetNewFileName(String rootFileName, String extension) {
    uint8_t fileNumber = EEPROM.read(0);
    fileNumber++;
    EEPROM.write(0, fileNumber);
    EEPROM.commit();
    
    return "/" + rootFileName + String(fileNumber) + extension;
}