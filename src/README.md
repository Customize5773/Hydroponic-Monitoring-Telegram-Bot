# Hydroponic Monitoring System (Arduino)

This project implements a **Hydroponic Monitoring and Control System** using an Arduino-based microcontroller (ESP32/ESP8266 recommended).  
It measures and controls **pH, EC, and water temperature** across multiple hydroponic tanks, with integrated control of dosing pumps, solenoid valve, and refill system.

✅ Data is sent automatically every 15 minutes to a **Telegram Bot**, with support for manual commands and remote threshold adjustment.

---

## 📚 **Key Features**

- Monitor **pH, EC, and temperature** per tank
- Independent **thresholds per tank** (stored in SPIFFS)
- Automatic **nutrient dosing** using peristaltic pumps
- **Solenoid valve** drain control for pH/EC lowering
- Shared **refill pump** to maintain water level
- WiFi-based communication with **Telegram Bot**
- Supports:
  - Automatic 15-minute reporting
  - Manual `/status`, `/setph`, `/setec` commands
  - Telegram alerts for threshold violations
- Fully **standalone (no PC/server required)**

---

## 🚀 **Getting Started**

1. Clone the repository
2. Configure WiFi, Telegram Bot Token, Chat ID in `config.h`
3. Upload to compatible board (ESP32/ESP8266 recommended)
4. Ensure correct wiring for:
   - pH sensor
   - EC sensor
   - Temperature sensor
   - 4 peristaltic pumps
   - 1 solenoid valve
   - 1 refill pump
   - Ultrasonic water level sensor
5. Monitor system via Telegram Bot

---

## 📝 **Custom Commands**

See [`telegram/commands.md`](telegram/commands.md) for a full command list.

---

## 📢 **Disclaimer**

This system is intended for experimental or educational use.  
Always test thoroughly before deploying to a production hydroponic setup.
