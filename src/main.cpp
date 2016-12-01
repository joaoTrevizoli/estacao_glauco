/* station
  __  _       _      ___   ___  _  _    __
 / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /  | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \  | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\ |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Created by: João Trevizoli Esteves
*/
#include <Arduino.h>
#include "ClimateDataLogger.hpp"
#include "StationRTC.hpp"
#include "DS18b20.hpp"
#include "SoilMoisture.hpp"
#include "SDCard.hpp"
#include "Photoresistor.hpp"

// -------------------------defines------------------------------------------ //

#define DHT_PIN_1 3
#define DHT_PIN_2 2
#define CS_PIN 53
#define ONE_WIRE_BUS 5
#define MOISTURE_PIN A0
#define LIGHT_SENSOR_1 A1
#define LIGHT_SENSOR_2 A2

// -------------------------Object Instatiating------------------------------ //
DHT dht22_1(DHT_PIN_1, DHT22);
DHT dht22_2(DHT_PIN_2, DHT22);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20Sensor(&oneWire);

DS18b20 ds18b20(ds18b20Sensor, 500);


SoilMoisture soilMoist(MOISTURE_PIN);

SDCard SD(CS_PIN);

Photoresistor photoresistor_1(LIGHT_SENSOR_1);
Photoresistor photoresistor_2(LIGHT_SENSOR_2);

StationRtc rtc;

ClimateDataLogger climateDataLogger(dht22_1, dht22_2, ds18b20, soilMoist, photoresistor_1, photoresistor_2, rtc, SD);



// -------------------------setup-------------------------------------------- //

void setup()
{
    Serial.begin(9600);
    climateDataLogger.begin();
}

// -------------------------loop--------------------------------------------- //

void loop()
{
    climateDataLogger.save();
}

// -------------------------end of main-------------------------------------- //
