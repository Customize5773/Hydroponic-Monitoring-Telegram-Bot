#ifndef SOLENOID_CONTROLLER_H
#define SOLENOID_CONTROLLER_H

class SolenoidController {
  public:
    SolenoidController(int solenoidPin);
    void begin();
    void openValve();
    void closeValve();
    bool isOpen();

  private:
    int _solenoidPin;
    bool _isOpen;
};

#endif
