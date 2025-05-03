#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

class TempSensor {
  public:
    TempSensor(int analogPin);
    void begin();
    float readTemperatureCelsius();

  private:
    int _analogPin;
};

#endif
