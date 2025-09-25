/* 
time and timer related functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>

char * current_time_str();
int64_t current_time_ms();
int64_t get_active_time(int64_t start);
uint64_t convert_ms_h(uint64_t ms);