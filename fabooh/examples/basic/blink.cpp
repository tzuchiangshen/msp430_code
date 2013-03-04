/**
 * blink.cpp - blink test
 *
 * Pins Used: RED_LED, GREEN_LED, PUSH2
 */

#include <fabooh.h>

#define SMALL_INIT4 /* don't initialize .bss and .data sections */
#include <main.h>

inline void setup() {
  RED_LED::pinMode(OUTPUT);
  GREEN_LED::pinMode(OUTPUT);
  PUSH2::pinMode(INPUT_PULLUP);

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

  // toggle the port as the leds are on the same one
  RED_LED::toggle_pins(RED_LED::pin_mask|GREEN_LED::pin_mask);
  delay_msecs(100);
}
