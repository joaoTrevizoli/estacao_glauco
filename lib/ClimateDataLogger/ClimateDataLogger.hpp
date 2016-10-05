/*ClimateDataLogger
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Interface of the climate datalogger object

Created by: Joao Trevizoli Esteves
*/

#ifndef CLIMATEDATALOGGER_HPP
#define  CLIMATEDATALOGGER_HPP

// -----------------------------------------------//

#if ARDUINO >= 100
 #include "Arduino.h"
#endif
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "StationRTC.hpp"
#include "DS18B20.hpp"
#include "SoilMoisture.hpp"
#include "Photoresistor.hpp"
#include "SDCard.hpp"
// -----------------------------------------------//

#define CLIMATEDATALOGGER_DEBUG 1

// -----------------------------------------------//
const uint32_t SAMPLE_INTERVAL_MS = 2000;
const size_t N_LEDS = 2;

// -----------------------------------------------//

class ClimateDataLogger
{
public:
  ClimateDataLogger(DHT &dht22_1,
    DHT &dht22_2, DS18b20 &ds18b20sensor,
    SoilMoisture &soilMoistureSensor,
    Photoresistor &photoresistorSensor_1,
    Photoresistor &photoresistorSensor_2,
    StationRtc &rtc,
    SDCard &card);
  void begin();
  void save();
  void update();


private:
  float dht_1Temp;
  float dht_2Temp;
  float dht_1Humid;
  float dht_2Humid;
  float ds18b20Temp;
  float soilMoisture;
  int luminosity_1;
  int luminosity_2;

  uint32_t logTime;
  DHT dht_1;
  DHT dht_2;
  DS18b20 ds18b20sensor;
  SoilMoisture soilMoistureSensor;
  Photoresistor photoresistorSensor_1;
  Photoresistor photoresistorSensor_2;
  StationRtc rtc;
  SDCard card;
  void resetArduino(uint8_t resetPin);

};

#endif
