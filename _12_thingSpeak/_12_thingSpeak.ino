#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 13
float h, t;

const char* ssid = "Mahesh";
const char* password = "87654321";
#define DHTTYPE DHT11

String serverName = "https://api.thingspeak.com/update?api_key=XCMB6EVEZX23R1WH";

unsigned long lastTime = 0;
const unsigned long timerDelay = 5000; // 3 seconds delay

WiFiClient client;
HTTPClient http;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to WiFi, IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 10 seconds. It will take 10 seconds before publishing the first reading.");
  Serial.println(F("DHT11 test!"));
  dht.begin();
}

void loop() {
  if (millis() - lastTime >= timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      h = dht.readHumidity();
      t = dht.readTemperature();
      if(isnan(h) || isnan(t)) {
        h = 100;
        t = 150;
        Serial.println(F("Failed to read from DHT sensor!"));
        //return;
      }

      String serverPath = serverName + "&field1=" + String(h) + "&field2=" + String(t);

      Serial.print("Humidity = ");  Serial.print(h);
      Serial.print(" Tempearture = ");  Serial.println(t); 

      http.begin(serverPath);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);  // Print the response payload
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);  // Error code if request failed
      }
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }

    lastTime = millis();
  }
}
