/*SoilMoisture
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the Soil Moisture Sensor

Created by: Barbara Panosso and João Trevizoli Esteves
*/

#include "SoilMoisture.hpp"

// -------------------------Init method-------------------------------------- //

SoilMoisture::SoilMoisture(const uint8_t pin)
{
  analogPin = pin;
}

// -------------------------Public methods----------------------------------- //

void SoilMoisture::begin()
{
  pinMode(analogPin, INPUT);
}

// -------------------------Public methods----------------------------------- //

float SoilMoisture::soilHumidityPercent(int minReading, int maxReading)
{
int sensorValue = analogRead(analogPin);

sensorValue = map(sensorValue, maxReading, minReading, 0, 10000);
float moisture = static_cast<float>(sensorValue)/100.0;

#if SOIL_HUMIDITY_DEBUG == 1
    this->rawHumidity();
    Serial.print("Soil Moisture in percentage: ");
    Serial.println(moisture);
#endif

return moisture;
}

// -------------------------------------------------------------------------- //

uint8_t SoilMoisture::rawHumidity()
{
  #if SOIL_HUMIDITY_DEBUG == 1
    Serial.print("Raw measurement of Humidity: ");
    Serial.println(analogRead(analogPin));
  #endif
  return analogRead(analogPin);
}

// -------------------------------------------------------------------------- //
