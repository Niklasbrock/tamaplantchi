#include "Button.h"
Button::Button(int pin)
  : _pin(pin) {
    _state = false;
    _lastState = _state;
    _lastUpdate = 0;
    _currentTime = 0;
  }

void Button::press(){
  _state = !_state;
  Serial.print("Button state changed to: ");
  Serial.println(_state);
}
bool Button::isPressed(){
  return _state;
}

#define CHECK_INTERVAL 100 // define check interval in milliseconds

bool Button::checkPress(unsigned long currentTime){
  _currentTime = currentTime;
  
  if (digitalRead(_pin) == LOW) { // Button is pressed
    if (_buttonWasReleased && (_currentTime - _lastUpdateTime > CHECK_INTERVAL)) { // enough time has passed since the last check
      _buttonWasReleased = false; // button is currently pressed
      _lastUpdateTime = _currentTime; // update the last check time
      
      return true; // a button press has occurred
    }
  }
  else { // Button is not pressed
    _buttonWasReleased = true; // button is currently released
  }
  
  return false; // no button press occurred
}

