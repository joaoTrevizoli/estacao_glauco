/* Errors
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the climate datalogger object

Created by: Barbara Panosso
*/

// #include "ConnectServer.hpp"
#include "Errors.hpp"

// ConnectServer Local;

Errors::Errors(){}


bool Errors::log_errors(String status, String cls, String function, String message)
{
  String send_msg;

  send_msg = "error=";
  send_msg += status;
  send_msg += "&class=";
  send_msg += cls;
  send_msg += "&function=";
  send_msg += function;
  send_msg += "&message=";
  send_msg += message;

}
// -------------------------------------------------------------------------- //

inline void Errors::printErrors(const char *msg)
{
  Serial.println(msg);
}
// -------------------------------------------------------------------------- //


void Errors::checkStatusCodePost(int StatusCode, String strpost)
{
  // receber status code servidor ou procurar na resposta servidor

  if(StatusCode != 200)
      save_errors(strpost);
  else
  return;

}

void Errors::save_errors(String post)
{
   //salva cartao e/ou eeprom
}

void Errors::del_errors()
{
  // deleta da eeprom
}
