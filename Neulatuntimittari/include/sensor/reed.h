/* 
reed switch functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#pragma once
#include <stdint.h>
#include <Arduino.h>
#define REED_PIN 25
// max time difference between reed switch activations (ms)
#define MAX_INTERVAL 5000

void IRAM_ATTR reed_isr();
void setup_reed();
int8_t is_reed_active();
