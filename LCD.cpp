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
  _currentTime = 0;
  // Set the starting screen to first
  _pageSelect = 1;
}

#define CHECK_INTERVAL 500 // define check interval in milliseconds

void LCD::updateDisplay(int progress, String message, int level, unsigned long timeSinceWatering, unsigned long currentTime){
  _currentTime = currentTime;
  if(_currentTime - _lastUpdate > CHECK_INTERVAL || _currentTime < _lastUpdate){
    _lastUpdate = _currentTime;
    clearRow(1);
    setProgressBar(progress);
    if (_button.isPressed()){
      updateTimeSinceWatering(timeSinceWatering);
    } else{
      setLevel(level);
    }
    if(message.length() <= 15){
      clearRow(0);
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
  createChar(4, clock);
  createChar(5, waterDroplet);
}

void LCD::displayCustomCharacters() {
  //TODO Implement custom display logic here
}

void LCD::setProgressBar(int progress) {
  setCursor(9, 1);
  write((byte)5);
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


void LCD::updateTimeSinceWatering(unsigned long timeSinceWatering){
  // Convert milliseconds to seconds
  unsigned long totalSeconds = timeSinceWatering / 1000;
  // Calculate days, hours, minutes
  unsigned long days = totalSeconds / 86400;  //60 * 60 * 24
  unsigned long hours = (totalSeconds % 86400) / 3600;  //60 * 60
  // unsigned long minutes = (totalSeconds % 3600) / 60;
  // Print the results
  setCursor(0,1);
  write((byte)4);
  print(days);
  print("d ");
  print(hours);
  print("h");
  // print(minutes);
  // print("m");
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

void LCD::clearRow(int row) {
  setCursor(0, row);
  for (int i = 0; i < _lcdColumns; i++) {
    print(" ");
  }
}

void LCD::setButton(Button& button){
  _button = button;
}

Button& LCD::getButton(){
  return _button;
}
void LCD::setPageSelect(int page){
  _pageSelect = page;
}

int LCD::getPageSelect(){
  return _pageSelect;
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

byte clock[8] = {
  0b00000,
  0b01110,
  0b10101,
  0b10111,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};

byte waterDroplet[8] = {
  0b00000,
  0b00100,
  0b00100,
  0b01010,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};