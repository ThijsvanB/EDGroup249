#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";
const char* domain = "iwaterplant.infinityfreeapp.com";

void setup() {
  Serial.begin(9600);

  initWiFi();

  delay(5000);

  sendRequest();

  if(WiFi.status() == WL_CONNECTED) {
    delay(5000);
    endWiFi();
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ...");
  int i = 0;
  while(WiFi.status() != WL_CONNECTED && i < 5) {
    Serial.print(".");
    delay(1000);
    i++;
  }
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Not connected, try again");
  }
}

void endWiFi() {
  Serial.println("Disconnecting");
  WiFi.disconnect();
  delay(2000);
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected");
  }
}

bool sendRequest() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return false;
  }

  HTTPClient http;
  http.begin("https://iwaterplant.000webhostapp.com/IWP_process.php");

  http.addHeader("User-Agent", "ESP32 Client");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseCode = http.POST("username=hop&password=pakee");
  
  for(int i = 0; i < 10; i++) {
    Serial.println(i);
    delay(1000);
  }

  if(httpResponseCode > 0) {
    Serial.print("Response code");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  
  return true;
}

void loop() {
  
}
