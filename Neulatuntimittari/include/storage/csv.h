/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>
// Read CSV into array
int get_hours();
// Write updated CSV
int save_hours();

/* Log time spent in active mode
  Check correct needle id 
  > add difference of end and start to corresponding field 
  > send array to be saved as csv
*/
int logging(int64_t time);