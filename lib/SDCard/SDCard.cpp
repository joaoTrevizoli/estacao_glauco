/*SDCard
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the SDCard wrapper object

Created by: Joao Trevizoli Esteves
*/

#include "SDCard.hpp"

SdFat sd;
SdFile logFile;

// -----------------------------------------------//

SDCard::SDCard(const uint8_t pinSaving)
{
  chipPin = pinSaving;
}
// -----------------------------------------------//
void SDCard::begin()
{
  pinMode(this->chipPin, OUTPUT);
  while(!sd.begin(this->chipPin, SPI_HALF_SPEED))
  {
    Serial.println("Insert the sd card!");
    delay(500);
  }
  this->openFile();
  this->csvHeader();

}
// -----------------------------------------------//
void SDCard::stop()
{
  logFile.sync();
  logFile.close();
}
// -----------------------------------------------//

void SDCard::openFile()
{
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.csv";

  if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
  while (sd.exists(fileName))
  {
    if (fileName[BASE_NAME_SIZE + 1] != '9')
    {
      fileName[BASE_NAME_SIZE + 1]++;
    }
    else if (fileName[BASE_NAME_SIZE] != '9')
    {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    }
    else
    {
      error("Can't create file name");
    }
  }
  if (!logFile.open(fileName, O_CREAT | O_WRITE | O_EXCL))
  {
    error("file.open");
  }
  Serial.print("Saving at ");
  Serial.println(fileName);

}
// -----------------------------------------------//
void SDCard::csvHeader()
{
  logFile.println(F("Data, dht22_1 Temperature, dht22_2 Temperature, dht22_1 Humidity, dht22_3 Humidity, ds18b20 Temperature, Soil Moisture, luminosity_1, luminosity_2"));
  logFile.sync();

}
// -----------------------------------------------//
void SDCard::logData(String data, float dht_1Temp, float dht_2Temp,
  float dht_1Humid, float dht_2Humid,
  float ds18b20Temp, float soilMoisture,
  float luminosity_1, float luminosity_2)
{
    logFile.print(data);
    logFile.write(',');
    logFile.print(dht_1Temp);
    logFile.write(',');
    logFile.print(dht_2Temp);
    logFile.write(',');
    logFile.print(dht_1Humid);
    logFile.write(',');
    logFile.print(dht_2Humid);
    logFile.write(',');
    logFile.print(ds18b20Temp);
    logFile.write(',');
    logFile.print(soilMoisture);
    logFile.write(',');
    logFile.print(luminosity_1);
    logFile.write(',');
    logFile.print(luminosity_2);
    logFile.println();

    if (!logFile.sync() || logFile.getWriteError())
    {
      error("write error");
    }
}
// -----------------------------------------------//
