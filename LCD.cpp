#include "LCD.h"
#include "Button.h"
LCD::LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, Button& button)
  : LiquidCrystal(rs, enable, d0, d1, d2, d3), _button(button) {
  createCustomCharacters();
//   Set the max length of the progress bar
  _maxProgress = 6;
  _lastUpdate = 0;
  // Scrolling variables
  _lastScrollTime = 0;
  _scrollPosition = _lcdColumns;
  _currentTime = millis();
}

void LCD::updateDisplay(int progress, String message, int level, unsigned long currentTime){
  _currentTime = currentTime;
  if(_currentTime - _lastUpdate > 1000 || _currentTime < _lastUpdate){
    _lastUpdate = _currentTime;
    // TODO, change this clear to only clear the button row
    clear();
    setProgressBar(progress);
    setLevel(level);
    if(message.length() <= 15){
      setMessage(message);
    }
  }
  if(message.length() > 15){
    setMessage(message);
  }
}

void LCD::createCustomCharacters() {
  createChar(0, box);
  createChar(1, verticalBorder);
  createChar(2, endBorder);
  createChar(3, startBorder);
}

void LCD::displayCustomCharacters() {
  //TODO Implement custom display logic here
}

void LCD::setProgressBar(int progress) {
  setCursor(10, 1);
  if (progress < 0 or progress > _maxProgress) {
    return;
  } else if (progress == 0) {
      write((byte)3);
      for (int i = 0; i < _maxProgress - 2; i++) {
        write((byte)1);
    }
    write((byte)2);
  } else if (progress == _maxProgress) {
      for (int i = 0; i < progress; i++) {
        write((byte)0);
      }
  } else {
      for (int i = 0; i < progress; i++) {
        write((byte)0);
      }
    for (int i = 0; i < _maxProgress - progress - 1; i++) {
      write((byte)1);
    }
    write((byte)2);
  }
}
void LCD::setLevel(int level){
  setCursor(0,1);
  print("Lvl");
  setCursor(4, 1);
  print(level);
  //TODO Add a arrow up or down to indicate if lvl is increasing or decreasing
}
void LCD::setMessage(String message){
  if(message.length() < _lcdColumns){
    setCursor(0,0);
    print(message);
  } else{
      if (_currentTime - _lastScrollTime >= _scrollSpeed) { // scroll every 200ms
        _lastScrollTime = _currentTime;
        
        for (int i = 0; i < _lcdColumns; i++) {
          int charIndex = (_scrollPosition + i) % message.length();
          setCursor(i, 0);
          print(message.charAt(charIndex));
        }
        _scrollPosition++;
        if (_scrollPosition >= message.length()) {
          _scrollPosition = 0;
        }
      }
    }
}

void LCD::setButton(Button button){
  _button = button;
}

byte box[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte verticalBorder[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

byte endBorder[8] = {
  0b11111,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b11111
};

byte startBorder[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};
