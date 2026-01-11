#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ------------------- Configuration -------------------
const char* ssid = "HUSAMM";        //Your WiFi SSID
const char* password = "arrrrrrr"; //Your WiFi Password

// Server URL
const char* serverUrl = "http://172.17.25.216:3000/api/data";

// --- Pin Definitions for Maker Feather AIoT S3 ---
#define DHTPIN 21      // Updated to GPIO 21 based on user connection
#define DHTTYPE DHT22 
#define RELAY_PIN 42   // Physical label D42

// Temperature Settings
const float TARGET_TEMP = 37.5; 
const float TEMP_HYSTERESIS = 0.5; 

// Relay Logic Configuration
// Change this to true if your relay turns ON when the pin is HIGH
bool relayActiveHigh = true; 

// ------------------- Globals -------------------
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to connect
  Serial.println("\n--- Smart Egg Incubator Starting ---");
  
  // Initialize Relay
  pinMode(RELAY_PIN, OUTPUT);
  // Turn relay OFF immediately on boot
  digitalWrite(RELAY_PIN, relayActiveHigh ? LOW : HIGH); 

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.println("\nConnected!");
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // --- Control Logic ---
  bool fanStatus = false;
  
  if (temperature > (TARGET_TEMP + TEMP_HYSTERESIS)) {
    // Turn Fan ON
    digitalWrite(RELAY_PIN, relayActiveHigh ? HIGH : LOW);
    fanStatus = true;
  } else if (temperature < TARGET_TEMP) {
    // Turn Fan OFF
    digitalWrite(RELAY_PIN, relayActiveHigh ? LOW : HIGH);
    fanStatus = false;
  }

  // --- Serial Debugging ---
  Serial.printf("Temp: %.2f°C | Hum: %.2f%% | Fan: %s\n", 
                temperature, humidity, fanStatus ? "ON" : "OFF");

  // --- Send Data to Cloud ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Using a more robust string formatting
    String jsonPayload = "{\"temperature\": " + String(temperature) + 
                         ", \"humidity\": " + String(humidity) + 
                         ", \"fanStatus\": " + String(fanStatus ? "true" : "false") + "}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  }

  delay(5000); 
}
