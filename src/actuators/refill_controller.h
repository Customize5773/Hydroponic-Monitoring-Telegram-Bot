#ifndef REFILL_CONTROLLER_H
#define REFILL_CONTROLLER_H

class RefillController {
  public:
    RefillController(int refillPumpPin);
    void begin();
    void startRefill();
    void stopRefill();
    bool isRefilling();

  private:
    int _refillPumpPin;
    bool _refilling;
};

#endif
