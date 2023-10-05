#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";
const char* domain = "iwaterplant.infinityfreeapp.com";

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

bool sendRequest() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return false;
  }

  HTTPClient http;
  http.begin(domain);

  int httpResponseCode = http.GET();
  
  if(httpResponseCode > 0) {
    Serial.print("Response code");
    Serial.print(httpResponseCode);
  }
  
  http.end();
  
  return true;
}

void loop() {
  while(!sendRequest()) {
    delay(500);
  }
}
