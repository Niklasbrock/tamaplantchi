#include "Plant.h"
#include "LCD.h"
#include "MoistureSensor.h"
#include "Button.h"
#include "SDCard.h"
#include "Face.h"

// Defining the pins
const uint8_t rs = 4, enable = 6, d0 = 10, d1 = 11, d2 = 12, d3 = 13;
#define MOISTURE_PIN A0
#define HAPPINESS_THRESHOLD 100
#define BUTTON_PIN 9
#define SDCARD_PIN 8
#define FACE_DIN_PIN 2
#define FACE_CS_PIN 3
#define FACE_CLK_PIN 5

// Call constructors
Button button(BUTTON_PIN);
MoistureSensor moistureSensor(MOISTURE_PIN);
Plant plant(moistureSensor);
LCD lcd(rs, enable, d0, d1, d2, d3, button);
SDCard sdCard(SDCARD_PIN);
Face face(FACE_DIN_PIN, FACE_CLK_PIN, FACE_CS_PIN);

// Commands
String inputString;

// Time management
unsigned long timeOffset = 0;

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
  unsigned long time = millis() + timeOffset;
  // Check for button press and change pageSelect variable on press
  if(lcd.getButton().checkPress(millis())){
    Serial.println("Button pressed");
    lcd.getButton().press();
  }
  unsigned long displayTime = millis();
  // Check if the plant has been watered. On success waits 5 min before checking again.
  if(plant.checkWatering(time)){
    // set the message to Thank you for watering me!
    plant.setMessage(plant.say(THANKS));
  }
  // Updates the display
  lcd.updateDisplay(moistureSensor.getMoistureLevel(time), plant.getMessage(), plant.getLevel(), plant.getTimeSinceWatering(time), time);
  face.defineMood(plant.getHappiness(), moistureSensor.getMoistureLevel(time), time);
  // String content = sdCard.readFile("/test.txt"); // Read from file
  // Serial.println(content);

  // Command logic
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();

    if (inChar == '\n') {
      int separatorIndex = inputString.indexOf('[');
      int endIndex = inputString.indexOf(']');
      String command = inputString.substring(0, separatorIndex);
      if (command == "watertime") {
        unsigned long value = inputString.substring(separatorIndex+1, endIndex).toInt();
        plant.setTimeOfWatering(value);
      }
      if (command == "time") {
        unsigned long value = inputString.substring(separatorIndex+1, endIndex).toInt();
        timeOffset = value;
      }
      if (command == "lvl") {
        int value = inputString.substring(separatorIndex+1, endIndex).toInt();
        plant.setLevel(value);
      }
      if (command == "say") {
        String value = inputString.substring(separatorIndex+1, endIndex);
        plant.setMessage(value);
      }

      inputString = "";
    } else {
      inputString += inChar;
    }
  }
}
