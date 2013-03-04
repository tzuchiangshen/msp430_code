/**
 * blink.ino - blink test
 *
 * Pins Used: RED_LED, GREEN_LED, PUSH2
 *
 */

#define SMALL_INIT4 /* don't initialize .bss and .data sections */
#include <main.h>

void setup() {

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

  RED_LED::toggle();
  GREEN_LED::toggle();

  delay_msecs(500);
}
