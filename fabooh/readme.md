FABOOH - as in FABricate meets OOH La La
========================================
Fabooh is an optimized C++ template based peripheral framework for the
msp430 microcontroller.  It creates very small and efficient code while
still providing a flexible framework akin to what you might expect in
Energia without needless overhead.  It makes liberal use of inline
msp430-gcc assembler code to produce optimized code that is sometimes
smaller than generic 'C' code.

Example:
========
A typical blink program looks something like this:

<pre>
<code>
  #include &lt;fabooh.h>
  #include &lt;main.h>
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
</code>
</pre>

This results in very efficient code that uses only 158 bytes of flash, and no DATA or BSS space.

Dependencies
------------

fabooh needs msp430-gcc version 4.6.3 or above. You can get a prebuilt mps430-gcc
binary for windows, OSX, or linux by downloading the Energia IDE ( http://energia.nu/downloads )
Energia is not required to use fabooh. However, some people do find its build environment easy
to use.

Usage
-----

To build all examples:
<pre>
 $ make clean all 
</pre>

To build and install the blink example using the defaults (msp430g2553):
<pre>
 $ cd examples/basic 
 $ make clean all install
</pre>

Credits
-------

* Many chunks of code have be used from various open source projects.
* Much inspiration has come from the Energia and Arduino API
* Big chunks of Kevin Timmerman's (oPossum) msp430 CCS code has been lifted and ported to msp430-gcc
* Robert Wessels' msp430 code provided insight into how to best use the msp430 peripherals
* This post http://mbed.org/users/igorsk/notebook/fast-gpio-with-c-templates/ got me thinking about
using C++ to provide a reasonable API without sacrificing speed and small code size.
