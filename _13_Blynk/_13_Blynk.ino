#define BLYNK_PRINT Serial


#define BLYNK_TEMPLATE_ID "TMPL3VZR43Ezo"
#define BLYNK_TEMPLATE_NAME "weather"
#define BLYNK_AUTH_TOKEN "xD7gKUlhJrEen2qBBosoa8fEoXSUPrn0"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "Mahesh";
char pass[] = "87654321";
int x, y;

void setup()
{ Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  x = 13;
  y = 23;
}

void loop()
{ Blynk.virtualWrite(V0, x);
  Blynk.virtualWrite(V1, y);


  Blynk.run();
  x = x + 2;
  y = y + 3;
  delay(4000);
}

