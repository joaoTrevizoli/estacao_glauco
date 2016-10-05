/*DS18b20
    __  _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Interface of the DS18b20 Sensor object

Created by: João Trevizoli Esteves
*/

#ifndef PHOTORESISTOR_HPP
#define  PHOTORESISTOR_HPP

#include <Arduino.h>


#define PHOTORESISTOR_DEBUG 1

class Photoresistor
{
public:
  Photoresistor(int pin);
  void begin();
  int rawLuminosity();

private:
  int analogPin;
};

#endif
