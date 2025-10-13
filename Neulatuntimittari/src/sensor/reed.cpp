/*
reed switch functionality
Karri Korsu 2025
*/

/* This has some fiddly weirdness still. Doesn't always activate when it should
  * It could be because in my test setup the magned doesn't go far away
    enough so that the reed opens/closes.
  -> it is because polling is too slow -> move to interrupt
*/
#include "sensor/reed.h"
#include "time/time.h"

volatile int64_t reed_timestamp = 0;

/* Interrupt function for polling reed switch */
void IRAM_ATTR reed_isr()
{
  // update timestamp
  reed_timestamp = current_time_ms();
  /*   Serial.println("interrupt");
    Serial.print(reed_timestamp); */
}

void setup_reed()
{
  // REED SWITCH
  pinMode(REED_PIN, INPUT_PULLUP); // Digital input
  attachInterrupt(REED_PIN, reed_isr, CHANGE);
}

/* Compare current time with when reed was last switched
  return 0 if timestamp difference is bigger than allowed
  return -1 if something weird has happened
  otherwise return 1
*/
int8_t is_reed_active()
{
  int64_t diff = reed_timestamp ? (current_time_ms() - reed_timestamp) : 0;
  Serial.print("diff=");
  Serial.println(diff);
  if (diff >= 0 && diff < MAX_INTERVAL)
    return diff ? 1 : 0;
  else if (diff < 0)
    return -1;
  else
    return 0;
}
