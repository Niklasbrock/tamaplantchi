#ifndef FACE_H
#define FACE_H

#include <LedControl.h>

class Face {
  public:
    Face(int dinPin, int csPin, int clkPin);
    void defineMood(int happiness, int moisture, unsigned long currentTime);
  
  private:
  LedControl display;
    const uint64_t IMAGES[8] = {
      0x1020140202142010,
      0x0000340202340000,
      0x8050920202121000,
      0x0050320404325000,
      0x2038220404223820,
      0x5020530505532050,
      0x1f3f163d1d361f3f,
      0x4020130505132040
    };
    const int IMAGES_LEN = sizeof(IMAGES) / 8;
    void displayImage(uint64_t image);
    void expression(String expression);
    unsigned long _currentTime;
    unsigned long _lastUpdate;

};

#endif
