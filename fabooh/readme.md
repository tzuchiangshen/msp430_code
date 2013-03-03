FABOOH - as in FABricate meets OOH la la
========================================
Fabooh is an optimized C++ template based peripheral framework for the
msp430 microcontroller.  It creates very small and efficient code while
still providing a flexible framework akin to what you might expect in
Energia with minimal overhead.  It makes liberal use of inline
msp430-gcc assembler code to produce optimized code that is sometimes
smaller than generic 'C' code.

Example
-------
A typical blink program looks something like this:

<pre>
<code>#include &lt;fabooh.h>
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
}</code>
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

Motivation
----------
I started with the msp430 when msp430-gcc didn't know about the value line chips. Most
of the examples supplied by Texas Instruments look like they were written by someone
took the asm code and just formatted it for 'C'. The differences between TIs CCS
and gcc were a pain. Most people were using CCS to write code and provide better
samples.  Still I wanted someting better.  

I really wanted a simple to use API. I liked the idea of Arduino API but the implemention
isn't really focused on small code or efficiency.  I contribute my time to the Energia
port of Arduino that runs on the msp430. I like it and we did try to be as efficient
as we could be within the confines of the Arduino framework

This code is my attempt to retain the goodness of the Energia framework while trying
to be as fast and effcient as I can be without worrying about breaking the Arduino
API.  The code makes frequent use of msp430-gcc ability to inline msp430 asm. If you
look at the implementation of the software only serial code, I don't know how you 
would do that in straight 'C'.  I try to use compile time decisions over runtime ones.
The way the GPIO class works assumes you know at compile time which pins and ports
you want to use and doesn't use up any space at runtime trying to figure that out.
Compare that with the table look up scheme that is done are runtime with Wiring based
frameworks. I think you will like the results with the small changes you have to make
in your coding style to take advantage of it.

Things have changed for the better. The msp430-gcc I'm using is based on 4.5.3 gnu. It
is fully featured and can be used with all the msp430 chips, value line chips included. 
Energia is being widely used so getting a working msp430-gcc is not really a problem.

With all that being said, it seemed that is was time to see if I can take advantage
of all that compiler infrastructure and make better use of it. 

Support
-------
I'm often on irc.freenode.net in #43oh  http://webchat.freenode.net/ #43oh  Constructive
comments welcome.
