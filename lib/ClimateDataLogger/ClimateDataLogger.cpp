/* DHT 22 sensor
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the climate datalogger object

*/

#include "ClimateDataLogger.hpp"

ClimateDataLogger::ClimateDataLogger(DHT &dht22_1, DHT &dht22_2,
  LiquidCrystal_I2C& lcdS, StationRtc &rtc,
  uint8_t csPin, uint8_t greenLed, uint8_t redLed):
  dht_1(dht22_1),
  dht_2(dht22_2),
  lcd(lcdS),
  r(rtc),
  ledPins{greenLed, redLed}
{

}

// -----------------------------------------------//

void ClimateDataLogger::begin()
{
  for (size_t i = 0; i < N_LEDS; i++)pinMode(ledPins[i], OUTPUT);
  this->dht_1.begin();
  this->dht_2.begin();
  this->lcd.init();
  this->lcd.setBacklight(HIGH);
  this->lcd.clear();
  this->r.begin();
  this->logTime = SAMPLE_INTERVAL_MS;
}


// -----------------------------------------------//

void ClimateDataLogger::save()
{
  uint32_t currentMillis = millis();
  if(currentMillis - this->logTime > SAMPLE_INTERVAL_MS)
  {
    digitalWrite(this->ledPins[0], HIGH);
    this->logTime = currentMillis - 1;
    this->readTemp(), this->readHum();
  }
}

// -----------------------------------------------//

float ClimateDataLogger::readTemp()
{
  float temp = this->dht_1.readTemperature();
  this->lcd.setCursor(0, 0);
  if (this->lastTemp > temp)
  {
    for (size_t i = 0; i < 16; i++)
    {
      this->lcd.print(" ");
    }
    this->lcd.setCursor(0, 0);
  }
  this->lcd.print(temp);
  this->lcd.print(" *C");
  this->lastTemp = temp;
  return temp;
}

// -----------------------------------------------//

float ClimateDataLogger::readHum()
{
  float humid = this->dht_1.readHumidity();
  this->lcd.setCursor(0, 1);
  if (this->lastHumid > humid)
  {
    for (size_t i = 0; i < 16; i++)
    {
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
  }
  this->lcd.print(humid);
  this->lcd.print(" %");
  this->lastHumid = humid;
  return humid;
}

// -----------------------------------------------//
