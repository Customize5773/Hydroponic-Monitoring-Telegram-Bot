#ifndef TELEGRAM_HANDLER_H
#define TELEGRAM_HANDLER_H

#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

class TelegramHandler {
  public:
    TelegramHandler(UniversalTelegramBot* bot, const String& chatId);
    void processMessages();
    void sendMessage(const String& message);
    void setPHThreshold(int tankIndex, float minPH, float maxPH);
    void setECThreshold(int tankIndex, float minEC, float maxEC);

  private:
    UniversalTelegramBot* _bot;
    String _chatId;
    void handleCommand(const String& command, const String& params);
};

#endif
