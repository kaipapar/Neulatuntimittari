/*
 * Blink
 * Turns on builtin led when connection between power and pin 25 is made,
 * Used to test switching.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
#ifndef LED_BUILTIN
    #define LED_BUILTIN 2
#endif

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(25,INPUT);
  Serial.begin(9600);

}

int status = 0;
void loop()
{
  int status = digitalRead(25);
  if (status == HIGH) {
    digitalWrite(LED_BUILTIN, 1);
  } else {
    digitalWrite(LED_BUILTIN, 0);
  }
  // Serial.println("Output:");
  // Serial.println(status);
  // delay(1000);  
}
