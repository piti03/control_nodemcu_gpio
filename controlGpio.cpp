
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Arduino_JSON.h>

const char* ssid = "shatel";
const char* password = "@136313631363@";

// The URL of your site.
const char* serverName = "http://rabipoor.ir/iot/nodemcu_led/mcu_feeds.php";


void setup() {
 
 Serial.begin(115200);
 
 WiFi.begin(ssid, password);
 Serial.println("connecting");
 
 while (WiFi.status() != WL_CONNECTED){
   delay(500);
   Serial.print(".");
 }
   Serial.println("");
   Serial.print("connecting to the local wifi, IP ADDRESS :");
   Serial.println(WiFi.localIP());
 

}

void loop() {
   WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    int httpCode = http.GET();
    if(httpCode == 200){

      String response = http.getString();
      JSONVar gotObject = JSON.parse(response);
       if (JSON.typeof(gotObject) == "undefined") {
        Serial.println("failed! something went wrong");
        return;
            }
      Serial.print("JSON object = ");
      Serial.println(gotObject);
     
      JSONVar gpioKeys = gotObject.keys();
      for(int i = 0; i < gpioKeys.length(); i++){
        JSONVar gpioValue = gotObject[gpioKeys[i]];
        Serial.print("GPIO: ");
        Serial.print(gpioKeys[i]);
        Serial.print(" - SET to: ");
        Serial.println(gpioValue);
        pinMode(atoi(gpioKeys[i]), OUTPUT);
        digitalWrite(atoi(gpioKeys[i]), atoi(gpioValue));
      }
    }else{
        Serial.print("no successfull connection");
        Serial.print(httpCode);
      }

     }
    

