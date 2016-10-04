/* Format
  __  _       _      ___   ___  _  _    __
 / / | | __ _| |__  ( _ ) / _ \| || |   \ \
/ /  | |/ _` | '_ \ / _ \| | | | || |_   \ \
\ \  | | (_| | |_) | (_) | |_| |__   _|  / /
 \_\ |_|\__,_|_.__/ \___/ \___/   |_|   /_/

Implementation of format string functions

Created by: Joao Trevizoli Esteves
*/

#include "Format.h"

// -------------------------format------------------------------------------- //

String format(const char *strFormat, ...)
{
  int replacePosition = 0, lastPosition = 0, count = 0;
  String strToFormat = String(strFormat);
  String concatedString = "";

  for (size_t i=0; i<strToFormat.length(); i++) if(strToFormat[i]=='%') count++;
  if (count == 0)
    return "No formatable string were found";

  va_list argv;
  va_start(argv, count);

  for (size_t i = 0; i <count; i++)
  {
    replacePosition = strToFormat.indexOf('%', replacePosition + i);
    switch (strToFormat[replacePosition + 1])
    {
      case 'd':
      case 'D':
        concatedString += strToFormat.substring(lastPosition, replacePosition);
        concatedString += va_arg(argv, int);
        break;
      case 'f':
      case 'F':
      case 'l':
      case 'L':
        concatedString += strToFormat.substring(lastPosition, replacePosition);
        concatedString += va_arg(argv, double);
        break;
      case 'c':
      case 'C':
        concatedString += strToFormat.substring(lastPosition, replacePosition);
        concatedString += (char)va_arg(argv, int);
        break;
      case 's':
      case 'S':
        concatedString += strToFormat.substring(lastPosition, replacePosition);
        concatedString += va_arg(argv, const char *);
        break;
      default: ;
    }
    lastPosition = replacePosition + 2;
  }
  return concatedString;
}

// -------------------------sprintf------------------------------------------ //

void printformat(const char *strFormat, ...)
{
  uint8_t count = 0;
  String strToFormat = String(strFormat);

  for (size_t i=0; i<strToFormat.length(); i++) if(strToFormat[i]=='%') count++;

  va_list argv;
  va_start(argv, count);

  for (size_t i = 0; i < strToFormat.length(); i++)
  {
    if (strToFormat[i] == '%')
    {
      switch (strToFormat[i + 1])
      {
        case 'd':
        case 'D':
          Serial.print(va_arg(argv, int));
          break;
        case 'f':
        case 'F':
        case 'l':
        case 'L':
          Serial.print(va_arg(argv, double));
          break;
        case 'c':
        case 'C':
          Serial.print((char)va_arg(argv, int));
          break;
        case 's':
        case 'S':
          Serial.print(va_arg(argv, const char *));
          break;
        default: ;
      }
      i++;
    }
    else
    {
        Serial.print(strToFormat[i]);
    }
  }
}

// -------------------------enf of format string functions------------------- //
