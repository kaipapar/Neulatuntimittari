/* 
button functionality
not a sensor but hey
Karri Korsu 2025
*/

#include "sensor/button.h"
#include "time/time.h"

volatile int64_t btn_timestamp = 0;

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
/* Cycle through styli */
int8_t fast_click(uint64_t active_styli[COLS])
{
  int8_t current_i = get_active(active_styli);
  active_styli[current_i] = 0;
  if (current_i < COLS)
    active_styli[current_i+1] = 1;    
  else 
    active_styli[0] = 1;
  return 0;
}

/* Set current stylus hours to 0 */
int8_t slow_click(uint64_t* hours)
{
  *hours = 0;
  return 0;
}

int8_t btn_release(uint64_t table[ROWS][COLS])
{
  int8_t pressed = !digitalRead(BTN_PIN);
  if (pressed) {
    return 1;
  } else {
    click_logic(table);
    btn_timestamp = 0;
  }
  return 0;
}

int8_t click_logic(uint64_t table[ROWS][COLS])
{
  int64_t diff = btn_timestamp ? (current_time_ms() - btn_timestamp) : 0;
  if (diff >= DEBOUNCE && diff < SUPER_SLOW){
    if (diff >= SLOW_THRHLD)
      return slow_click(&table[0][get_active(table[1])]);
    else
      return fast_click(table[1]);
  }// do nothing
  return 1;
}