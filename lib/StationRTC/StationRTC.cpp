/*StationRtc
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of the Real time Clock DS1307 object

Created by: Joao Trevizoli Esteves
*/

#include "StationRTC.hpp"

// -------------------------Init method-------------------------------------- //
StationRtc::StationRtc():
  rtc()
{

}

// -------------------------Public methods----------------------------------- //

void StationRtc::begin()
{
  this->rtc.begin();
}

String StationRtc::formatDateTime(int n)
{
  String digits = String(n);
  if(digits.length() == 1)
  {
    digits = "0" + digits;
  }
  return digits;
}

// ---------------------------------------------------------------------------//

String StationRtc::dateTimeNow()
{
    if(!this->rtc.isrunning())
  {
      this->rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      this->rtc.begin();
      return "RTC parado";
  }
    DateTime timeStamp = rtc.now();

    String fmtDateTime = String(timeStamp.year()) + "-";
    fmtDateTime = fmtDateTime + this->formatDateTime(timeStamp.month()) + "-";
    fmtDateTime = fmtDateTime + this->formatDateTime(timeStamp.day()) + "T";

    fmtDateTime = fmtDateTime + this->formatDateTime(timeStamp.hour()) + ":";
    fmtDateTime = fmtDateTime + this->formatDateTime(timeStamp.minute()) + ":";
    fmtDateTime = fmtDateTime + this->formatDateTime(timeStamp.second());
    return fmtDateTime;
}


// -----------------------------------------------//
