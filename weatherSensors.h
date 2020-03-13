/* esp32-weather-sensor-suite 
 *  Blake Bennett
 *  3/8/2020
 *
 *  This class holds the sensor objects and the methods to read from them.
 */

#ifndef WEATHERSENSORS_H
#define WEATHERSENSORS_H

#include <Arduino.h>
#include "DHT.h"
#define DEBUG 1

class weatherSensors
{
public:

	weatherSensors(uint8_t tempSensorPin, uint8_t tempSensorType);
	~weatherSensors();

	String readDHTTemperature();
	String readDHTHumidity();
	String readDHTHeatIndex();

    DHT dhtSensor_;



};
#endif // WEATHERSENSORS_H
