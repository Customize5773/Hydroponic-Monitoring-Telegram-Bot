#ifndef EC_SENSOR_H
#define EC_SENSOR_H

class ECSensor {
  public:
    ECSensor(int analogPin);
    void begin();
    float readEC(float waterTemperatureCelsius);

  private:
    int _analogPin;
    float _voltageToEC(float voltage, float temperature);
};

#endif
