# Guide: How to Connect the Board and Run the Program

Follow these steps to set up your Smart Egg Incubator system.

## 1. Hardware Connections (Wiring)
Connect your ESP32 to the components as follows:

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| **DHT22 VCC** | 3.3V | Power for sensor |
| **DHT22 GND** | GND | Ground |
| **DHT22 Data**| GPIO 4 | Data signal |
| **Relay VCC** | 5V (or Vin) | Power for relay coil |
| **Relay GND** | GND | Ground |
| **Relay IN**  | GPIO 5 | Control signal |

## 1.1 Visual Wiring Description
Since I cannot provide actual photos, here is a detailed visual guide:

### DHT22 Sensor (Blue or White box with 4 pins)
- **Pin 1 (Leftmost):** Connect to ESP32 **3.3V**.
- **Pin 2:** Connect to ESP32 **GPIO 18** (Label A5 on Maker Feather S3).
- **Pin 4 (Rightmost):** Connect to ESP32 **GND**.
- *(Note: If using a module with 3 pins, they are usually labeled VCC, Data, GND).*

**Troubleshooting "Failed to read from DHT sensor!":**
1. **Check Wiring:** Ensure the data pin is firmly connected to **GPIO 18**.
2. **Pull-up Resistor:** If you are using the bare DHT22 sensor (not a module), you MUST place a **10k Ohm resistor** between Pin 1 (VCC) and Pin 2 (Data).
3. **Power:** Ensure you are using the **3.3V** pin, not 5V, as the DHT22 is sensitive to voltage on some ESP32 boards.

### Relay Module (Blue cube on a small board)
- **VCC:** Connect to ESP32 **Vin** (or 5V).
- **GND:** Connect to ESP32 **GND**.
- **IN:** Connect to ESP32 **GPIO 5**.

### Fan Wiring (Cooling System)
- **Power Source (+):** Connect directly to the Fan's positive wire.
- **Power Source (-):** Connect to the Relay **COM** terminal.
- **Relay NO terminal:** Connect to the Fan's negative wire.
- *When the temperature exceeds 38°C, the relay clicks, completing the circuit and turning the fan ON.*

---

## 2. Running the Web Application (Server)
You must start the server first so the ESP32 has somewhere to send data.

1.  Open a terminal in VS Code.
2.  Navigate to the web app folder:
    ```bash
    cd "EggIncubatorProject/web-app"
    ```
3.  Install dependencies (if not already done):
    ```bash
    npm install
    ```
4.  Start the server:
    ```bash
    npm start
    ```
5.  **Note your IP Address:** Open another terminal and type `hostname -I` (Linux) or `ipconfig` (Windows). You will need this IP for the ESP32 code.

---

## 3. Uploading the Firmware (ESP32)
1.  Open `EggIncubatorProject/firmware/EggIncubator/EggIncubator.ino` in the **Arduino IDE**.
2.  **Install Libraries:**
    - Go to `Sketch` -> `Include Library` -> `Manage Libraries...`
    - Search for and install: **"DHT sensor library"** by Adafruit.
    - Search for and install: **"Adafruit Unified Sensor"**.
3.  **Configure WiFi & Server:**
    - Change `YOUR_WIFI_SSID` to your WiFi name.
    - Change `YOUR_WIFI_PASSWORD` to your WiFi password.
    - Change the IP in `serverUrl` to your computer's IP address (e.g., `http://192.168.1.15:3000/api/data`).
4.  **Upload:**
    - Connect ESP32 to your PC via USB.
    - Select your board (e.g., "DOIT ESP32 DEVKIT V1").
    - Click the **Upload** button (arrow icon).

---

## 4. Viewing the Dashboard
1.  Once the server is running and the ESP32 is powered on, open your web browser.
2.  Go to: `http://localhost:3000`
3.  You should see the temperature and humidity updating every 5 seconds!
4.  **Fan Status:** The "Heater Status" on the dashboard now represents the **Fan**. If it says "ON", the fan should be spinning to cool the incubator.
