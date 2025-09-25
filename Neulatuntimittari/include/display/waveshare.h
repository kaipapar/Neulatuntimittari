/* 
waveshare epaper display functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>

void setup_waveshare();
void print_time_now(); // not in use
void setup_ui();
void update_dist(); // not in use
/*Generic function for waveshare prints 
  min y dist between two elements= 
  Q: does accessing display.width in this header cause issues
  */
void update_screen(uint16_t input,
                  uint16_t y = 0,
                  uint16_t x = 0,
                  uint16_t w = 50,
                  uint16_t h = 30);