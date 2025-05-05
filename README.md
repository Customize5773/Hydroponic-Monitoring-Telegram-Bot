# Hydroponic Monitoring and Control System 🌿

![Image Hyroponic Monitoring and Control](https://github.com/user-attachments/assets/e531bcbd-946e-4c4b-a8ee-5079f57b5a15)

A standalone, WiFi-based monitoring and automation system for hydroponic farming using Arduino/ESP32.  
This project provides real-time monitoring and automated control of nutrient levels (pH, EC), water temperature, and water level across 4 hydroponic tanks, integrated with a Telegram Bot interface for remote access and control.

---

## 🚀 Features

✅ Monitor pH, EC, and temperature per tank  
✅ Automatic dosing using 4 peristaltic pumps (1 per tank)  
✅ Shared solenoid valve for automatic draining  
✅ Shared refill pump for automatic water level refill  
✅ Threshold-based automation per tank (stored in SPIFFS JSON config)  
✅ Telegram Bot integration for:
- Scheduled data reporting every 15 minutes
- Manual data request
- Changing threshold parameters remotely
✅ Notification alerts if pH or EC is out of range  
✅ Standalone operation (ESP32, no external PC/server)

---

## 🏗️ Project Structure

```plaintext
├── src/                  # Main source code
│   ├── main.ino
│   ├── config.h
│   ├── sensors/          # Sensor modules
│   ├── actuators/        # Actuator controllers
│   ├── telegram/         # Telegram Bot handler
│   ├── utils/            # Utility modules
│   └── README.md         # Source-level documentation
├── test/                 # Test sketches
│   ├── test_ph_sensor.ino
│   ├── test_ec_sensor.ino
│   └── test_telegram.ino
├── data/                 # SPIFFS data (upload via SPIFFS uploader)
│   └── thresholds.json
├── docs/                 # Documentation & diagrams
│   ├── README.md
│   ├── Graphic Schematic Drawing.svg
│   └── flowchart.png
└── README.md             # Project overview
````

---

## 📝 Hardware Requirements

* **ESP32 Dev Board**
* **4x pH Sensors (analog)**
* **4x EC Sensors (analog)**
* **4x DS18B20 Waterproof Temperature Sensors**
* **1x Ultrasonic Sensor (water level)**
* **4x Peristaltic Pumps (12V)**
* **1x Solenoid Valve (12V)**
* **1x Refill Pump (12V)**
* **Relay modules or MOSFET drivers for actuators**
* **12V Power Supply for actuators**
* **5V Regulator for ESP32**
* Waterproof enclosures for outdoor environment

---

## ⚡ Wiring Overview

Refer to [`docs/README.md`](docs/README.md) for detailed wiring pinout and schematic flow.

Key connections:

| Sensor/Actuator | Pin Mapping |
| --------------- | ----------- |
| pH 1–4          | A0–A3       |
| EC 1–4          | A4–A7       |
| Temp sensors    | D1 (1-Wire) |
| Ultrasonic      | D5/D6       |
| Pumps 1–4       | D7–D10      |
| Solenoid valve  | D11         |
| Refill pump     | D12         |

---

## 💬 Telegram Bot Integration

* Uses [Universal Arduino Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot) library
* Responds to commands:

  * `/status` → current sensor data
  * `/setph [tank] [min] [max]` → update pH threshold
  * `/setec [tank] [min] [max]` → update EC threshold
* Sends automatic updates every 15 minutes
* Sends alerts if pH/EC outside thresholds

---

## 🔧 Configuration

Thresholds per tank are stored in `/data/thresholds.json` (uploaded via SPIFFS uploader):

```json
{
  "tanks": [
    { "id": 1, "ph_min": 5.8, "ph_max": 6.5, "ec_min": 1.2, "ec_max": 1.8 },
    ...
  ]
}
```

Update thresholds either by:

1. Editing and re-uploading `thresholds.json`
2. Using Telegram `/setph` and `/setec` commands

---

## 🏃‍♂️ Getting Started

1. Clone the repository
2. Open in Arduino IDE or PlatformIO
3. Install dependencies:

   * ArduinoJson
   * Universal Telegram Bot
   * WiFi
   * SPIFFS
4. Configure WiFi credentials and Telegram token in `config.h`
5. Upload `/data/thresholds.json` via SPIFFS uploader
6. Flash firmware
7. Verify Telegram Bot responds and sensors function

---

## 🧪 Testing

Use provided test sketches in `/test` to validate individual sensors and modules before full deployment.

---

## 📄 Documentation

* Flowchart and technical docs available in [`docs/`](docs/)

---

## 📢 License

MIT License

---

## 👨‍💻 Contribution

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

---
