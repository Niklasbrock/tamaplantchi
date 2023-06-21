#include "Face.h"

Face::Face(int DIN_PIN, int CLK_PIN, int CS_PIN): display(DIN_PIN, CLK_PIN, CS_PIN){
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
  _currentTime = millis();
  _lastUpdate = 0;
}

void Face::displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

void Face::defineMood(int happiness, int moisture, unsigned long currentTime) {
    _currentTime = currentTime;
    if(_currentTime - _lastUpdate > 1000 || _currentTime < _lastUpdate){
    _lastUpdate = _currentTime;
    // Serial.print("Changing Face with values: ");
    // Serial.print(happiness);
    // Serial.print(" ");
    // Serial.println(moisture);
    if (happiness >= 70 && moisture >= 3 && moisture <= 6) {
      expression("happy");
    } else if (happiness < 70 && happiness >= 50 && moisture >= 2 && moisture <= 5) {
      expression("default");
    } else if (happiness <= 30 && moisture >= 2 && moisture <= 4) {
      expression("bored");
    } else if (happiness <= 10 && moisture == 3 || moisture == 4) {
      expression("upset");
    } else if (moisture == 0) {
      expression("dead");
    } else if (moisture == 7) {
      expression("drown");
    } else if (moisture >= 5) {
      expression("cry");
    } else if (happiness <= 10) {
      expression("angry");
    } else {
      expression("default");
    }
  }
}

bool Face::isSleeping(){
  return _sleeping;
}
void Face::setSleeping(bool sleeping){
  _sleeping = sleeping;
}

void Face::expression(String expression) {
  // Serial.println("Setting expression to: " + expression);
  if (expression == "happy") {
    displayImage(IMAGES[0]);
  } else if (expression == "default") {
    displayImage(IMAGES[1]);
  } else if (expression == "bored") {
    displayImage(IMAGES[2]);
  } else if (expression == "upset") {
    displayImage(IMAGES[3]);
  } else if (expression == "cry") {
    displayImage(IMAGES[4]);
  } else if (expression == "dead") {
    displayImage(IMAGES[5]);
  } else if (expression == "drown") {
    displayImage(IMAGES[6]);
  } else if (expression == "angry") {
    displayImage(IMAGES[7]);
  } else if (expression == "sleepy") {
    displayImage(IMAGES[8]);
  }
}
