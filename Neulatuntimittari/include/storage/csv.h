/* 
LittleFS + CSV fileIO functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>

#define ROWS 1    // adjust for your file
#define COLS 10   // stylus + 9 hours
#define HOURS COLS-1   // 
#define STYLI 1   // index of id in table

struct hours_active {
  uint64_t hours[HOURS];
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
uint8_t print_array(uint64_t array[HOURS]);


uint8_t get_struct_csv(hours_active* id_hours);
uint8_t save_struct_csv(hours_active* id_hours);