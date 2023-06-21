#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int trigPin, int echoPin, unsigned short maxDistanceCm, unsigned long absoluteTimeout)
    : UltraSonicDistanceSensor(trigPin, echoPin, maxDistanceCm, absoluteTimeout) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _maxDistanceCm = maxDistanceCm;
    _absoluteTimeout = absoluteTimeout;
    _distance = 0;
    _lastWaveTime = 0;
    _lastCheckTime = 0;
    _checkCooldown = 0;
}

int DistanceSensor::getDistance() {
  return _distance;
}

bool DistanceSensor::checkHumanDetection(unsigned long measureTime) {
    // If 5 seconds haven't passed since the last wave, do nothing.
    if (measureTime - _lastWaveTime < _checkCooldown) {
        return false;
    }
    // If x milliseconds have passed since the last distance check, update the distance.
    if (measureTime - _lastCheckTime >= checkInterval) {
        _lastCheckTime = measureTime;
        unsigned short newDistance = measureDistanceCm(26);
        Serial.print("Distance: ");
        Serial.println(newDistance);
        // If the new distance is closer than threshold
        if (newDistance < distanceThreshold) {
            // Update the distance in the array.
            _lastDistances[_waveCount] = newDistance;
            // Increase the wave count.
            _waveCount++;
        } else {
            // If the new distance is not closer than the threshold, reset the wave count and the distances.
            _waveCount = 0;
            for (int i = 0; i < 4; i++) {
                _lastDistances[i] = newDistance;
            }
        }

        // If 4 waves have been detected.
        if (_waveCount == 4) {
            // Reset the wave count and update the time of the last wave.
            _waveCount = 0;
            _lastWaveTime = measureTime;
            _checkCooldown = 60000; 
            return true;
        }
    }

    return false;
}