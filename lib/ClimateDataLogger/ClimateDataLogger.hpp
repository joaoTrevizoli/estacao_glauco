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
// -----------------------------------------------//

const uint32_t SAMPLE_INTERVAL_MS = 2000;
const size_t N_LEDS = 2;

// -----------------------------------------------//

class ClimateDataLogger
{
public:
  ClimateDataLogger(DHT &dht22_1, DHT &dht22_2, LiquidCrystal_I2C &lcd,
    StationRtc &rtc, uint8_t csPin,
    uint8_t greenLed, uint8_t redLed);
  void begin();
  void save();
  float readTemp();
  float readHum();


private:
  float lastTemp;
  float lastHumid;
  uint32_t logTime;
  DHT dht_1;
  DHT dht_2;
  LiquidCrystal_I2C lcd;
  StationRtc r;
  uint8_t ledPins[N_LEDS];
  void resetArduino(uint8_t resetPin);

};

#endif
