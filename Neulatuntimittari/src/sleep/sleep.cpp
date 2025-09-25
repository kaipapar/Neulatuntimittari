/* 
sleeping functionality
Karri Korsu 2025
https://github.com/kaipapar/Neulatuntimittari
*/
#include "sleep/sleep.h"
#include <Arduino.h>
//Sleep
#include "esp_sleep.h"
//#include "driver/rtc_io.h"

void go_sleep(uint8_t state, gpio_num_t wakeup_pin){
// 1. disable reed pin as gpio pin 2. activate it as wakeup pin
// 3. go to sleep
    Serial.println("Going to sleep");
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
    //gpio_set_direction((gpio_num_t)REED_PIN, GPIO_MODE_DISABLE);
    //rtc_gpio_pullup_en((gpio_num_t)REED_PIN);
    Serial.print("State from gosleep: ");
    Serial.println(state);
    if (state){
        esp_sleep_enable_ext0_wakeup(wakeup_pin,LOW);
    } else {
        esp_sleep_enable_ext0_wakeup(wakeup_pin,HIGH);
    }
    esp_deep_sleep_start();
}