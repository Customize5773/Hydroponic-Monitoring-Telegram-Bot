#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "sensor/ph_sensor.h"
#include "sensor/ec_sensor.h"
#include "sensor/temp_sensor.h"

#include "actuators/pump_controller.h"
#include "actuators/solenoid_controller.h"
#include "actuators/refill_controller.h"

// ===== WiFi & Telegram Config =====
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";
const char* botToken = "BOT_TOKEN";
const char* chatID = "CHAT_ID";  // target telegram ID

WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);

// ===== Pin Definitions =====
const int pumpPins[4] = { 23, 22, 21, 19 };    // Peristaltic pump pins for tank1-tank4
const int solenoidPin = 18;                     // Solenoid valve pin
const int refillPumpPin = 5;                    // Refill pump pin
const int ultrasonicTrigPin = 26;               // Ultrasonic trig
const int ultrasonicEchoPin = 27;               // Ultrasonic echo

// ===== Threshold Data =====
struct Threshold {
  float ph_min;
  float ph_max;
  float ec_min;
  float ec_max;
};

Threshold thresholds[4];  // 4 tanks

unsigned long lastDataSend = 0;
const unsigned long sendInterval = 15 * 60 * 1000; // 15 minutes

// Dummy function (replace with real sensor read)
float readPHSensor(int tank) { return random(550, 670) / 100.0; }  // random 5.5 - 6.7
float readECSensor(int tank) { return random(110, 230) / 100.0; }  // random 1.1 - 2.3
float readTempSensor() { return random(200, 300) / 10.0; }         // random 20 - 30
float readWaterLevel() { return random(10, 30); }                   // dummy cm

// ===== Function to load thresholds from SPIFFS =====
bool loadThresholds() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return false;
  }

  File file = SPIFFS.open("/thresholds.json", "r");
  if (!file) {
    Serial.println("File thresholds.json not found!");
    return false;
  }

  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size + 1]);
  file.readBytes(buf.get(), size);
  buf[size] = '\0';

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.println("Failed to parse threshold JSON");
    return false;
  }

  for (int i = 0; i < 4; i++) {
    String tankKey = "tank" + String(i + 1);
    thresholds[i].ph_min = doc[tankKey]["ph_min"];
    thresholds[i].ph_max = doc[tankKey]["ph_max"];
    thresholds[i].ec_min = doc[tankKey]["ec_min"];
    thresholds[i].ec_max = doc[tankKey]["ec_max"];
  }

  Serial.println("Thresholds loaded from SPIFFS.");
  return true;
}

// ===== Function to save thresholds to SPIFFS =====
bool saveThresholds() {
  StaticJsonDocument<512> doc;
  for (int i = 0; i < 4; i++) {
    String tankKey = "tank" + String(i + 1);
    doc[tankKey]["ph_min"] = thresholds[i].ph_min;
    doc[tankKey]["ph_max"] = thresholds[i].ph_max;
    doc[tankKey]["ec_min"] = thresholds[i].ec_min;
    doc[tankKey]["ec_max"] = thresholds[i].ec_max;
  }

  File file = SPIFFS.open("/thresholds.json", "w");
  if (!file) {
    Serial.println("Failed to write thresholds.json");
    return false;
  }
  serializeJsonPretty(doc, file);
  file.close();
  Serial.println("Thresholds saved to SPIFFS.");
  return true;
}

// ===== Function to send sensor data =====
void sendSensorData() {
  String message = "📊 *Hydroponic Monitoring*\n";
  for (int i = 0; i < 4; i++) {
    float ph = readPHSensor(i);
    float ec = readECSensor(i);
    message += "🔹 Tank " + String(i + 1) + ": pH=" + String(ph) + ", EC=" + String(ec) + "\n";

    // Check pH threshold
    if (ph < thresholds[i].ph_min) {
      digitalWrite(pumpPins[i], HIGH);
      bot.sendMessage(chatID, "⚠️ Tank " + String(i + 1) + ": pH LOW! Pump activated.", "");
    } else if (ph > thresholds[i].ph_max) {
      digitalWrite(solenoidPin, HIGH);  // Open solenoid to drain
      bot.sendMessage(chatID, "⚠️ Tank " + String(i + 1) + ": pH HIGH! Solenoid opened.", "");
    } else {
      digitalWrite(pumpPins[i], LOW);
      digitalWrite(solenoidPin, LOW);
    }

    // Check EC threshold
    if (ec < thresholds[i].ec_min) {
      digitalWrite(pumpPins[i], HIGH);
      bot.sendMessage(chatID, "⚠️ Tank " + String(i + 1) + ": EC LOW! Pump activated.", "");
    } else if (ec > thresholds[i].ec_max) {
      digitalWrite(solenoidPin, HIGH);
      bot.sendMessage(chatID, "⚠️ Tank " + String(i + 1) + ": EC HIGH! Solenoid opened.", "");
    } else {
      digitalWrite(pumpPins[i], LOW);
      digitalWrite(solenoidPin, LOW);
    }
  }

  float temp = readTempSensor();
  message += "🌡️ Water Temp: " + String(temp) + "°C\n";

  float level = readWaterLevel();
  message += "💧 Water Level: " + String(level) + " cm\n";

  if (level < 15) {
    digitalWrite(refillPumpPin, HIGH);
    bot.sendMessage(chatID, "⚠️ Low water level! Refill pump activated.", "");
  } else {
    digitalWrite(refillPumpPin, LOW);
  }

  bot.sendMessage(chatID, message, "Markdown");
}

