#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>
#include <HCSR04.h>

class DistanceSensor : public UltraSonicDistanceSensor {
  public:
    DistanceSensor(int trigPin, int echoPin, unsigned short maxDistanceCm, unsigned long absoluteTimeout);
    void begin();
    void measureDistance();
    int getDistance();
    bool checkHumanDetection(unsigned long measureTime);

  private:
    unsigned long _lastWaveTime;
    unsigned long _lastCheckTime ;
    int _lastDistances[4] = {0, 0, 0, 0};
    int _waveCount = 0;
    unsigned long _checkCooldown; 
    const unsigned long checkInterval = 400; 
    const unsigned short distanceThreshold = 75;
    int _trigPin;
    int _echoPin;
    long _duration;
    unsigned short _distance;
    unsigned short _maxDistanceCm;
    unsigned long _absoluteTimeout;

};

#endif
