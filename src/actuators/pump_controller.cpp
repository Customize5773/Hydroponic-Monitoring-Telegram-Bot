#include "pump_controller.h"
#include <Arduino.h>

PumpController::PumpController(int pumpPin) {
  _pumpPin = pumpPin;
  _running = false;
}

void PumpController::begin() {
  pinMode(_pumpPin, OUTPUT);
  stopPump(); // Ensure pump is off at startup
}

void PumpController::startPump() {
  digitalWrite(_pumpPin, HIGH);
  _running = true;
}

void PumpController::stopPump() {
  digitalWrite(_pumpPin, LOW);
  _running = false;
}

bool PumpController::isRunning() {
  return _running;
}
