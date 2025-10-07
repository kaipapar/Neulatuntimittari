/* 
reed switch functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>
#define REED_PIN 25
// max time difference between reed switch activations
#define MAX_INTERVAL 5000

void setup_reed();
int8_t is_reed_active(int64_t* prev_time, uint8_t* prev_state);
