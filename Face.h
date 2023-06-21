#ifndef FACE_H
#define FACE_H

#include <LedControl.h>

class Face {
  public:
    Face(int dinPin, int csPin, int clkPin);
    void defineMood(int happiness, int moisture, unsigned long currentTime);
    bool isSleeping();
    void setSleeping(bool sleeping);
    void expression(String expression);
  
  private:
    LedControl display;
    const uint64_t IMAGES[9] = {
      0x1020140202142010,
      0x0000340202340000,
      0x8050920202121000,
      0x0050320404325000,
      0x2038220404223820,
      0x5020530505532050,
      0x1f3f163d1d361f3f,
      0x4020130505132040,
      0x40c09030290d0b09
    };
    const int IMAGES_LEN = sizeof(IMAGES) / sizeof(uint64_t);
    void displayImage(uint64_t image);
    bool _sleeping;
    unsigned long _currentTime;
    unsigned long _lastUpdate;
    const uint64_t WATERING_ANIMATION[10] = {
      0x0000000000000000,
      0x5500000000000000,
      0xffaa000000000000,
      0xffff550000000000,
      0xffffffaa00000000,
      0xffffffff55000000,
      0xffffffffff550000,
      0xffffffffffffaa00,
      0xffffffffffffff55,
      0xffffffffffffffff
    };
    const int WATERING_ANIMATION_LEN = sizeof(WATERING_ANIMATION) / sizeof(uint64_t);
};

#endif
