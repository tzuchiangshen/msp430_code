/**
 * blink.cpp - blink test
 *
 * Pins Used: RED_LED, GREEN_LED, PUSH2
 */

#include <fabooh.h>
#include <pins.h>

#define SMALL_INIT4 /* don't initialize .bss and .data sections */
#include <main.h>

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PUSH2, INPUT_PULLUP);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}

void loop() {
  // block loop if user holds down the button
  if ( !digitalRead(PUSH2) ) {
    do {
      delay(10); // debounce the button
    } while(!digitalRead(PUSH2));
  }

  RED_LED::toggle();
  GREEN_LED::toggle();
  delay(100);
}
