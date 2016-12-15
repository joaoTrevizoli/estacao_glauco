/*DS18b20
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the DS18b20 Sensor object

Created by: Barbara Panosso
*/

#include "DS18b20.hpp"

// -------------------------Init method-------------------------------------- //

DS18b20::DS18b20(DallasTemperature &dallasAdd,  uint32_t updateInterval):
sensors(dallasAdd)
{
  this->previousUpdate = 0;
  this->updateInterval = updateInterval;
  this->restartInterval = 3000;
  this->temperature = NAN;
}

// -------------------------Public methods----------------------------------- //
void DS18b20::begin()
{
  this->sensors.begin();
  if(this->checkSensor());
    this->searchForSensors();
}

// -------------------------------------------------------------------------- //

float DS18b20::getTemperature()
{
  this->update();
  return  this->temperature;
}

// -------------------------------------------------------------------------- //

bool DS18b20::checkSensor()
{
    if (!this->sensors.getAddress(this->thermometerAddr, this->one_wire_b))
    {
      #if BS18b20_DEBUG == 1
        Serial.println(ERROR_DS18B20_NOT_FOUND);
      #endif
      return false;
    }
    return true;
}

// -------------------------Private methods---------------------------------- //

void DS18b20::searchForSensors()
{
  #if BS18b20_DEBUG == 1
  Serial.println("Searching for One Wire sensors...");
  #endif
  if (this->checkSensor())
  {
    uint8_t numberOfSensors = this->sensors.getDeviceCount();
    if (numberOfSensors > 1)
    {
      #if BS18b20_DEBUG == 1
      Serial.print(format("It were found %d One Wire sensors\n",
       numberOfSensors));
       #endif
    }
    else
    {
      #if BS18b20_DEBUG == 1
      Serial.print("It were found 1 One Wire sensor\n");
      #endif
    }
    #if BS18b20_DEBUG == 1
      Serial.print(format("Sensor: "));
      this->printAddress(this->thermometerAddr);
      Serial.print("\n\n");
      #endif
  }
  else
  {
    #if BS18b20_DEBUG == 1
    Serial.println("It was't found any One Wire sensors");
    #endif
  }
}

// -------------------------------------------------------------------------- //

void DS18b20::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// -------------------------------------------------------------------------- //

bool DS18b20::setTemperature()
{
  if(!this->checkSensor())
  {
    #if BS18b20_DEBUG == 1
      Serial.println(ERROR_DS18B20_START);
    #endif
    return false;
  }
  this->sensors.requestTemperatures();
  this->temperature = sensors.getTempC(this->thermometerAddr);

  if(this->temperature == -127)
  {
    #if BS18b20_DEBUG == 1
      Serial.println(ERROR_DS18B20_ABSOLUTE_NEGATIVE_TEMP);
      #endif
    return false;
  }

  return true;

}

// -------------------------------------------------------------------------- //
bool DS18b20::update()
{
  if(this->checkSensor())
  {
    if ((millis() - this->previousUpdate > updateInterval) ||
     this->temperature == NAN)
    {
      this->previousUpdate = millis();
      this->setTemperature();
    }
  }
  else if ((millis() - this->previousUpdate > this->restartInterval))
  {
    this->begin();
    this->previousUpdate = millis();
  }
}

// -------------------------------------------------------------------------- //
