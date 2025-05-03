#include "scheduler.h"

Scheduler::Scheduler(unsigned long intervalMillis) {
  _interval = intervalMillis;
  _lastRun = 0;
}

bool Scheduler::shouldRun() {
  unsigned long currentMillis = millis();
  if (currentMillis - _lastRun >= _interval) {
    _lastRun = currentMillis;
    return true;
  }
  return false;
}

void Scheduler::reset() {
  _lastRun = millis();
}
