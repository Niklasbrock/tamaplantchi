#include <Arduino.h>
class MoistureSensor {
  private:
    int _sensorPin;
    int _moisture;
    unsigned long _lastUpdate;
    unsigned long _currentTime;
    int readMoisture();

  public:
    MoistureSensor(int pin);
    int getMoistureLevel(unsigned long currentTime);
};