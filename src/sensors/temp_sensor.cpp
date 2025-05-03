#include "temp_sensor.h"
#include <Arduino.h>

TempSensor::TempSensor(int analogPin) {
  _analogPin = analogPin;
}

void TempSensor::begin() {
  // Initialize sensor if needed
}

float TempSensor::readTemperatureCelsius() {
  int adcValue = analogRead(_analogPin);
  float voltage = (adcValue / 4095.0) * 3.3; // For 12-bit ADC ESP32
  // Example for analog NTC thermistor → adjust calibration as needed
  float resistance = (10000 * voltage) / (3.3 - voltage);
  float steinhart;
  steinhart = resistance / 10000.0; // (R/Ro)
  steinhart = log(steinhart);       // ln(R/Ro)
  steinhart /= 3950;                // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25 + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;      // Invert
  steinhart -= 273.15;              // convert to °C
  return steinhart;
}
