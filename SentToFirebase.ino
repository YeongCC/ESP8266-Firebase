#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define FIREBASE_HOST "******.firebaseio.com"
#define FIREBASE_AUTH "**************************"
#define WIFI_SSID "*******"
#define WIFI_PASSWORD "*********"
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

int n = 0;

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Firebase.setFloat("temperature", t);
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }

  Firebase.setFloat("humidity", h);
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  Serial.print("Data Temperature: ");
  Serial.println(Firebase.getFloat("temperature"));
  Serial.print("Data Humidity: ");
  Serial.println(Firebase.getFloat("humidity"));
  Serial.println();
  delay(1000);
}
