#include "tolarentern.h"

void lantern_on(){
  digitalWrite(LANTERN_PIN, LOW);
}

void lantern_off(){
  digitalWrite(LANTERN_PIN, HIGH);
}

void led_on(){
  digitalWrite(LANTERN_PIN, HIGH);
}

void led_off(){
  digitalWrite(LANTERN_PIN, LOW);
}
