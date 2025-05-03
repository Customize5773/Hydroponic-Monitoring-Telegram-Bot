#include "../src/sensors/ph_sensor.h"

PHSensor phSensor(A0);  // Use correct analog pin for your board

void setup() {
  Serial.begin(115200);
  Serial.println("=== pH Sensor Test ===");
}

void loop() {
  float ph = phSensor.readPH();
  Serial.print("pH: ");
  Serial.println(ph, 2);
  delay(2000);  // Read every 2 seconds
}
