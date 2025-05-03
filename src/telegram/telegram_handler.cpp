#include "telegram_handler.h"
#include <Arduino.h>

TelegramHandler::TelegramHandler(UniversalTelegramBot* bot, const String& chatId) {
  _bot = bot;
  _chatId = chatId;
}

void TelegramHandler::processMessages() {
  int numNewMessages = _bot->getUpdates(_bot->last_message_received + 1);
  for (int i = 0; i < numNewMessages; i++) {
    String text = _bot->messages[i].text;
    String command = text;
    String params = "";

    int spaceIndex = text.indexOf(' ');
    if (spaceIndex != -1) {
      command = text.substring(0, spaceIndex);
      params = text.substring(spaceIndex + 1);
    }

    handleCommand(command, params);
  }
}

void TelegramHandler::handleCommand(const String& command, const String& params) {
  if (command == "/start") {
    sendMessage("✅ Hydroponic Monitoring Bot is active.\nUse /help for commands.");
  }
  else if (command == "/help") {
    sendMessage("📋 Available Commands:\n"
                "/status → Get current readings\n"
                "/setph <tank> <min> <max>\n"
                "/setec <tank> <min> <max>\n");
  }
  else if (command == "/status") {
    // Example → real sensor data should be passed in production
    sendMessage("📈 Tank 1:\nPH: 6.2\nEC: 1.8 mS/cm\nTemp: 24.5°C\n...");
  }
  else if (command.startsWith("/setph")) {
    // Example parsing → you can expand parsing logic
    sendMessage("✅ PH threshold updated.");
  }
  else if (command.startsWith("/setec")) {
    sendMessage("✅ EC threshold updated.");
  }
  else {
    sendMessage("⚠️ Unknown command. Type /help for list.");
  }
}

void TelegramHandler::sendMessage(const String& message) {
  _bot->sendMessage(_chatId, message, "");
}

void TelegramHandler::setPHThreshold(int tankIndex, float minPH, float maxPH) {
  // Logic to store new PH thresholds (e.g., write to SPIFFS/JSON)
}

void TelegramHandler::setECThreshold(int tankIndex, float minEC, float maxEC) {
  // Logic to store new EC thresholds
}
