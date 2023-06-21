#include "Plant.h"

#define HAPPINESS_THRESHOLD 100

const char* Plant::_messages[] = {
    "Hello!",
    "Goodbye!",
    "Thank you for watering me! ",
    "I just leveled up to level %LEVEL%! ",
    "Hello master! Good to see you! ",
    "zzZZzzZZzzzZZZzzzZZzzzZZzzzZ"
    // Add more messages as needed
};

Plant::Plant(MoistureSensor& moistureSensor, Face& face)
  : _moistureSensor(moistureSensor), _face(face){
  _level = 1;
  _happiness = 10;
  _lastInteraction = 0;
  _timeOfWatering = 0;
  _lastWateringCheck = 0;
  _currentTime = 0;
  _timeOfMessage = 0;
  _lastMoisture = 0;
  _message = _messages[SLEEP];

}

void Plant::levelUp() {
  _level++;
}

void Plant::checkInteraction(int gesture) {
  
}

int Plant::getLevel() {
  return _level;
}

void Plant::setLevel(int level){
  _level = level;
}

int Plant::getHappiness() {
  return _happiness;
}
Face Plant::getFace(){
  return _face;
}

void Plant::setHappiness(int happiness){
  _happiness = happiness;
  if(_happiness > HAPPINESS_THRESHOLD){
    _happiness = HAPPINESS_THRESHOLD;
  }
}
// Take a message type and return the message
String Plant::say(MessageType type, unsigned long currentTime) {
  if (type >= 0 && type < NUM_MESSAGES) {
        String message = _messages[type];
        _message = message;
        // If variables needs to be changed in the message, it is done here
        message.replace("%LEVEL%", String(_level));
        _timeOfMessage = currentTime;
        return message;
    } else {
        return "Message not found.";
    }
}

// a function that checks if a message has been active for more than 10 seconds.
// if it has, it will change the message to the default message
void Plant::checkMessageExpired(unsigned long currentTime){
  if(currentTime - _timeOfMessage > 15000){
    _message = _messages[SLEEP]; // Change to default SLEEP message
  }
}

// a function that matches the Face to the message
void Plant::checkFace(unsigned long currentTime, int moisture){
  if(_message == _messages[SLEEP]){
    _face.setSleeping(true);
    _face.expression("sleepy"); // Change to default SLEEP message
  } else {
    _face.setSleeping(false);
    _face.defineMood(_happiness, moisture, currentTime);
  }
}

bool Plant::checkWatering(unsigned long currentTime){
  _currentTime = currentTime;
  // Make it check less, only once per second
  if(_currentTime - _lastWateringCheck > 1000){
    // Check if the cooldown is over
    if(cooldown()){
      Serial.print("Result of Time difference: ");
      Serial.println(_currentTime - _lastWateringCheck);
      _lastWateringCheck = _currentTime;
      int moisture = _moistureSensor.readMoisture();
      Serial.print("Water Check Moisture: ");
      Serial.println(moisture);
      Serial.print("Last Moisture: ");
      Serial.println(_lastMoisture);
      // If moisture decreases by more than 100 since last check and is lower than 750. Also waits for 5 sec after startup has passed
      if(moisture <= 750 && _lastMoisture - moisture > 100 && _currentTime > 5000){
        Serial.print("Result: ");
        Serial.println(moisture - _lastMoisture);
        _lastMoisture = moisture;
        // Set a grace time period so it won't check again for 5 min
        _wateringCooldown = (300000); // Add grace period 5 * 60 * 1000
        _timeOfWatering = _currentTime;
        Serial.println("Watering Detected");
        return true;
      }
      _lastMoisture = moisture;
    }
    return false;
  }
}

bool Plant::cooldown(){
  if(_currentTime > (_timeOfWatering + _wateringCooldown)){
    return true;
  }
  return false;
}
void Plant::setTimeOfWatering(unsigned long timeOfWatering) {
  _timeOfWatering = timeOfWatering;
}
unsigned long Plant::getTimeSinceWatering(unsigned long time) {
  return time - _timeOfWatering;
}

void Plant::setTimeSinceWatering(unsigned long timeSinceWatering) {
  _timeSinceWatering = timeSinceWatering;
}

String Plant::getMessage() {
  return _message;
}
void Plant::setMessage(String message) {
  _message = message;
}

String Plant::getMessages(int index) {
  return _messages[index];
}

void Plant::setTimeOfMessage(unsigned long timeOfMessage) {
  _timeOfMessage = timeOfMessage;
}