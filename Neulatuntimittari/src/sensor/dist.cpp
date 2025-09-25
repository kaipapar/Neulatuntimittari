/* 
distance sensor (IR) functionality
Karri Korsu 2025
*/
#include "sensor/dist.h"
#include <stdint.h>
#include <Arduino.h>

void setup_dist(){
    pinMode(DIST_PIN, OUTPUT); // Enable output
    digitalWrite(DIST_PIN, HIGH);
    Serial.println("IR Setup **********\n");
}

int8_t is_dist_active(){
  uint16_t dist_status = analogRead(DIST_PIN);
  Serial.println("::: HEllo from dist function::");
  Serial.print(dist_status);
  return (dist_status > 100) ? 1 : 0;
}