#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Madhura"
#define WIFI_PASSWORD "87654321"
#define API_KEY "AIzaSyDtSitCEne-p_oKx3psnfJdNs2g5ovO_2U"

#define DATABASE_URL "https://smart-b4d0a-default-rtdb.firebaseio.com/" 
#define FIREBASE_PROJECT_ID "smart-b4d0a"
#define DHTPIN 13
#define DHTTYPE DHT11
float h, t;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool taskCompleted = false;
int i;
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);


void setup()
{ i = 0;
  Serial.begin(115200);
  dht.begin();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("SignUp Ok");
    taskCompleted = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectNetwork(true);
  i=1;
}

void loop()
{ Serial.print(" It is in loop. ");
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)){
  sendDataPrevMillis = millis();
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  if(Firebase.RTDB.setInt(&fbdo, "/test/Temperature", t)){
    Serial.println(" Temperature saved Succefully");
  }
  else
  Serial.println(" Temperature not saved.");

  if(Firebase.RTDB.setInt(&fbdo, "/test/Humidity", h)){
    Serial.println(" Humidity saved Succefully");
  }
  else
  Serial.println(" Humidity not saved.");

  Serial.print(" Temprature = "); Serial.print(t); 
  Serial.print(" Humidity = "); Serial.println(h); 

}

  delay(5000);
  
}
