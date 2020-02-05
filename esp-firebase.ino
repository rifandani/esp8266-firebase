int sensorPin = A0;                

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Ysu"
#define WIFI_PASSWORD "rahasiadong"

#define FIREBASE_HOST "esp8266-weather-station-9b3d1.firebaseio.com"
#define FIREBASE_AUTH "s1rjSzX9SjZbhyIpxpbNuLMH15CYmBpAxZBnzkxB" 
//#define MEASURES "measures" 

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  Serial.println("Rain Value: ");
  Serial.print(sensorValue);
  String rainValue = String(sensorValue) + String("poin analog");                                             
  delay(4000);
  
  Firebase.pushString("/SensorHujan", rainValue);
//Firebase.pushInt(MEASURES, sensorValue);
  if (Firebase.failed()) {
      Serial.println("pushing failed: ");
      Serial.print(Firebase.error());  
      return;
  }
}
