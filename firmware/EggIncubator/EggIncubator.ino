#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ------------------- Configuration -------------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server URL (Replace with your computer's IP if running locally, or cloud URL)
const char* serverUrl = "http://192.168.1.100:3000/api/data";

// Pin Definitions
#define DHTPIN 4      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define RELAY_PIN 5   // Pin connected to the Relay (Heater)

// Temperature Settings
const float TARGET_TEMP = 37.5; // Target temperature in Celsius
const float TEMP_HYSTERESIS = 0.5; // Allowable fluctuation

// ------------------- Globals -------------------
DHT dht(DHTPIN, DHTTYPE);
HTTPClient http;

void setup() {
  Serial.begin(115200);
  
  // Initialize Pins
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure heater is off initially

  // Initialize Sensor
  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 1. Read Sensor Data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // 2. Control Logic (Simple Thermostat)
  bool heaterStatus = false;
  if (temperature < (TARGET_TEMP - TEMP_HYSTERESIS)) {
    digitalWrite(RELAY_PIN, HIGH); // Turn Heater ON
    heaterStatus = true;
  } else if (temperature > TARGET_TEMP) {
    digitalWrite(RELAY_PIN, LOW); // Turn Heater OFF
    heaterStatus = false;
  }

  // 3. Send Data to Cloud
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{";
    jsonPayload += "\"temperature\": " + String(temperature) + ",";
    jsonPayload += "\"humidity\": " + String(humidity) + ",";
    jsonPayload += "\"heater\": " + String(heaterStatus ? "true" : "false");
    jsonPayload += "}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Cloud Response: " + String(httpResponseCode) + " " + response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Wait before next reading
  delay(5000); // Send data every 5 seconds
}
