/* 
main.cpp
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#if 1
#include "display/waveshare.h"
#include "sensor/dist.h"
#include "sensor/reed.h"
#include "storage/csv.h"
#include "time/time.h"
#include "sleep/sleep.h"

#include <stdio.h>
#include <Arduino.h>


// Set LED_BUILTIN if it is not defined by Arduino framework
#ifndef LED_BUILTIN
    #define LED_BUILTIN 2
#endif

// # of cycles from deep sleep to wake. 
RTC_DATA_ATTR int boot_cnt = 0;

// Macro to pack two bits into one value 
#define STATE(s1, s2)  (((s1) << 1) | (s2))
// helpers for reading the states
#define GET_S1(state)    (((state) >> 1) & 1)
#define GET_S2(state)    (((state) >> 0) & 1)
uint8_t sensorStatus = STATE(0,0); //00:both off, 10: reed on dist off, 01: opposite of before, 11: both on. Does the EOL char mess this up?

void setup(){
  setup_waveshare();
  Serial.begin(9600);

  setup_ui();
  setup_dist();
  setup_reed();
    // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  boot_cnt++; 
}
void loop() { 
  int64_t reed_time = 0; // time last seen for reed switch
  uint8_t reed_prev_state = 0; // previous reed state
  int64_t start_time = 0; // stores time since
  int64_t active_time = 0; // amount of time spent active in ms
  int8_t reed_state = -2;
  int8_t dist_state = -2;
  while (1){
    reed_state = is_reed_active(&reed_time, &reed_prev_state);
    dist_state = is_dist_active();
/*     dist_state = 1;
    reed_state = 1; */
    Serial.print("Dista_state;");
    Serial.println(dist_state);
    if ((reed_state != 0 && reed_state != 1) ||
        (dist_state != 0 && dist_state != 1)) {
      Serial.println("::::: ERROR, sensor states are not valid");
      Serial.print("Dista_state, reeda state;");
      Serial.println(dist_state);
      Serial.println(reed_state);
      reed_state = 0;
      dist_state = 0;
    }

      
    // sensorStatus = STATE(reed_state,dist_state);
    sensorStatus = STATE(digitalRead(REED_PIN),dist_state);

    // state machine    
    switch (sensorStatus)
    {
    case STATE(0,0):
      /* both off, push hours to file, reset timer, going to sleep */
      Serial.println("::both off, push hours to file, reset timer, going to sleep");
      logging(active_time);
      // timer is reset upon boot
      go_sleep(reed_state, (gpio_num_t)REED_PIN);
      break;
    case STATE(0,1):
      /* distance sensor on but reed is off, stop timer */
      Serial.println("::distance sensor on but reed is off, stop timer");
      // if start time is something other than 0 active time can be updated
      active_time += (start_time ? (current_time_ms() - start_time) : 0);  
      start_time = 0;          
      break;
    case STATE(1,0):
      /* reed is on but distance sensor is off, stop timer */
      Serial.println("reed is on but distance sensor is off, stop timer");
      // if start time is something other than 0 active time can be updated
      active_time += (start_time ? (current_time_ms() - start_time) : 0);
      start_time = 0;
      break;    
    case STATE(1,1):
      /* both sensors are on, start timer */
      Serial.println("both sensors are on, start timer: timer status::::");
      if (start_time != 0){
        // donothing, timer has already started
      } else {
        start_time = current_time_ms();
      }
      Serial.println(start_time);
      break;        
    default:
      break;
    }
    Serial.println("Timer statii; Start, active, current");
    Serial.println(start_time);
    Serial.println(active_time);
    Serial.println(current_time_ms());
  
    // update screen
    update_screen(reed_state, 35);
    update_screen(dist_state, 50); // they are overlapping now.
  }
  delay(1000);

};

#endif