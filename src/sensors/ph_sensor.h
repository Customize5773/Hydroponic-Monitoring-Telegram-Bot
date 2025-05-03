#ifndef PH_SENSOR_H
#define PH_SENSOR_H

class PHSensor {
  public:
    PHSensor(int analogPin);
    void begin();
    float readPH();

  private:
    int _analogPin;
    float _voltageToPH(float voltage);
};

#endif
