/* 
button functionality
not a sensor but hey
Karri Korsu 2025
*/

#include "sensor/button.h"
#include "time/time.h"

volatile int64_t btn_timestamp = 0;
#ifdef ARDUINO
/* Interrupt function for polling push button */
void IRAM_ATTR btn_isr() 
{
  btn_timestamp = current_time_ms();
}

void setup_btn()
{
  pinMode(BTN_PIN, INPUT_PULLUP);
  attachInterrupt(BTN_PIN, btn_isr, CHANGE); // Should it be rising or falling
}
#endif
/* Cycle through styli */
int8_t fast_click(int8_t* current_i)
{
  DebugPrintPair("button.cpp: active stylus i: ", *current_i);
  if (*current_i < COLS)
    *current_i++;    
  else if (*current_i == COLS)
    *current_i = 0;
  else{ // its something weird
    DebugPrintPair("ERROR: button.cpp: active stylus i: ", *current_i);
    *current_i = 0;
    return 1;
  } 
  return 0;
}

/* Set current stylus hours to 0 */
int8_t slow_click(uint64_t* hours)
{
  *hours = 0;
  return 0;
}

int8_t btn_release(hours_active* id_hours, int8_t btn_state)
{
  if (btn_state == 1 || btn_timestamp == 0)
    return 1;

  click_logic(id_hours);
  btn_timestamp = 0;
  return 0;
}

int8_t click_logic(hours_active* id_hours)
{
  int64_t diff = btn_timestamp ? (current_time_ms() - btn_timestamp) : 0;
  if (diff >= DEBOUNCE && diff < SUPER_SLOW){
    if (diff >= SLOW_THRHLD)
      return slow_click(&id_hours->hours[id_hours->active]);
    else
      return fast_click(&id_hours->active);
  }// do nothing
  return 1;
}

int8_t get_active(uint64_t array[COLS]){
  uint8_t index = 0;
  while (index < COLS){
    if (array[index] == 1)
      break;
    index += 1;
  }
  return index;
}