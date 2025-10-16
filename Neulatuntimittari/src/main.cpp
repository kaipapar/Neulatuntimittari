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
#include <debug_serial.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

// \# of cycles from deep sleep to wake.
RTC_DATA_ATTR int boot_cnt = 0;

// Macro to pack two bits into one value
#define STATE(s1, s2) (((s1) << 1) | (s2))
// helpers for reading the states
#define GET_S1(state) (((state) >> 1) & 1)
#define GET_S2(state) (((state) >> 0) & 1)

void setup()
{
  setup_waveshare();
  Serial.begin(9600);

  setup_ui();
  setup_dist();
  setup_reed();
  setup_littlefs();
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  boot_cnt++;
}
void loop()
{
  int64_t start_time = 0;  // stores time since
  int64_t active_time = 0; // amount of time spent active in ms
  int8_t reed_state = -2;
  int8_t dist_state = -2;
  uint8_t sensorStatus = STATE(0, 0); // 00:both off, 10: reed on dist off, 01: opposite of before, 11: both on. Does the EOL char mess this up?
  uint64_t id_hours[ROWS][COLS] = {0};
  // for ui printing
  uint8_t stylus_id = 0;
  uint8_t hours = 0;
  get_hours_csv(id_hours);
  DebugPrintln(id_hours[0][0]);
  DebugPrint("^hours on startup");
  print_hours(convert_ms_m(id_hours[0][0])); // prints ms for easier testing
  delay(4000); // give time to poll reed on startup
  while (1)
  {
    reed_state = is_reed_active();
    dist_state = is_dist_active();
    if ((reed_state != 0 && reed_state != 1) ||
        (dist_state != 0 && dist_state != 1))
    {
      DebugPrintln("::::: ERROR, sensor states are not valid");
      DebugPrintPair("main.cpp.line68: dist_state: ", dist_state);
      DebugPrintPair("main.cpp.line69: reed_state: ", reed_state);      
      reed_state = 0;
      dist_state = 0;
    }

    sensorStatus = STATE(reed_state, dist_state);
    DebugPrintPair("main.cpp.line75: dist_state: ", dist_state);
    DebugPrintPair("main.cpp.line76: reed_state: ", reed_state);    
    switch (sensorStatus)
    {
    case STATE(0, 0):
      /* both off, push hours to file, reset timer, going to sleep */
      DebugPrintln(id_hours[0][0]);
      DebugPrintln("^hours prelog, hours postlog v");
      log_hours(active_time, &id_hours[0][0]); // should point to the correct needle id hours
      save_hours_csv(id_hours);
      delay(100); // give time for saving 
      print_status(2);
      print_hours(convert_ms_m(id_hours[0][0])); // prints ms for easier testing
      DebugPrint(id_hours[0][0]);
      // timer is reset upon boot
      get_hours_csv(id_hours);
      go_sleep(1, (gpio_num_t)REED_PIN);
      break;
    case STATE(0, 1):
      /* distance sensor on but reed is off, stop timer */
      // DebugPrintln("::distance sensor on but reed is off, stop timer");
      active_time += get_active_time(start_time);
      start_time = 0;
      print_status(1);
      break;
    case STATE(1, 0):
      /* reed is on but distance sensor is off, stop timer */
      // DebugPrintln("reed is on but distance sensor is off, stop timer");
      active_time += get_active_time(start_time);
      start_time = 0;
      print_status(1);
      break;
    case STATE(1, 1):
      /* both sensors are on, start timer */
      // DebugPrintln("both sensors are on, start timer: timer status::::");
      if (start_time != 0)
      {
        // donothing, timer has already started
      }
      else
      {
        start_time = current_time_ms();
      }
      print_status(0);
      ////DebugPrintln(start_time);
      break;
    default:
      break;
    }
  }
};

#endif