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
  double current_time_ms = (double)esp_timer_get_time() / 1000.0;
  return (int64_t) floor(current_time_ms);
}

/* Returns: 
    active time (difference between start and now)
    or 0 */
int64_t get_active_time(int64_t start){
    // if start time is something other than 0 active time can be updated
    return (start ? (current_time_ms() - start) : 0);
}

uint16_t convert_ms_h(uint64_t ms){
  uint16_t hours = 0;
  hours = floor((ms/1000)/3600);
  return hours;
}

uint16_t convert_ms_m(uint64_t ms){
  uint16_t minutes = 0;
  minutes = floor((ms/1000)/60);
  return minutes;
}