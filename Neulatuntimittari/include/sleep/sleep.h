/* 
sleeping functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>
#include <Arduino.h>
void go_sleep(uint8_t state, gpio_num_t wakeup_pin);