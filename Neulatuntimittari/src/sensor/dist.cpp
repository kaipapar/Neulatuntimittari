/* 
distance sensor (IR) functionality
Karri Korsu 2025
*/
#include "sensor/dist.h"
#include <stdint.h>
#include <debug_serial.h>

void setup_dist(){
    pinMode(DIST_CS_PIN, INPUT); // Enable output
    digitalWrite(DIST_CS_PIN, HIGH);
    //DebugPrintln("IR Setup **********\n");
}

int8_t is_dist_active(){
  uint16_t dist_status = analogRead(DIST_OUT_PIN);
  //DebugPrintln("::: HEllo from dist function::");
  //DebugPrint(dist_status);
  return (dist_status > 100) ? 1 : 0;
}