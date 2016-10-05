/* DHT 22 sensor
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the climate datalogger object

*/

#include "ClimateDataLogger.hpp"

ClimateDataLogger::ClimateDataLogger(DHT &dht22_1,
  DHT &dht22_2,
  DS18b20 &ds18b20sensor,
  SoilMoisture &soilMoistureSensor,
  Photoresistor &photoresistorSensor_1,
  Photoresistor &photoresistorSensor_2,
  StationRtc &rtc,
  SDCard &card):
  dht_1(dht22_1),
  dht_2(dht22_2),
  ds18b20sensor(ds18b20sensor),
  soilMoistureSensor(soilMoistureSensor),
  photoresistorSensor_1(photoresistorSensor_1),
  photoresistorSensor_2(photoresistorSensor_2),
  rtc(rtc),
  card(card)
{

}

// -----------------------------------------------//

void ClimateDataLogger::begin()
{
  this->dht_1.begin();
  this->dht_2.begin();
  this->ds18b20sensor.begin();
  this->soilMoistureSensor.begin();
  this->rtc.begin();
  this->card.begin();
  this->logTime = SAMPLE_INTERVAL_MS;
}


// -----------------------------------------------//

void ClimateDataLogger::save()
{
  uint32_t currentMillis = millis();
  if(currentMillis - this->logTime > SAMPLE_INTERVAL_MS)
  {
    this->logTime = millis();
    this->update();
    #if CLIMATEDATALOGGER_DEBUG == 1
      Serial.print("DHT 1 temp: ");
      Serial.print(this->dht_1Temp);
      Serial.print(" DHT 2 temp: ");
      Serial.print(this->dht_2Temp);
      Serial.print(" DHT 1 Humid: ");
      Serial.print(this->dht_1Humid);
      Serial.print(" DHT 2 Humid: ");
      Serial.print(this->dht_2Humid);
      Serial.print(" DS18b20 Temp: ");
      Serial.print(this->ds18b20Temp);
      Serial.print(" Soil Moisture: ");
      Serial.println(this->soilMoisture);
    #endif
    this->card.logData(this->rtc.dateTimeNow(), this->dht_1Temp,
    this->dht_2Temp, this->dht_1Humid, this->dht_2Humid,
    this->ds18b20Temp, this->soilMoisture, this->luminosity_1, this->luminosity_2);
  }
}

// -----------------------------------------------//

void ClimateDataLogger::update()
{
  this->dht_1Temp = this->dht_1.readTemperature();
  this->dht_2Temp = this->dht_2.readTemperature();
  this->dht_1Humid = this->dht_1.readHumidity();
  this->dht_2Humid = this->dht_2.readHumidity();
  this->ds18b20Temp = this->ds18b20sensor.getTemperature();
  this->soilMoisture =  static_cast<float>(this->soilMoistureSensor.rawHumidity());
  this->luminosity_1 = this->photoresistorSensor_1.rawLuminosity();
  this->luminosity_2 = this->photoresistorSensor_2.rawLuminosity();
}

// -----------------------------------------------//
