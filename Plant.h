#ifndef _PLANT_h
#define _PLANT_h
#include <Arduino.h>
#include "MoistureSensor.h"

enum MessageType {
  HELLO,
  GOODBYE,
  THANKS,
  LEVELUP,
  NUM_MESSAGES
};

class Plant {
public:
  Plant(MoistureSensor& moistureSensor);
  void updateHappiness(); 
  void levelUp();
  void checkInteraction(int gesture);
  int getLevel();
  void setLevel(int level);
  int getHappiness();
  String getMessage();
  String say(MessageType type) const;
  unsigned long getTimeSinceWatering(unsigned long time);
  void setTimeSinceWatering(unsigned long timeSinceWatering);
  unsigned long getTimeOfWatering();
  void setTimeOfWatering(unsigned long timeOfWatering);
  void setMessage(String message);
  void updateLastWatering();
  int parseLastWatering();
  unsigned long getLastWatering();
  bool checkWatering(unsigned long currentTime);

private:
  MoistureSensor _moistureSensor;
  int _level;
  int _happiness;
  int _happinessThreshold;
  int _lastMoisture;
  unsigned long _lastWatering;
  unsigned long _lastInteraction;
  unsigned long _timeOfWatering;
  unsigned long _timeSinceWatering;
  unsigned long _offsetTime;
  unsigned long _lastWateringCheck;
  unsigned long _currentTime;
  String _message;
  static const char* _messages[];
};

#endif