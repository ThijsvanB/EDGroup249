#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";
const char* domain = "iwaterplant.infinityfreeapp.com";

#define DEVICEID = 101;

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

/*
 * Function to send the sensor value to the server.
 * Param sensor_value this is the value that should be sent to the server
*/
void send_sensor_value(int sensor_value) {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return false;
  }

  HTTPClient http;
  http.begin("https://iwaterplant.000webhostapp.com/IWP_process.php");

  http.addHeader("User-Agent", "ESP32 Client");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String device_id = String(DEVICEID);
  String sensor_value = String(sensor_value) // this should be changed to the function that gets the sensor value
  String data = String("device_id=" + device_id + "&sensor_value=" + sensor_value);

  int httpResponseCode = http.POST(data.c_str());
  
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
}

/*
 * Function to get the water requirement from the server
 * Returns the water depth requirement if its registered, otherwise returns -1
*/
int get_water_requirement() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return false;
  }

  HTTPClient http;
  String url = "https://iwaterplant.000webhostapp.com/IWP_get_esp32data.?device_id=" + String(DEVICEID);
  http.begin("https://iwaterplant.000webhostapp.com/IWP_get_esp32data.?device_id = ");

  int httpResponseCode = http.GET();
  
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
}

void loop() {
  
}
