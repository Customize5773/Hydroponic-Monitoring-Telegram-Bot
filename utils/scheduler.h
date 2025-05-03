#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

class Scheduler {
  public:
    Scheduler(unsigned long intervalMillis);
    bool shouldRun();
    void reset();

  private:
    unsigned long _interval;
    unsigned long _lastRun;
};

#endif
