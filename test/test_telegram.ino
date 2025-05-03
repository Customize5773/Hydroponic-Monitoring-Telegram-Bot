#include "../src/telegram/telegram_handler.h"
#include "../src/config.h"  // Assumes WiFi SSID, PASS, BOT_TOKEN, CHAT_ID defined here

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
TelegramHandler telegramHandler(&bot, CHAT_ID);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  secured_client.setInsecure();  // Disable certificate validation
  telegramHandler.sendMessage("✅ Test message from Arduino!");
}

void loop() {
  telegramHandler.processMessages();
}
