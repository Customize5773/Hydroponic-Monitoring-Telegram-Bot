# 📚 Hydroponic Monitoring System Documentation

This folder contains technical documentation, schematics, and design information for the Hydroponic Monitoring and Control System.

---

## 📝 Technical Overview

This system monitors and controls:

- **pH**, **EC**, and **water temperature** in 4 hydroponic tanks
- Automatic dosing with **4 peristaltic pumps** (1 pump per tank)
- Automatic drain via **shared solenoid valve**
- Automatic refill using **shared refill pump**
- Thresholds per tank stored in **SPIFFS JSON config**
- Communication via **Telegram Bot** over WiFi
- Periodic and on-demand reporting through Telegram

The system operates **24/7**, designed to be **standalone and outdoor-capable** (requires waterproof enclosures for electronics).

---

## ⚡ Wiring Diagram

### Sensors:

| Sensor            | Pin                 |
|------------------|--------------------|
| pH sensor 1       | Analog pin A0       |
| pH sensor 2       | Analog pin A1       |
| pH sensor 3       | Analog pin A2       |
| pH sensor 4       | Analog pin A3       |
| EC sensor 1       | Analog pin A4       |
| EC sensor 2       | Analog pin A5       |
| EC sensor 3       | Analog pin A6       |
| EC sensor 4       | Analog pin A7       |
| Temp sensor 1-4   | Digital pin D1-D4 (1-Wire DS18B20) |
| Ultrasonic sensor | Trig=D5, Echo=D6    |

### Actuators:

| Actuator                | Pin        |
|------------------------|------------|
| Pump 1 (tank 1)         | D7         |
| Pump 2 (tank 2)         | D8         |
| Pump 3 (tank 3)         | D9         |
| Pump 4 (tank 4)         | D10        |
| Solenoid valve          | D11        |
| Refill pump             | D12        |

✅ Pins are examples—adjust based on your board.

Each pump/valve controlled via **relay module or MOSFET driver**.

---

## 🖼️ Flowchart

See [`flowchart.png`](docs/flowchart.png) for system flow.

### Flowchart Summary:

1. Every 15 minutes:
   - Measure pH, EC, temperature
   - Compare with threshold
   - Dose if out of range
   - Drain if over-threshold
   - Refill if water level low
   - Send data to Telegram

2. Telegram commands:
   - `/status`: send current data
   - `/setph [tank] [min] [max]`
   - `/setec [tank] [min] [max]`

3. Alerts:
   - Notify if pH/EC out of threshold

---

## 📝 Notes:

- All pumps and valves **share GND power rail** → use external power supply for actuators.
- Ensure **logic level compatibility** if using 5V relays with 3.3V ESP32/ESP8266.
- Protect sensors/boards in **IP65+ waterproof enclosure** for outdoor use.

---

## 📂 Files in `docs/`:

- `flowchart.png`: system process flowchart
- `README.md`: this technical documentation

---

## 📢 Disclaimer

This system is experimental. Always validate hardware wiring and logic before operating pumps/valves with live hydroponic setups.

