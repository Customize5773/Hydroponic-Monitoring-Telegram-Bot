#include "refill_controller.h"
#include <Arduino.h>

RefillController::RefillController(int refillPumpPin) {
  _refillPumpPin = refillPumpPin;
  _refilling = false;
}

void RefillController::begin() {
  pinMode(_refillPumpPin, OUTPUT);
  stopRefill(); // Ensure refill pump is off at startup
}

void RefillController::startRefill() {
  digitalWrite(_refillPumpPin, HIGH);
  _refilling = true;
}

void RefillController::stopRefill() {
  digitalWrite(_refillPumpPin, LOW);
  _refilling = false;
}

bool RefillController::isRefilling() {
  return _refilling;
}
