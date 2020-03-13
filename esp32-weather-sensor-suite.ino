/* esp32-weather-sensor-suite 
 *  Blake Bennett
 *  3/8/2020
 */

// Includes
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "weatherSensors.h"

// Definitions
#define DHT_OUT_PIN 13
#define DHT_SENSOR_TYPE DHT11 //Using a DHT11 sensor for this project.

// Global Variables
/* TODO
 *  Can we parse these out of a file stored in /data by SPIFFS?
 *  That would be much cleaner and .gitignore would allow those passwords to remain hidden.
 */
const char* ssid = "YOUR_SSID_HERE";
const char* password = "YOUR_PASSWORD_HERE";


weatherSensors sensors(DHT_OUT_PIN, DHT_SENSOR_TYPE);
AsyncWebServer server(80);  //Port 80

String processor(const String& var){
  Serial.println(var);
  if(var == "TEMPERATURE"){
    return sensors.readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return sensors.readDHTHumidity();
  }
  else if(var == "HEAT_INDEX"){
    return sensors.readDHTHeatIndex();
  }
  return String();
}

void setup() {
  
  Serial.begin(115200); // Begin serial communication for debug

  // Initialize SPIFFS filesystem
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Wi-Fi connected!");
  
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  
  server.begin();
  Serial.println("Server started!");
 }

void loop() {
  
  
}
