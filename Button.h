#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
class Button{
  public:
    Button(int pin);
    void press();
    bool isPressed();
    bool checkPress(unsigned long currentTime);
  private:
    int _pin;
    bool _state;
    bool _lastState;
    unsigned long _lastUpdate;
    unsigned long _currentTime;
};

#endif // BUTTON_H