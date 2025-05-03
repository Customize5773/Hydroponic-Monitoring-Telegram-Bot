#include "../src/sensors/ec_sensor.h"

ECSensor ecSensor(A1);  // Use correct analog pin for your board

void setup() {
  Serial.begin(115200);
  Serial.println("=== EC Sensor Test ===");
}

void loop() {
  float ec = ecSensor.readEC();
  Serial.print("EC: ");
  Serial.print(ec, 2);
  Serial.println(" mS/cm");
  delay(2000);  // Read every 2 seconds
}
