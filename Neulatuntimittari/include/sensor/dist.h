/* 
distance sensor (IR) functionality
Karri Korsu 2025
*/
#pragma once
#include <stdint.h>
#define DIST_OUT_PIN 39
#define DIST_CS_PIN 26

void setup_dist();
int8_t is_dist_active();