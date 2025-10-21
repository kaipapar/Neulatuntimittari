/* 
button functionality
not a sensor but hey
Karri Korsu 2025
*/
#pragma once

#include <stdint.h>
#include "storage/csv.h"

#define BTN_PIN 13         //IO13/D7
#define SLOW_THRHLD 5000
#define SUPER_SLOW 8000   // if button is accidentally pressed for too long
#define DEBOUNCE 50

#ifdef ARDUINO
#include <debug_serial.h>
void IRAM_ATTR btn_isr();
void IRAM_ATTR btn_isr_end();
void setup_btn();
void attach_btn_isr();
void detach_btn_isr();
void zero_btn_timestamp();

#endif

int8_t fast_click(int8_t* current_i); // Cycle through styli
int8_t slow_click(uint64_t* hours); // Set current stylus hours to 0
int8_t btn_release(hours_active* id_hours);
int8_t click_logic(hours_active* id_hours, int64_t diff);
int8_t get_active(uint64_t array[COLS]);
