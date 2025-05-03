#include "ph_sensor.h"
#include <Arduino.h>

PHSensor::PHSensor(int analogPin) {
  _analogPin = analogPin;
}

void PHSensor::begin() {
  // Initialize sensor if needed
}

float PHSensor::readPH() {
  int adcValue = analogRead(_analogPin);
  float voltage = (adcValue / 4095.0) * 3.3; // For 12-bit ADC ESP32
  return _voltageToPH(voltage);
}

float PHSensor::_voltageToPH(float voltage) {
  // Example calibration equation, adjust based on your sensor
  float slope = -5.70;
  float intercept = 21.34;
  return slope * voltage + intercept;
}
