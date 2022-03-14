#include "tolarentern.h"

#define DATA_PIN 27
#define LANTERN_PIN 33
#define LED_PIN 32

void lantern_on(){
  digitalWrite(LANTERN_PIN, LOW);
}

void lantern_off(){
  digitalWrite(LANTERN_PIN, HIGH);
}

void led_on(){
  digitalWrite(LANTERN_PIN, HIGH);
}

void led_on(){
  digitalWrite(LANTERN_PIN, LOW);
}

void blinking_led(void* arg){
  int blinking_time_msec = 500; // msec
  while (1) {
    led_on();
    vTaskDelay(blinking_time_usec);
    led_off();
    vTaskDelay(blinking_time_usec);
  }
}

void blinking_led(void* arg){
  int blinking_time_usec = 1000; // msec
  while (1) {
    lantern_on();
    vTaskDelay(blinking_time_usec);
    lantern_off();
    vTaskDelay(blinking_time_usec);
  }
}
