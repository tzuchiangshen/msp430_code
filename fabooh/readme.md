FABOOH - \ˈfab-ü\ 
=================

Fabooh is an optimized C++ template based peripheral framework for the
msp430 microcontroller.  It creates very small and efficient code while
still providing a flexible framework similar to what you might expect 
to find with something like the Arduino API.  It makes liberal use of inline
msp430-gcc assembler code to produce optimized code that is sometimes
smaller than generic 'C' code.


Example
-------

A typical blink program looks something like this:

<pre>
<code>#include &lt;fabooh.h>
#include &lt;main.h>

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

This results in very efficient code that uses only 120 bytes of flash, and no DATA or BSS space.

Dependencies
------------

fabooh needs msp430-gcc version 4.6.3 or above. You can get a prebuilt mps430-gcc
binary for windows, OSX, or linux by downloading the Energia IDE ( http://energia.nu/downloads )
Energia is not required to use fabooh. However, some people do find its build environment easy
to use.

Usage
-----

Fabooh assumes a unix or unix-like shell environment (cygwin).  Makefiles drive
the build process.  It assumes that the msp430-gcc toolchain and mspdebug
is in your path. If you have a copy of naken430utils, it will use that to
compute cycle counts of your resulting asm code.

The directory tree mirrors what is required to run inside the Energia build system.
(Energia is not needed to use fabooh). However, I'm trying to provide the ability
to use fabooh as a target platform along side the standard Energia framework.
This might be useful for people who don't want to run command line make builds

* examples/ - where you find sample code for fabooh grouped in categories
* msp430/cores/fabooh/ - contains the fabooh framework header files
* msp430/cores/fabooh/drivers/ - contains peripheral drivers, things like serial, spi, led, lcd
* msp430/variants/ - these are the "boards" pin mapping for each chip and board supported

To build all examples:
<pre>
 $ make clean all 
</pre>

To build and install the blink example using the defaults (msp430g2553):
<pre>
 $ cd examples/basic 
 $ make clean all install
</pre>

Some important files.

* includes.mk - contains make rules used by all the samples. If you want to
switch boards you would edit this and find the line where the board
and chip files are included
* include-msp430fr5739.mk - will allow you to compile for the Fraunchpad
* include-msp430g2231in14.mk - for the launchpad with a g2231 chip, It
is setup for 16MHz instead of the default 1MHz, you will have to tweak
the DCO values in cpu430.h for your chip, or change the F_CPU to 1000000
* include-msp430g2553in29.mk - this is the default using 16MHz g2553 chip


Credits
-------

* Much inspiration has come from the Energia and Arduino API
* Big chunks of Kevin Timmerman's (oPossum) msp430 CCS code has been lifted and ported to msp430-gcc
* Robert Wessels' msp430 code provided insight into how to best use the msp430 peripherals
* This post http://mbed.org/users/igorsk/notebook/fast-gpio-with-c-templates/ got me thinking about
using C++ to provide a reasonable API without sacrificing speed and small code size.

Motivation
----------

FABricate (construct, manufacture; specifically : to construct from diverse and usually standardized parts) +
OOH (to exclaim in amazement)

I started with the msp430 when msp430-gcc didn't know about the value line chips. Most
of the examples supplied by Texas Instruments looked like they were written by someone
who took the asm code and just formatted it for 'C'. The small code differences required
for TIs CCS and msp430-gcc made writing code that would run in both environments
painful. Most people were using CCS to write code for their projects and code samples.
I used CCS for a while but still I wanted someting better.  

I really wanted a simple to use API. I wanted to be able to share my code and to use other
peoples code. I liked the idea of the Arduino API but the implemention isn't really focused
on small or efficient code.  About a year ago, I started to contribute my time to the
Energia project. It is a port of Arduino that runs on the msp430 chips. I like it and we do
try to be as efficient as we can be within the confines of the Arduino framework.
One of the biggest things we accomplished was to get a larger number of people
using msp430-gcc.

This code is my attempt to retain the goodness of the Energia framework while
trying to be as fast and efficient as I can be without worrying about breaking
the Arduino API.  The code makes frequent use of msp430-gcc's ability to
inline msp430 asm. If you look at the fabooh implementation of a software
only UART (drivers/swserial430.h), you will see some very tight asm code
that can use any combination of ports and pins. I don't know how you would
do that in straight 'C' and msp430 asm without some really convoluted macros.

Fabooh favors compile time decisions over runtime ones. The gpio class
templates assume you know at compile time which pins and ports you want
to use and the code doesn't end up using any flash or ram space at runtime
trying to figure that out. Constrast that with the table look up scheme
that is done at runtime with Arduino based frameworks. The Arduino scheme
uses up time, flash and ram space that isn't in excess on the small msp430
value line chips.  I think you will like the results achieved with the minor
changes you will have to make to your coding style to take advantage of fabooh.

At this point in the msp430 lifecycle many things have changed for the better. The
msp430-gcc I'm using is based on 4.6.3 gnu. It is fully featured and can be used
with all the msp430 chips, value line chips included. Energia is being widely used
so getting a working msp430-gcc is not really a problem.

With all that being said, it seemed that now is the time to see if I can take
advantage of all that compiler infrastructure and make better use of it. The
result is fabooh.

Support
-------

I'm often on irc.freenode.net in #43oh or #energia channel http://webchat.freenode.net/

Constructive comments welcome.

Warnings
--------

This code is very much in a alpha state. None of the APIs are stable. I'm adding and changing
things around every day.  However, I'll try never to leave the branch in an unstable state.
You should always be able to build and test whatever is checked in.
