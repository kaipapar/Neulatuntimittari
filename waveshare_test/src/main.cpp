// GxEPD2_HelloWorld.ino by Jean-Marc Zingg
//
// Display Library example for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display: https://www.good-display.com/companyfile/32/
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// Supporting Arduino Forum Topics (closed, read only):
// Good Display ePaper for Arduino: https://forum.arduino.cc/t/good-display-epaper-for-arduino/419657
// Waveshare e-paper displays with SPI: https://forum.arduino.cc/t/waveshare-e-paper-displays-with-spi/467865
//
// Add new topics in https://forum.arduino.cc/c/using-arduino/displays/23 for new questions and issues

// see GxEPD2_wiring_examples.h for wiring suggestions and examples
// if you use a different wiring, you need to adapt the constructor parameters!

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
#if 1
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// select the display class and display driver class in the following file (new style):
#include "GxEPD2_display_selection_new_style.h"

// or select the display constructor line in one of the following files (old style):
#include "GxEPD2_display_selection.h"
#include "GxEPD2_display_selection_added.h"

// alternately you can copy the constructor from GxEPD2_display_selection.h or GxEPD2_display_selection_added.h to here
// e.g. for Wemos D1 mini:
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEH0154D67

// for handling alternative SPI pins (ESP32, RP2040) see example GxEPD2_Example.ino
#include <time.h>
#include <stdio.h>
#include <stdio.h>
#include <Arduino.h>


// Set LED_BUILTIN if it is not defined by Arduino framework
#ifndef LED_BUILTIN
    #define LED_BUILTIN 2
#endif

const char HelloWorld[] = "Hello World!";

uint16_t dist_status = analogRead(39);
uint16_t dist_status_prev = 0;

static char * current_time(){
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
void helloWorld()
{

  int16_t tbx, tby; uint16_t tbw, tbh;
  char *time_now = current_time();
  display.getTextBounds(time_now, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = wh;
  uint16_t x = 0;
  uint16_t y = wy;
  display.firstPage();
  display.setFullWindow();
  display.setCursor(x, y);
  display.print(time_now);
  display.nextPage();
  display.setCursor(x, display.height()/1.5);
  display.print(time_now);
  display.nextPage();
  // display.clearScreen();
  display.hibernate();
  
}

void setup_ui() {
// Setting up static UI elements
  const char * static_elements[] = {"Time: ", "Status: ","Uptime: ","Distance: ", "Reed Switch: "};
  uint16_t y, x;
  y = x = 0;
  y = FreeMonoBold9pt7b.yAdvance;
  x = 5;
  display.firstPage();
  display.setFullWindow();
  do {
    display.setCursor(x, y);
    display.print(static_elements[0]);
    display.setCursor(x, y+20);
    display.print(static_elements[1]);
    display.setCursor(x, y+40);
    display.print(static_elements[2]);
    display.setCursor(x, y+60);
    display.print(static_elements[3]);
    display.setCursor(x, y+80);
    display.print(static_elements[4]);
  }while (display.nextPage());
}

void update_dist(){
// updating dynamic UI elements
  uint16_t x = display.width() / 3;
  uint16_t y = 0;
  uint16_t w = 50;
  uint16_t h = 30;  
  display.setPartialWindow(x,y,w,h);
  display.firstPage();
  Serial.println("Updating dist *****");
  Serial.print("Dist status::: ");
  Serial.println(dist_status);
  do {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);

    display.setCursor(x,y+FreeMonoBold9pt7b.yAdvance);
    display.print(dist_status);

  }while (display.nextPage());  
}
void update_input(uint16_t input,
                  uint16_t y = 0,
                  uint16_t x = display.width() / 3,
                  uint16_t w = 50,
                  uint16_t h = 30){
  // Generic function
  display.setPartialWindow(x,y,w,h);
  display.firstPage();
  Serial.println("Updating *****");
  Serial.print("status::: ");
  Serial.println(input);
  do {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);

    display.setCursor(x,y+FreeMonoBold9pt7b.yAdvance);
    display.print(input);

  }while (display.nextPage());  
}

void setup_ir_sensor() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(25,INPUT); // Digital input
  //pinMode(39, INPUT); // Analog input
  pinMode(26, OUTPUT); // Enable output
  digitalWrite(26, HIGH);
  Serial.println("IR Setup **********\n");
}

void setup()
{
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  Serial.begin(115200);

  setup_ui();
  setup_ir_sensor();

}
void loop() { 
/*   helloWorld();
  delay(10000); */
  
  // if (dist_status_prev != dist_status)
  dist_status = analogRead(39);

  update_input(dist_status);
  dist_status_prev = dist_status;
  delay(1000);
};

#endif