/* esp32-weather-sensor-suite 
 *  Blake Bennett
 *  3/8/2020
 *
 *  This class holds the sensor objects and the methods to read from them.
 */

#include "weatherSensors.h"

weatherSensors::weatherSensors(uint8_t tempSensorPin, uint8_t tempSensorType):
  dhtSensor_(tempSensorPin, tempSensorType)
  {
    dhtSensor_.begin();
  }

  weatherSensors::~weatherSensors()
  {
    // Empty
  }

String weatherSensors::readDHTTemperature(){
  float temperature = this->dhtSensor_.readTemperature();

  if (isnan(temperature)){
    if( DEBUG ){
      Serial.println("DHT sensor failure.");
    }
    return "";
  }

  if( DEBUG ){
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ");
  }

  return String(temperature);
}

String weatherSensors::readDHTHumidity(){
  float humidity = this->dhtSensor_.readHumidity();
  
  if (isnan(humidity)){
    if( DEBUG ){
      Serial.println("DHT sensor failure.");
    }
    return "";
  }

  if( DEBUG ){
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  return String(humidity);
}

String weatherSensors::readDHTHeatIndex(){
  float humidity = this->dhtSensor_.readHumidity();
  float temperature = this->dhtSensor_.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    if( DEBUG ){
      Serial.println("DHT sensor failure.");
    }
    return "";
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float heat_index_celcius = this->dhtSensor_.computeHeatIndex(temperature, humidity, false);

  if( DEBUG ){
    Serial.print("Heat index: ");
    Serial.print(heat_index_celcius);
    Serial.println("°C ");
  }

  return String(heat_index_celcius);
}
