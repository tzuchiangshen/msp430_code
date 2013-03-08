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
  RED_LED::set_mode(OUTPUT);
  GREEN_LED::set_mode(OUTPUT);
  PUSH2::set_mode(INPUT_PULLUP);

  GREEN_LED::low();
  RED_LED::high();
}

void loop() {
  // block loop if user holds down the button
  if ( !PUSH2::read() ) {
    do {
      delay_msecs(10); // debounce the button
    } while(!PUSH2::read());
  }

  RED_LED::toggle();
  GREEN_LED::toggle();
  delay_msecs(100);
}
