#ifndef CONFIG_H
#define CONFIG_H

// ===== WiFi Configuration =====
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"

// ===== Telegram Bot Configuration =====
#define BOT_TOKEN "Your_Telegram_Bot_Token"
#define CHAT_ID "Your_Chat_ID"  // Telegram user ID or group ID to send messages

// ===== Pin Definitions =====
#define PUMP_PIN_1 23   // Peristaltic pump for Tank 1
#define PUMP_PIN_2 22   // Peristaltic pump for Tank 2
#define PUMP_PIN_3 21   // Peristaltic pump for Tank 3
#define PUMP_PIN_4 19   // Peristaltic pump for Tank 4

#define SOLENOID_PIN 18 // Shared solenoid valve
#define REFILL_PUMP_PIN 5 // Shared refill pump

#define ULTRASONIC_TRIG_PIN 26
#define ULTRASONIC_ECHO_PIN 27

// ===== Timing Configuration =====
#define DATA_SEND_INTERVAL_MS (15 * 60 * 1000) // 15 minutes interval

// ===== Default Thresholds (if thresholds.json not found) =====
#define DEFAULT_PH_MIN 5.8
#define DEFAULT_PH_MAX 6.5
#define DEFAULT_EC_MIN 1.2
#define DEFAULT_EC_MAX 2.0

// ===== Ultrasonic Sensor Settings =====
#define WATER_LEVEL_MIN_CM 15 // minimum water level before refill

// ===== SSL Certificate Handling =====
#define TELEGRAM_SSL_INSECURE // Uncomment this if using unsecured client (for UniversalTelegramBot)

#endif
