/*SoilMoisture
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Interface of the Soil Moisture Sensor

Created by: Barbara Panosso and João Trevizoli Esteves
*/

#ifndef SOILHUMIDITY_HPP
#define  SOILHUMIDITY_HPP


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// -------------------------Debug Directives--------------------------------- //

#define SOIL_HUMIDITY_DEBUG 1

// -------------------------Class Interface---------------------------------- //

class SoilMoisture
{
public:
  SoilMoisture(const uint8_t pin);
  void begin();
  float soilHumidityPercent(int minReading, int maxReading);
  uint8_t rawHumidity();

private:
  uint8_t analogPin = A0;
};

   #endif
