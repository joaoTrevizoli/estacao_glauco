/*SoilMoisture
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the Soil Moisture Sensor

Created by: João Trevizoli Esteves
*/

#include "Photoresistor.hpp"

// -------------------------Init method-------------------------------------- //

Photoresistor::Photoresistor(int pin)
{
  this->analogPin = pin;
}

// -------------------------Public methods----------------------------------- //

void Photoresistor::begin()
{
  pinMode(this->analogPin, INPUT);
}

// -------------------------------------------------------------------------- //


int Photoresistor::rawLuminosity()
{
  #if PHOTORESISTOR_DEBUG
    Serial.print("Raw luminosity measurement: ");
    Serial.println(analogRead(this->analogPin));
  #endif
  return analogRead(this->analogPin);
}

// -------------------------------------------------------------------------- //
