#include "SDCard.h"

SDCard::SDCard(int csPin) : _csPin(csPin) {}

void SDCard::begin() {
  if (!SD.begin(_csPin)) {
    Serial.println("Card initialization failed!");
    return;
  }
  Serial.println("SD Card Initialized");
}

void SDCard::writeFile(const char* path, const char* message) {
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

String SDCard::readFile(const char* path) {
  File file = SD.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("Failed to open file for reading");
    return String();
  }
  String fileContent;
  while (file.available()) {
    fileContent += char(file.read());
  }
  file.close();
  return fileContent;
}
