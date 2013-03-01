FABOOH - as in FABricate meets OOH La La
----------------------------------------
Fabooh is an optimized C++ template based peripheral framework for the
msp430 microcontroller.  It creates very small and efficient code while
still providing a flexible framework akin to what you might expect in
Energia without needless overhead.  It makes liberal use of inline
msp430-gcc assembler code to produce optimized code that is sometimes
smaller than generic 'C' code.

A typical blink program looks something like this:

[code]
#include <fabooh.h>
#include <main.h>
using namespace GPIO;

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
      delay_msecs(10); // debounce switch
    } while(!PUSH2::read());
  }

  delay_msecs(100);
  RED_LED::toggle();
  GREEN_LED::toggle();
}
[/code]

