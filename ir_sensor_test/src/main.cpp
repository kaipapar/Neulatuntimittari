/*
 * main
 * Takes in an analog and digital input prints the contents of both to serial,
 * Also sets an enable pin to high
 * Used to test sensor modules.
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
  pinMode(25,INPUT); // Digital input
  //pinMode(39, INPUT); // Analog input
  pinMode(26, OUTPUT); // Enable output
  Serial.begin(9600); // Serial setup 
  digitalWrite(26, HIGH);
  Serial.println("Setup");
}

void loop()
{
  int statusD = digitalRead(25);
  int statusA = analogRead(39);

  Serial.print("Output:");
  Serial.print("\t Analog:");
  Serial.print(statusA);
  Serial.print("\t Digital:");
  Serial.println(statusD);

  delay(500);  
}
