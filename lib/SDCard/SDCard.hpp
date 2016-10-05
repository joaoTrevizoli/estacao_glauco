/*SDCard
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Interface of the SDCard wrapper object

Created by: Joao Trevizoli Esteves
*/

#ifndef SDCARD_HPP
#define SDCARD_HPP

#include <SPI.h>
#include <SdFat.h>

// -----------------------------------------------//
#define FILE_BASE_NAME "Data"

// -----------------------------------------------//

class SDCard
{
public:
  SDCard(const uint8_t chipSelectPin);
  void begin();
  void stop();
  void logData(String data, float dht_1Temp, float dht_2Temp,
    float dht_1Humid, float dht_2Humid,
    float ds18b20Temp, float soilMoisture,
    float luminosity_1, float luminosity_2);

private:
  uint8_t chipPin;
  #define error(msg) sd.errorHalt(F(msg))
  void openFile();
  void csvHeader();

};

#endif
