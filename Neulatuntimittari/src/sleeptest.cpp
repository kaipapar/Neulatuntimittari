/* Test deep sleep: wakeup and going to sleep
Show status on internal led
switch sleep and wakeup states via rtc gpio pin
*/
//works
#if 0
#define REED_PIN 25 // is rtc.
#define RTC_REED_PIN GPIO_NUM_25

#include <stdio.h>
#include <Arduino.h>
#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "esp_sleep.h"
void sleep(int state){
// 1. disable reed pin as gpio pin 2. activate it as wakeup pin
// 3. go to sleep
    Serial.println("Going to sleep");
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
    //gpio_set_direction(RTC_REED_PIN, GPIO_MODE_DISABLE);
    //rtc_gpio_pullup_en(RTC_REED_PIN);
    if (state){
        esp_sleep_enable_ext0_wakeup(RTC_REED_PIN,LOW);
    } else {
        esp_sleep_enable_ext0_wakeup(RTC_REED_PIN,HIGH);
    }
    esp_deep_sleep_start();
}

void wakeup(){
// 1. setup runs on wakeup
}

void setup() {
    Serial.begin(9600);
    //rtc_gpio_deinit(RTC_REED_PIN);
    // gpio_set_direction(RTC_REED_PIN,GPIO_MODE_INPUT);
    // gpio_set_pull_mode(RTC_REED_PIN, GPIO_PULLUP_ONLY);
    pinMode(25,INPUT_PULLUP);
    digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
// listen to sleep signal
    // int state = gpio_get_level(RTC_REED_PIN);
    int state = digitalRead(25);

    int prev_state = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    while(1){
        state = digitalRead(25);
        Serial.print("STATE:");
        Serial.println(state);
        if (state != prev_state){
            sleep(state);
        }
    
        prev_state = state;
        delay(500);
    }
}
#endif