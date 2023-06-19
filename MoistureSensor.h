#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include <Arduino.h>
class MoistureSensor {
  private:
    int _sensorPin;
    int _moisture;
    unsigned long _lastUpdate;
    unsigned long _currentTime;

  public:
    int readMoisture();
    MoistureSensor(int pin);
    int getMoistureLevel(unsigned long currentTime);
};

#endif // MOISTURESENSOR_H