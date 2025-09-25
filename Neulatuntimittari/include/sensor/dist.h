/* 
distance sensor (IR) functionality
Karri Korsu 2025
*/
#pragma once
#include <stdint.h>
#define DIST_PIN 39 // OR 26 ? 

void setup_dist();
int8_t is_dist_active();