/* 
waveshare epaper display functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/

#include "display/waveshare.h"

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
// select the display class and display driver class in the following file (new style):
#include "display/GxEPD2_display_selection_new_style.h"
// or select the display constructor line in one of the following files (old style):
#include "display/GxEPD2_display_selection.h"
#include "display/GxEPD2_display_selection_added.h"

#include "time/time.h"

void setup_waveshare(){
    //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
}

void print_time_now() // not in use
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
                  uint16_t y,
                  uint16_t x,
                  uint16_t w,
                  uint16_t h){
  if(x==0){
    x=display.width() / 3;
  }
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