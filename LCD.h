#ifndef _LCD_h
#define _LCD_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Button.h"

class LCD : public LiquidCrystal {
  public:
    LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, Button& button);
    void displayCustomCharacters();
    void updateDisplay(int progress, String message, int level, unsigned long timeSinceWatering, unsigned long currentTime);
    void setButton(Button& button);
    void setPageSelect(int page);
    int getPageSelect();
    Button& getButton();

  private:
    void createCustomCharacters();
    void setProgressBar(int progress);
    void setLevel(int level);
    void updateTimeSinceWatering(unsigned long timeSinceWatering);
    void setMessage(String message);
    void clearRow(int row);
    int _pageSelect;
    int _maxProgress;
    unsigned long _currentTime;
    unsigned long _lastUpdate;
    unsigned long _lastScrollTime;
    int _scrollPosition;
    const int _lcdColumns = 16;
    const int _scrollSpeed = 200; 
    Button& _button;
};

extern byte box[8];
extern byte verticalBorder[8];
extern byte endBorder[8];
extern byte startBorder[8];
extern byte clock[8];
extern byte waterDroplet[8];

#endif
