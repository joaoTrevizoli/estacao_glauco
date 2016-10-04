/* Errors
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the climate datalogger object

Created by: Barbara Panosso
*/


#ifndef ERRORS_HPP
#define  ERRORS_HPP


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <EEPROM.h>

// -----------------------------------------------//

class Errors
{
public:
  Errors();
  virtual bool log_errors(String status, String clasS, String function, String message);
  virtual void printErrors(const char *msg);
  virtual void save_errors(String post);  // save to eeprom and sd
  virtual void del_errors(); // delete to eeprom
  virtual void checkStatusCodePost(int code, String post);

private:


};

#endif
