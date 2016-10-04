/* Format
  __  _       _      ___   ___  _  _    __
 / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /  | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \  | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\ |_|\__,_|_.__/ \___/ \___/   |_|   /_/

prototype of format string functions

Created by: Joao Trevizoli Esteves
*/

#ifndef FORMAT
#define  FORMAT

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdarg.h>

String format(const char *strFormat, ...);
void printformat(const char *strFormat, ...);

#endif
