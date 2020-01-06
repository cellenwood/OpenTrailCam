#include "PictureRepo.h"

void PictureRepo::Initialize() {
    EEPROM.begin(EEPROM_SIZE);
}

void PictureRepo::SavePictureToSSD(String rootFileName, String extension, PictureData data, size_t length) {
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

    Serial.println("Saving picture to SSD...");
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

void PictureRepo::SendPictureToHost(PictureData data, size_t length) {
    Serial.println("Attempting to connect to picture server.");

    WiFiMulti connection;
    connection.addAP("SSID", "Password");
    if (connection.run() != WL_CONNECTED) {
        Serial.println("Failed to connect to picture server.");
        return;
    }

    HTTPClient client;
    client.begin("http://my.pictureserver.com");
    int response = client.POST(data, length);
    if (response < 0) { //response negative on error
        Serial.println("Faield to post picture to server.");
    }

    client.end();
}

String PictureRepo::GetNewFileName(String rootFileName, String extension) {
    uint8_t fileNumber = EEPROM.read(0);
    fileNumber++;
    EEPROM.write(0, fileNumber);
    EEPROM.commit();
    
    return "/" + rootFileName + String(fileNumber) + extension;
}