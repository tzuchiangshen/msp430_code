/**
 * blink.cpp - blink test
 *
 * Pins Used: RED_LED, GREEN_LED, PUSH2
 *
 */

#include <fabooh.h>

#define SMALL_INIT4 /* don't initialize .bss and .data sections */
#include <main.h>

using namespace GPIO;

inline void setup() {

  RED_LED::pinMode(OUTPUT);
  GREEN_LED::pinMode(OUTPUT);
  PUSH2::setmode_inputpullup();

  GREEN_LED::low();
  RED_LED::high();

}

void loop() {
  
  // block loop if user holds down the button
  if ( !PUSH2::read() ) {
    do {
      delay_msecs(10); // debounce switch
    } while(!PUSH2::read());
  }

  delay_msecs(100);
  if ( 1 /* same port do both at the same time*/) {
    RED_LED::toggle_pins(RED_LED::pin_mask|GREEN_LED::pin_mask);
  }
  else {
    RED_LED::toggle();
    GREEN_LED::toggle();
  }
}