// ===== Handle Telegram Commands =====
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String text = bot.messages[i].text;
    String from = bot.messages[i].chat_id;

    if (from != chatID) continue; // respond only to owner

    if (text == "/status") {
      sendSensorData();
    }
    else if (text.startsWith("/setphmin")) {
      int tank = text.substring(9,10).toInt() - 1;
      float val = text.substring(11).toFloat();
      thresholds[tank].ph_min = val;
      saveThresholds();
      bot.sendMessage(chatID, "✅ Tank " + String(tank+1) + " pH_min set to " + String(val), "");
    }
    else if (text.startsWith("/setphmax")) {
      int tank = text.substring(9,10).toInt() - 1;
      float val = text.substring(11).toFloat();
      thresholds[tank].ph_max = val;
      saveThresholds();
      bot.sendMessage(chatID, "✅ Tank " + String(tank+1) + " pH_max set to " + String(val), "");
    }
    else if (text.startsWith("/setecmin")) {
      int tank = text.substring(9,10).toInt() - 1;
      float val = text.substring(11).toFloat();
      thresholds[tank].ec_min = val;
      saveThresholds();
      bot.sendMessage(chatID, "✅ Tank " + String(tank+1) + " EC_min set to " + String(val), "");
    }
    else if (text.startsWith("/setecmax")) {
      int tank = text.substring(9,10).toInt() - 1;
      float val = text.substring(11).toFloat();
      thresholds[tank].ec_max = val;
      saveThresholds();
      bot.sendMessage(chatID, "✅ Tank " + String(tank+1) + " EC_max set to " + String(val), "");
    }
    else {
      bot.sendMessage(chatID, "Unknown command. Use /status or /setphminx value", "");
    }
  }
}

PHSensor phSensor(34); // Example pin
ECSensor ecSensor(35);
TempSensor tempSensor(32);

PumpController pump1(PUMP_PIN_1);
PumpController pump2(PUMP_PIN_2);
PumpController pump3(PUMP_PIN_3);
PumpController pump4(PUMP_PIN_4);

SolenoidController solenoid(SOLENOID_PIN);
RefillController refill(REFILL_PUMP_PIN);

// ===== Setup =====
void setup() {
  Serial.begin(115200);

  phSensor.begin();
  ecSensor.begin();
  tempSensor.begin();

  pump1.begin();
  pump2.begin();
  pump3.begin();
  pump4.begin();
  solenoid.begin();
  refill.begin();

  for (int i = 0; i < 4; i++) pinMode(pumpPins[i], OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(refillPumpPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  secured_client.setInsecure();  // Disable SSL verification

  if (!loadThresholds()) {
    Serial.println("Using default thresholds.");
    for (int i = 0; i < 4; i++) {
      thresholds[i] = {5.8, 6.5, 1.2, 2.0};
    }
    saveThresholds();
  }

  bot.sendMessage(chatID, "✅ Hydroponic Monitoring System Online!", "");
}

// ===== Loop =====
void loop() {
  if (millis() - lastDataSend > sendInterval) {
    sendSensorData();
    lastDataSend = millis();
  }

  float tempC = tempSensor.readTemperatureCelsius();
  float ec = ecSensor.readEC(tempC);
  float ph = phSensor.readPH();

  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while (numNewMessages) {
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
  Serial.printf("T: %.2f C, EC: %.2f mS/cm, pH: %.2f\n", tempC, ec, ph);
  delay(1000);
}
