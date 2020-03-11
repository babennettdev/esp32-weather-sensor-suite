/* esp32-weather-sensor-suite 
 *  Blake Bennett
 *  3/8/2020
 */

// Includes
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"

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

DHT dhtSensor(DHT_OUT_PIN, DHT_SENSOR_TYPE);


void setup() {
  Serial.begin(115200);
  Serial.println("Test DHT11 sensor");

  dhtSensor.begin();

}

void loop() {
  delay(2000);

  float humidity = dhtSensor.readHumidity();
  float temperature = dhtSensor.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("DHT sensor failure."));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float heat_index_celcius = dhtSensor.computeHeatIndex(temperature, humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.print("°C ");
  Serial.print("Heat index: ");
  Serial.print(heat_index_celcius);
  Serial.println("°C ");
}
