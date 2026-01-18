#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Mahesh";
const char* password = "87654321";
int x, y;

String serverName = "https://api.thingspeak.com/update?api_key=Q2TLQ2JA6RXHKWUY";


unsigned long lastTime = 0;
const unsigned long timerDelay = 5000; // 3 seconds delay

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  x = 5;
  y = 12;
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
}

void loop() {
  if (millis() - lastTime >= timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      x = x + 2;
      y = y + 3;
      String serverPath = serverName + "&field1=" + String(x) + "&field2=" + String(y);

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