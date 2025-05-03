#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H

class PumpController {
  public:
    PumpController(int pumpPin);
    void begin();
    void startPump();
    void stopPump();
    bool isRunning();

  private:
    int _pumpPin;
    bool _running;
};

#endif
