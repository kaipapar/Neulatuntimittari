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

#include <stdio.h>
#include <Arduino.h>
#include <math.h>

// Timer
#include "esp_timer.h"
#include <time.h>

//Filesystem
#include "LittleFS.h"

//Sleep
#include "esp_sleep.h"
//#include "driver/rtc_io.h"


// Set LED_BUILTIN if it is not defined by Arduino framework
#ifndef LED_BUILTIN
    #define LED_BUILTIN 2
#endif
#define REED_PIN 25
#define DIST_PIN 39

// # of cycles from deep sleep to wake. 
RTC_DATA_ATTR int boot_cnt = 0;

// Macro to pack two bits into one value 
#define STATE(s1, s2)  (((s1) << 1) | (s2))
// helpers for reading the states
#define GET_S1(state)    (((state) >> 1) & 1)
#define GET_S2(state)    (((state) >> 0) & 1)
uint8_t sensorStatus = STATE(0,0); //00:both off, 10: reed on dist off, 01: opposite of before, 11: both on. Does the EOL char mess this up?


// max time difference between reed switch activations
#define MAX_INTERVAL 5000

static char * current_time_str(){
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
void helloWorld() // not in use
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  char *time_now = current_time_str();
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
void setup_io() {
// IR SENSOR
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(DIST_PIN, INPUT); // Analog input
  pinMode(26, OUTPUT); // Enable output
  digitalWrite(26, HIGH);
  Serial.println("IR Setup **********\n");
// REED SWITCH
  pinMode(25,INPUT_PULLUP); // Digital input
}

void update_dist() // not in use
{
// updating dynamic UI elements
  uint16_t x = display.width() / 3;
  uint16_t y = 0;
  uint16_t w = 50;
  uint16_t h = 30;  
  display.setPartialWindow(x,y,w,h);
  display.firstPage();
  Serial.println("Updating dist *****");
  Serial.print("Dist status::: ");
  // Serial.println(dist_status);
  do {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);

    display.setCursor(x,y+FreeMonoBold9pt7b.yAdvance);
    // display.print(dist_status);

  }while (display.nextPage());  
}

/*Generic function for waveshare prints 
  min y dist between two elements= */
void update_screen(uint16_t input,
                  uint16_t y = 0,
                  uint16_t x = display.width() / 3,
                  uint16_t w = 50,
                  uint16_t h = 30){
  display.setPartialWindow(x,y,w,h);
  display.firstPage();
/*   Serial.println("Updating *****");
  Serial.print("status::: ");
  Serial.println(input); */
  do {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);

    display.setCursor(x,y+FreeMonoBold9pt7b.yAdvance);
    display.print(input);

  }while (display.nextPage());  
}
// Read CSV into array
int get_hours(){
  // LittleFS
  // Read CSV to 2d array 
  File file = LittleFS.open("/id_hours.csv");
  if(!file){
    Serial.println("Failed to open file for reading");
    return 0;
  }
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  return 0;
} 
// Write updated CSV
int save_hours(){
  return 0;
}
/* Log time spent in active mode
  Check correct needle id 
  > add difference of end and start to corresponding field 
  > send array to be saved as csv
*/
int logging(int64_t start, int64_t end) {
  
  return 0;
}

/* This has some fiddly weirdness still. Doesn't always activate when it should 
  * It could be because in my test setup the magned doesn't go far away
    enough so that the reed opens/closes.
*/
int8_t is_reed_active(int64_t* prev_time, uint8_t* prev_state){
  uint8_t current_state = digitalRead(25);
  // int32_t current_time = current_time_int();
  int64_t current_time = current_time_ms();

  int8_t state = -1;
  Serial.println("Current time, prev_time");
  Serial.print(current_time);
  Serial.print(":::");
  Serial.println(*prev_time);
  if (current_state != *prev_state){
    if ((current_time - *prev_time) > MAX_INTERVAL) {
      state = 0;
    } else if ((current_time - *prev_time) < 0) {
      // variables have wrapped or some other weirdness has happened
      state = -1;
      return state;
    } else {
      state = 1;
    }
  *prev_time = current_time;
  *prev_state = current_state;
  } else {
    state = 0;
  }
  return state;
}

int8_t is_dist_active(){
  uint16_t dist_status = analogRead(DIST_PIN);
  Serial.println("::: HEllo from dist function::");
  Serial.print(dist_status);
  return (dist_status > 100) ? 1 : 0;
}

void go_sleep(uint8_t state){
// 1. disable reed pin as gpio pin 2. activate it as wakeup pin
// 3. go to sleep
    Serial.println("Going to sleep");
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
    //gpio_set_direction((gpio_num_t)REED_PIN, GPIO_MODE_DISABLE);
    //rtc_gpio_pullup_en((gpio_num_t)REED_PIN);
    if (state){
        esp_sleep_enable_ext0_wakeup((gpio_num_t)REED_PIN,LOW);
    } else {
        esp_sleep_enable_ext0_wakeup((gpio_num_t)REED_PIN,HIGH);
    }
    esp_deep_sleep_start();
}

void setup(){
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  Serial.begin(9600);

  setup_ui();
  setup_io();
  boot_cnt++; 
}
void loop() { 
  int64_t reed_time = 0; // time last seen for reed switch
  uint8_t reed_prev_state = 0; // previous reed state
  int64_t start_time = 0; // stores time since
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

      
    sensorStatus = STATE(reed_state,dist_state);
  
    // state machine    
    switch (sensorStatus)
    {
    case STATE(0,0):
      /* both off, push hours to file, reset timer, going to sleep */
      Serial.println("::both off, push hours to file, reset timer, going to sleep");
      logging(start_time, esp_timer_get_time());
      // timer is reset upon boot
      go_sleep(reed_state);
      break;
    case STATE(0,1):
      /* distance sensor on but reed is off, stop timer */
      Serial.println("::distance sensor on but reed is off, stop timer");
      break;
    case STATE(1,0):
      /* reed is on but distance sensor is off, stop timer */
      Serial.println("reed is on but distance sensor is off, stop timer");
      break;    
    case STATE(1,1):
      /* both sensors are on, start timer */
      Serial.println("both sensors are on, start timer: timer status::::");
      if (start_time != 0){
        // donothing, timer has already started
      } else {
        start_time = esp_timer_get_time();
      }
      Serial.println(start_time);
      break;        
    default:
      break;
    }
    // update screen
    update_screen(reed_state, 35);
    update_screen(dist_state, 50); // they are overlapping now.
  }
  delay(1000);

};

#endif