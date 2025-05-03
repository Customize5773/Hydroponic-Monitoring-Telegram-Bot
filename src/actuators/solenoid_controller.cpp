#include "solenoid_controller.h"
#include <Arduino.h>

SolenoidController::SolenoidController(int solenoidPin) {
  _solenoidPin = solenoidPin;
  _isOpen = false;
}

void SolenoidController::begin() {
  pinMode(_solenoidPin, OUTPUT);
  closeValve(); // Ensure valve is closed at startup
}

void SolenoidController::openValve() {
  digitalWrite(_solenoidPin, HIGH);
  _isOpen = true;
}

void SolenoidController::closeValve() {
  digitalWrite(_solenoidPin, LOW);
  _isOpen = false;
}

bool SolenoidController::isOpen() {
  return _isOpen;
}
