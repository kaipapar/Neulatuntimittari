/* 
reed switch functionality
Karri Korsu 2025
*/

/* This has some fiddly weirdness still. Doesn't always activate when it should 
  * It could be because in my test setup the magned doesn't go far away
    enough so that the reed opens/closes.
*/
#include "sensor/reed.h"
#include "time/time.h"

#include <Arduino.h>

void setup_reed(){
// REED SWITCH
  pinMode(REED_PIN,INPUT_PULLUP); // Digital input
}

int8_t is_reed_active(int64_t* prev_time, uint8_t* prev_state){
  uint8_t current_state = digitalRead(25) ? 0 : 1; //flip
  // int32_t current_time = current_time_int();
  int64_t current_time = current_time_ms();

  int8_t state = -1;
  Serial.println("Current time, prev_time");
  Serial.print(current_time);
  Serial.print(":::");
  Serial.println(*prev_time);
  if (current_state != *prev_state){
    if ((current_time - *prev_time) > MAX_INTERVAL) {
      state = 0;
    } else if ((current_time - *prev_time) < 0) {
      // variables have wrapped or some other weirdness has happened
      state = -1;
      return state;
    } else {
      state = 1;
    }
  *prev_time = current_time;
  *prev_state = current_state;
  } else {
    state = 0;
  }
  return state;
}

