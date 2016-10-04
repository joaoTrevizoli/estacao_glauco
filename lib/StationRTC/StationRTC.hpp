/*StationRtc
    __ _       _      ___   ___  _  _    __
  / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /   | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \   | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\  |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Interface of the Real time Clock DS1307 object

Created by: Joao Trevizoli Esteves
*/

#ifndef STATIONRTC_HPP
#define  STATIONRTC_HPP

// -----------------------------------------------//

#if ARDUINO >= 100
 #include "Arduino.h"
#endif
#include <RTClib.h>
#include "Format.h"

// -------------------------Class Interface---------------------------------- //

class StationRtc
{
public:
  StationRtc();
  void begin();
  String dateTimeNow();
private:
  String formatDateTime(int n);
  RTC_DS1307 rtc;
};

#endif
