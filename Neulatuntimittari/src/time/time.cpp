/* 
time and timer related functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#include "time/time.h"

#include "esp_timer.h"
#include <time.h>
#include <math.h>


char * current_time_str(){
    time_t result;
    time(&result);
    static char buf[100];
    snprintf(buf,sizeof(buf), "The current time is %s(%jd seconds since the Epoch)\n",
               asctime(gmtime(&result)), (intmax_t)result);
    if (result != (time_t)(-1))
      return buf;
    else
      return "Error:", buf;
}
int64_t current_time_ms(){
  /* esp_timer_handle_t handle;
  esp_timer_create_args_t time_struct; */
  int64_t current_time_us = esp_timer_get_time();
  double current_time_ms = (double)current_time_us / 1000.0;
  return (int64_t) floor(current_time_ms);
}