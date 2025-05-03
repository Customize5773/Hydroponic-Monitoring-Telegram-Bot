#include "ec_sensor.h"
#include <Arduino.h>

ECSensor::ECSensor(int analogPin) {
  _analogPin = analogPin;
}

void ECSensor::begin() {
  // Initialize sensor if needed
}

float ECSensor::readEC(float waterTemperatureCelsius) {
  int adcValue = analogRead(_analogPin);
  float voltage = (adcValue / 4095.0) * 3.3; // For 12-bit ADC ESP32
  return _voltageToEC(voltage, waterTemperatureCelsius);
}

float ECSensor::_voltageToEC(float voltage, float temperature) {
  // Example calibration equation; adjust based on your probe
  float ec25 = (133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 1.0;
  // Temperature compensation (standard formula)
  float ec = ec25 / (1.0 + 0.0185 * (temperature - 25.0));
  return ec;
}
