/* 
button functionality
not a sensor but hey
Karri Korsu 2025
*/
#pragma once
#include <stdint.h>
#include <Arduino.h>
#define BTN_PIN
#define SLOW_THRHLD 5000

void IRAM_ATTR btn_isr();
void setup_btn();
int8_t fast_click(); // Cycle through styli
int8_t slow_click(); // Set current stylus hours to 0
