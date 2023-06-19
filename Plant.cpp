#include "Plant.h"

const char* Plant::_messages[] = {
    "Hello!",
    "Goodbye!",
    "Thank you for watering me! ",
    "I just leveled up to level %LEVEL%! "
    // Add more messages as needed
};

Plant::Plant(MoistureSensor& moistureSensor)
  : _moistureSensor(moistureSensor) {
  _level = 2;
  _happiness = 70;
  _lastInteraction = 0;
  _timeOfWatering = 0;
  _offsetTime = 0; // Two days in milliseconds
  _lastWateringCheck = 0;
  _currentTime = 0;
  _lastMoisture = 0;
  _message = _messages[0];
}

void Plant::updateHappiness(){
  
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

String Plant::say(MessageType type) const {
  if (type >= 0 && type < NUM_MESSAGES) {
        String message = _messages[type];
        // If variables needs to be changed in the message, it is done here
        message.replace("%LEVEL%", String(_level));
        return message;
    } else {
        return "Message not found.";
    }
}

// TODO the time in this is buggy. Does not check again after 5 min. FIX
bool Plant::checkWatering(unsigned long currentTime){
  _currentTime = currentTime;
  // Make it check less, only once per second and if a watering has been detected, wait 5 min before checking again.
  if(_currentTime - _lastWateringCheck > 1000 && _currentTime - _lastWateringCheck < 1020 || _currentTime < _lastWateringCheck && _currentTime - _lastWateringCheck < 1020){
    Serial.print("Result of Time difference: ");
    Serial.println(_currentTime - _lastWateringCheck);
    _lastWateringCheck = _currentTime;
    int moisture = _moistureSensor.readMoisture();
    Serial.print("Water Check Moisture: ");
    Serial.println(moisture);
    Serial.print("Last Moisture: ");
    Serial.println(_lastMoisture);
    // If moisture decreases by more than 100 since last check and is lower than 750. Also waits for 5 sec after startup has passed
    if(moisture <= 750 && _lastMoisture - moisture > 100 && _currentTime > 5 * 1000){
      Serial.print("Result: ");
      Serial.println(moisture - _lastMoisture);
      _lastMoisture = moisture;
      // Set a grace time period so it won't check again for 5 min
      _lastWateringCheck = _currentTime + (5 * 60 * 1000); // Add grace period
      _timeOfWatering = _currentTime;
      Serial.println("Watering Detected");
      return true;
    }
    _lastMoisture = moisture;
  }
  return false;
}

unsigned long Plant::getTimeOfWatering() {
  return _timeOfWatering;
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