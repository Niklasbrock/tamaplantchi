#ifndef _PLANT_h
#define _PLANT_h
#include <Arduino.h>


enum MessageType {
  HELLO,
  GOODBYE,
  THANKS,
  LEVELUP,
  NUM_MESSAGES
};

class Plant {
public:
  Plant(int happinessThreshold);
  void updateHappiness(); 
  void levelUp();
  void checkInteraction(int gesture);
  int getLevel();
  int getHappiness();
  String getMessage();
  String say(MessageType type) const;
  unsigned long getTimeSinceWatering();
  void setTimeSinceWatering(unsigned long timeSinceWatering);
  void setMessage(String message);
  void updateLastWatering();
  int parseLastWatering();
  unsigned long getLastWatering();

private:
  int _moisturePin;
  int _level;
  int _happiness;
  int _happinessThreshold;
  unsigned long _lastWatering;
  unsigned long _lastInteraction;
  unsigned long _timeSinceWatering;
  String _message;
  static const char* _messages[];
};

#endif