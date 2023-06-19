#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int sensorPin)
  : _sensorPin(sensorPin){
    _moisture = 0;
    _lastUpdate = 0;
    _currentTime = 0;
  }

int MoistureSensor::readMoisture(){
  return analogRead(_sensorPin);
}

int MoistureSensor::getMoistureLevel(unsigned long currentTime){
  _currentTime = currentTime;

  if(_currentTime - _lastUpdate > 1000 || _currentTime < _lastUpdate){
    _moisture = readMoisture();
    _lastUpdate = _currentTime;
    Serial.println(_moisture);
    if(_moisture > 950){
      _moisture = 0;
    } else if (_moisture > 850){
        _moisture = 1;
    } else if (_moisture > 750){
        _moisture = 2;
    } else if (_moisture > 650){
        _moisture = 3;
    } else if (_moisture > 550){
        _moisture = 4;
    } else if (_moisture > 450){
        _moisture = 5;
    } else if (_moisture > 350){
        _moisture = 6;
    } else {
        _moisture = 7;
    }
  }
  return _moisture;
}