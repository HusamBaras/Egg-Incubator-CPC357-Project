# CPC357: IoT Architecture & Smart Applications - Technical Report

## Project Title: Smart Egg Incubator for Urban Farming
**SDG 11 Impact:** Sustainable Cities and Communities

### Group Members:
1. Name: [Your Name] Matric No. : [Your Matric No.]
2. Name: [Member 2] Matric No. : [Matric 2]
3. Name: [Member 3] Matric No. : [Matric 3]

---

## 1. System Architecture
### Architecture Diagram
The system follows a standard 4-layer IoT architecture:
1.  **Perception Layer (Hardware):** ESP32 Microcontroller, DHT22 Temperature & Humidity Sensor, 5V Relay Module, Cooling Fan.
2.  **Network Layer (Communication):** WiFi connectivity using HTTP REST protocol (POST/GET).
3.  **Middleware Layer (Cloud/Backend):** Node.js Express server handling data ingestion and storage.
4.  **Application Layer (Visualization):** Web-based dashboard using HTML5, CSS3, and Chart.js for real-time monitoring.

### Component Descriptions
- **ESP32:** The brain of the system, handles sensor reading, local control logic, and WiFi communication.
- **DHT22:** Provides high-accuracy temperature and humidity data.
- **Relay Module:** Acts as an electrically operated switch to turn the cooling fan on/off based on ESP32 signals.
- **Node.js Server:** Receives data from the ESP32 and serves the web dashboard to users.

---

## 2. Hardware Documentation
### List of Components
- ESP32 Development Board
- DHT22 Sensor
- 5V Single Channel Relay Module
- 12V/5V Cooling Fan
- Jumper Wires & Breadboard

### Sensor Selection Justification
The **DHT22** was chosen over the DHT11 due to its higher precision and wider range, which is critical for egg incubation where a 0.5°C deviation can affect hatch rates. The **Relay** is essential for isolating the low-voltage ESP32 from the fan's power circuit.

### Hardware Setup Guide
1. Connect DHT22 VCC to 3.3V, GND to GND, and Data to GPIO 4.
2. Connect Relay VCC to 5V, GND to GND, and IN to GPIO 5.
3. Connect the cooling fan in series with the Relay's Normally Open (NO) and Common (COM) terminals.

---

## 3. SDG 11 Impact Analysis
### Addressing Smart City Challenges
Urbanization often leads to food insecurity and high carbon footprints due to long-distance food transport. This Smart Egg Incubator enables "Micro-Farming" in dense urban environments.

### Potential Real-World Impact
- **Food Security:** Empowers urban citizens to produce protein locally.
- **Waste Reduction:** Encourages circular economy by using kitchen scraps for poultry feed.
- **Resilience:** Makes cities more self-sufficient during supply chain disruptions.

---

## 4. Repository and Video Links
- **GitHub Repository:** [Insert Your Link Here]
- **YouTube Demonstration:** [Insert Your Link Here]

---
*Note: Ensure all source code is uploaded to the repository and the video is accessible before final submission.*
