#ifndef _PLANT_h
#define _PLANT_h
#include <Arduino.h>
#include "MoistureSensor.h"
#include "Face.h"
enum MessageType {
  HELLO,
  GOODBYE,
  THANKS,
  LEVELUP,
  HELLOMASTER,
  SLEEP,
  NUM_MESSAGES
};

class Plant {
public:
  Plant(MoistureSensor& moistureSensor, Face& face);
  void levelUp();
  void checkInteraction(int gesture);
  int getLevel();
  void setLevel(int level);
  int getHappiness();
  void setHappiness(int happiness);
  String getMessage();
  String getMessages(int index);
  String say(MessageType type, unsigned long currentTime);
  void setTimeOfMessage(unsigned long timeOfMessage);
  unsigned long getTimeOfMessage();
  unsigned long getTimeSinceWatering(unsigned long time);
  void setTimeSinceWatering(unsigned long timeSinceWatering);
  unsigned long getTimeOfWatering();
  void setTimeOfWatering(unsigned long timeOfWatering);
  void setMessage(String message);
  void updateLastWatering();
  int parseLastWatering();
  unsigned long getLastWatering();
  bool checkWatering(unsigned long currentTime);
  void checkMessageExpired(unsigned long currentTime);
  Face getFace();
  void checkFace(unsigned long currentTime, int moisture);
  
 

private:
  MoistureSensor _moistureSensor;
  Face _face;
  bool cooldown();
  int _level;
  int _happiness;
  int _happinessThreshold;
  int _lastMoisture;
  unsigned long _lastWatering;
  unsigned long _lastInteraction;
  unsigned long _timeOfWatering;
  unsigned long _timeSinceWatering;
  unsigned long _lastWateringCheck;
  unsigned long _wateringCooldown;
  unsigned long _currentTime;
  unsigned long _timeOfMessage;
  String _message;
  static const char* _messages[];

};

#endif