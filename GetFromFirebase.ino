#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#include <DHT.h>

#define FIREBASE_HOST "**************.firebaseio.com"
#define FIREBASE_AUTH "************"
#define WIFI_SSID "*********"
#define WIFI_PASSWORD "***********"
#define DHTPIN 14
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

float temp;
float humidity;

void loop() {

  temp = Firebase.getFloat("temperature");
  humidity = Firebase.getFloat("humidity");

  if (Firebase.failed())
  {
    Serial.print(Firebase.error());
  }
  else {
    Serial.print(humidity);
    Serial.print("\t");
    Serial.println(temp);
  }

  delay(3000);
}
