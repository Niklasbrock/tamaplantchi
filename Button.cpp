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
bool Button::checkPress(unsigned long currentTime){
  // Logic, with millis(), to check whether button is pressed.
  _currentTime = currentTime;
  if(_currentTime - _lastUpdate > 150 || _currentTime < _lastUpdate){
    _lastUpdate = _currentTime;
    if(digitalRead(_pin) == LOW){
      return true;
    }
  }
  return false;
}