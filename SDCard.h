#ifndef SDCard_h
#define SDCard_h

#include <Arduino.h>
#include <SD.h>

class SDCard {
  public:
    SDCard(int csPin);
    void begin();
    void writeFile(const char* path, const char* message);
    String readFile(const char* path);
  private:
    int _csPin;
};

#endif
