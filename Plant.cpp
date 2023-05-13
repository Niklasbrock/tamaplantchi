#include "Plant.h"

const char* Plant::_messages[] = {
    "Hello!",
    "Goodbye!",
    "Thank you for watering me!",
    "I just leveled up to level %LEVEL%!"
    // Add more messages as needed
};

Plant::Plant(MoistureSensor& moistureSensor)
  : _moistureSensor(moistureSensor) {
  _level = 2;
  _happiness = 0;
  _lastInteraction = millis();
  _timeSinceWatering = 0;
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

unsigned long Plant::getTimeSinceWatering() {
  return _timeSinceWatering;
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