/* 
button functionality
not a sensor but hey
Karri Korsu 2025
*/
#pragma once

#include <stdint.h>
#include "storage/csv.h"

#define BTN_PIN 15
#define SLOW_THRHLD 5000
#define SUPER_SLOW 8000 // if button is accidentally pressed for too long
#define DEBOUNCE 100

#ifdef ARDUINO
#include <debug_serial.h>
void IRAM_ATTR btn_isr();
void setup_btn();
#endif

int8_t fast_click(uint64_t active_styli[COLS]); // Cycle through styli
int8_t slow_click(uint64_t* hours); // Set current stylus hours to 0
int8_t btn_release(uint64_t array[ROWS][COLS]);
int8_t click_logic(uint64_t array[ROWS][COLS]);
int8_t get_active(uint64_t array[COLS]);