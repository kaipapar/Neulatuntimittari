/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>

#define ROWS 2    // adjust for your file
#define COLS 10   // adjust for max columns per row
#define STYLI 1   // index of id in table
#define HOURS 0   // index of hours in table

struct hours_active {
  uint64_t hours[COLS];
  int8_t active;
};

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
uint8_t log_hours(uint64_t time, uint64_t* field);
uint8_t print_table(uint64_t array[ROWS][COLS]);

uint8_t get_struct_csv(hours_active* id_hours);
uint8_t save_struct_csv(hours_active* id_hours);