#include <WiFi.h>

const char* ssid = "";
const char* password = "";

void setup() {
  initWiFi();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ...");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void connectToWebsite

void loop() {
  // put your main code here, to run repeatedly:

}
