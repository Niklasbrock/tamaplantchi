#include "Plant.h"
#include "LCD.h"
#include "MoistureSensor.h"
#include "Button.h"
#include "SDCard.h"
#include "Face.h"
#include "DistanceSensor.h"

// Defining the pins
const uint8_t rs = 4, enable = 6, d0 = 10, d1 = 11, d2 = 12, d3 = 13;
#define MOISTURE_PIN A15
#define BUTTON_PIN 9
#define SDCARD_PIN 8
#define FACE_DIN_PIN 2
#define FACE_CS_PIN 3
#define FACE_CLK_PIN 5
#define DISTANCE_ECHO_PIN 31
#define DISTANCE_TRIG_PIN 30

// Call constructors
Button button(BUTTON_PIN);
Face face(FACE_DIN_PIN, FACE_CLK_PIN, FACE_CS_PIN);
MoistureSensor moistureSensor(MOISTURE_PIN);
DistanceSensor distanceSensor(DISTANCE_TRIG_PIN, DISTANCE_ECHO_PIN, 150, 0);
Plant plant(moistureSensor, face);
LCD lcd(rs, enable, d0, d1, d2, d3, button);
SDCard sdCard(SDCARD_PIN);

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
  // Set the starting message to default sleeping message
}

void loop() {
  unsigned long time = millis() + timeOffset;
  unsigned long measureTime = millis();

  // Check for button press and change pageSelect variable on press
  if(lcd.getButton().checkPress(measureTime)){
    Serial.println("Button pressed");
    lcd.getButton().press();
    if(plant.getFace().isSleeping()){
      plant.setMessage(plant.say(HELLO, time));
    }
  }

  // Distance sensor check
  if (distanceSensor.checkHumanDetection(measureTime)) {
    Serial.println("Human detected!");
    plant.levelUp();
    plant.setHappiness(plant.getHappiness() + 20);
    plant.setMessage(plant.say(HELLOMASTER, time));
    // interact with owner or add happiness...
  }

  // Check if the plant has been watered. On success waits 5 min before checking again.
  if(plant.checkWatering(time)){
    // set the message to Thank you for watering me!
    plant.setMessage(plant.say(THANKS, time));
    plant.setHappiness(plant.getHappiness() + 20);
  }

  // Check if a message is expired
  plant.checkMessageExpired(time);

  // Updates the display
  int moistureLevel = moistureSensor.getMoistureLevel(measureTime);
  plant.checkFace(measureTime, moistureLevel);
  lcd.updateDisplay(moistureLevel, plant.getMessage(), plant.getLevel(), plant.getTimeSinceWatering(time), measureTime);
  // plant.getFace().defineMood(plant.getHappiness(), moistureLevel, measureTime);
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
        value = value * 3600000; // Convert hours to milliseconds
        timeOffset = value;
      }
      if (command == "lvl") {
        int value = inputString.substring(separatorIndex+1, endIndex).toInt();
        plant.setLevel(value);
      }
      if (command == "say") {
        String value = inputString.substring(separatorIndex+1, endIndex);
        plant.setTimeOfMessage(time);
        plant.setMessage(value);
      }

      inputString = "";
    } else {
      inputString += inChar;
    }
  }
}
