# Smart Egg Incubator - IoT Project (SDG 11)

## Project Overview
This project is a Smart Egg Incubator system designed to address urban food security and promote smart urban farming, contributing to **UN Sustainable Development Goal 11: Sustainable Cities and Communities**. 

The system uses an ESP32 microcontroller to monitor temperature and humidity in real-time, automatically controlling a heater to maintain optimal incubation conditions. Data is sent to a cloud-based (or local) web application for visualization and historical tracking.

## Features
- **Real-time Monitoring:** DHT22 sensor for precise temperature and humidity tracking.
- **Automated Control:** Hysteresis-based thermostat logic to control a heating element via a relay.
- **Web Dashboard:** Interactive dashboard with live gauges and historical line charts using Chart.js.
- **Cloud Integration:** REST API communication between ESP32 and Node.js backend.

## System Architecture
1. **Hardware Layer:** ESP32, DHT22 Sensor, 5V Relay, Heating Element.
2. **Communication Layer:** WiFi (HTTP POST/GET).
3. **Backend Layer:** Node.js with Express.js.
4. **Frontend Layer:** HTML5, CSS3, JavaScript (Chart.js).

## Hardware Setup
- **ESP32 Pin 4:** DHT22 Data Pin.
- **ESP32 Pin 5:** Relay Control Pin.
- **Power:** 5V for Relay/Sensor, 3.3V for ESP32.

## Installation & Setup

### Firmware
1. Open `firmware/EggIncubator.ino` in Arduino IDE.
2. Install `DHT sensor library` and `Adafruit Unified Sensor` via Library Manager.
3. Update `ssid`, `password`, and `serverUrl` in the code.
4. Upload to ESP32.

### Web Application
1. Navigate to `web-app/` directory.
2. Run `npm install` to install dependencies.
3. Run `npm start` to launch the server.
4. Access the dashboard at `http://localhost:3000`.

## SDG 11 Impact
By enabling efficient, small-scale urban poultry farming, this system reduces the carbon footprint of food transport and empowers urban residents to produce their own sustainable food sources, making cities more resilient and self-sufficient.
