#include "Plant.h"
#include "LCD.h"
#include "MoistureSensor.h"
#include "Button.h"
#include "SDCard.h"

// Defining the pins
#define MOISTURE_PIN A0
const uint8_t rs = 4, enable = 6, d0 = 10, d1 = 11, d2 = 12, d3 = 13;

#define HAPPINESS_THRESHOLD 100
#define BUTTON_PIN 9
#define SDCARD_PIN 8

// Call constructors
Button button(BUTTON_PIN);
Plant plant(HAPPINESS_THRESHOLD);
LCD lcd(rs, enable, d0, d1, d2, d3, button);
MoistureSensor moistureSensor(MOISTURE_PIN);
SDCard sdCard(SDCARD_PIN);

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
  // Create the custom character at location 0
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  sdCard.begin();
  sdCard.writeFile("/test.txt", "Hello, world!");
}

void loop() {
  unsigned long currentTime = millis();
  if(button.checkPress(currentTime)){
    Serial.println("Button pressed");
  }
  lcd.updateDisplay(moistureSensor.getMoistureLevel(currentTime), plant.say(THANKS), plant.getLevel(), currentTime);
  // String content = sdCard.readFile("/test.txt"); // Read from file
  // Serial.println(content);
}
