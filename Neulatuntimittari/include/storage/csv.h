/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>

#define ROWS 10   // adjust for your file
#define COLS 10   // adjust for max columns per row

int setup_littlefs();
// Read CSV into array
uint8_t get_hours_csv(uint64_t array[ROWS][COLS]);
// Write updated CSV
uint8_t save_hours_csv(uint64_t array[ROWS][COLS]);

/* Log time spent in active mode
  Check correct needle id 
  > add difference of end and start to corresponding field 
  > send array to be saved as csv
*/
int logging(int64_t time);

uint8_t print_table(uint64_t array[ROWS][COLS]);