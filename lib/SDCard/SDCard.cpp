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


// -----------------------------------------------//

SDCard::SDCard(const uint8_t pinSaving):
sd(),
logFile()
{
  chipPin = pinSaving;
}
// -----------------------------------------------//
void SDCard::begin()
{
  pinMode(this->chipPin, OUTPUT);
  while(!this->sd.begin(this->chipPin, SPI_HALF_SPEED))
  {
    Serial.println("Insira o Cartao!");
    delay(500);
  }
  this->openFile();
  this->csvHeader();
}
// -----------------------------------------------//
void SDCard::stop()
{
  this->logFile.sync();
  this->logFile.close();
}
// -----------------------------------------------//

void SDCard::openFile()
{
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.csv";

  if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
  while (this->sd.exists(fileName))
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
  if (!this->logFile.open(fileName, O_CREAT | O_WRITE | O_EXCL))
  {
    error("file.open");
  }
  Serial.print("Saving at ");
  Serial.println(fileName);
}
// -----------------------------------------------//
void SDCard::csvHeader()
{
  this->logFile.println(F("Data, Temperatura, Umidade"));
}
// -----------------------------------------------//
void SDCard::logData(String date, float temp, float humid)
{
    this->logFile.print(date);
    this->logFile.write(',');
    this->logFile.print(temp);
    this->logFile.write(',');
    this->logFile.print(humid);
    this->logFile.println();

    if (!logFile.sync() || logFile.getWriteError())
    {
      error("write error");
    }
}
// -----------------------------------------------//
