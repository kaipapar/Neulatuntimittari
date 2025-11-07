/* debug_serial.h
Override Serial.print and Serial.println methods
to use debug build flag
Karri Korsu 2025
*/

#pragma once

#include <Arduino.h>

#ifdef DEBUG
  #define DebugPrint(...)    Serial.print(__VA_ARGS__)
  #define DebugPrintln(...)  Serial.println(__VA_ARGS__)
  #define DebugPrintPair(a, b) do { Serial.print(a); Serial.println(b); } while (0)
#else
  #define DebugPrint(...)    do {} while (0)
  #define DebugPrintln(...)  do {} while (0)
  #define DebugPrintPair(a, b) do {} while (0)
#endif
