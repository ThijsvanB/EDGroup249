#include <WiFi.h>
#include <HTTPClient.h>

#define sensor 32
#define powerpin 4
#define LED 18

#define DEVICEID "101"

// network paramters
const char* ssid = "test";
const char* password = "test1234";

int setValue = 50;


int senseMoisture(){            //function to read sensor and get % val back
  const int dry = 880;
  const int wet = 2620;
  digitalWrite(powerpin, HIGH);
  delay(30);
  int output = analogRead(sensor);
  Serial.println(output);
  delay(30);
  digitalWrite(powerpin, LOW);
  int percent = map(output, wet, dry, 0, 100);
  if(percent < 0){
    percent = 0;
  }else if(percent > 100){
    percent = 100;
  }
  return percent;
}



void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ...");
  int i = 0;
  while(WiFi.status() != WL_CONNECTED && i < 15) {
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

bool send_sensor_value(int sensor_value) {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return false;
  }

  HTTPClient http;
  http.begin("https://iwaterplant.000webhostapp.com/IWP_process.php");

  http.addHeader("User-Agent", "ESP32 Client");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String device_id = DEVICEID;
  String sVal = String(sensor_value); // this should be changed to the function that gets the sensor value
  String data = String("device_id=" + device_id + "&sensor_value=" + sensor_value);

  int httpResponseCode = http.POST(data.c_str());
  
  delay(1000);
  
  if(httpResponseCode > 0) {
    Serial.print("Response code");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());
    http.end();
    return true;
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    http.end();
    return false;
  }
  
  

}

int get_water_requirement() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Not connected to the WiFi");
    return -1;
  }

  HTTPClient http;
  String url = "https://iwaterplant.000webhostapp.com/IWP_get_esp32data.php?device_id=" + String(DEVICEID);
  http.begin(url);

  int httpResponseCode = http.GET();
  
  delay(1000);

  String result = String(-1);

  if(httpResponseCode > 0) {
    Serial.print("Response code");
    Serial.println(httpResponseCode);
    //Serial.println(http.getString());
    result = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  Serial.println(result);
  Serial.println(result.toInt());
  return result.toInt();
}


void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  
  pinMode(powerpin, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {  
  int smv = senseMoisture();
  Serial.printf("Soil moisture = %d\n",smv);
  
  initWiFi();
  delay(1000);
  send_sensor_value(smv);
  int receivedValue = get_water_requirement();
  if(receivedValue > -1){
    setValue = receivedValue;
    Serial.println("setvalue received");
    Serial.println(setValue);
  }else{
    Serial.println("error");
  }
  delay(1000);
  endWiFi();

  if(smv < setValue){
    digitalWrite(LED, HIGH);
    delay(10000);
  }else{
    digitalWrite(LED, LOW);
  }
  
  Serial.println("going to sleep");
  esp_deep_sleep(1*30*1000000ULL);
    
}
