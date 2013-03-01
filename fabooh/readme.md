FABOOH - as in FABricate meets OOH La La
----------------------------------------
Fabooh is an optimized C++ template based peripheral framework for the
msp430 microcontroller.  It creates very small and efficient code while
still providing a flexible framework akin to what you might expect in
Energia without needless overhead.  It makes liberal use of inline
msp430-gcc assembler code to produce optimized code that is sometimes
smaller than generic 'C' code.

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
}
</code>
</pre>

This results in very efficient code that uses only 158 bytes of flash, no data and no BSS;

<pre>
<code>

blink.elf:     file format elf32-msp430


Disassembly of section .text:

0000c000 <__watchdog_support>:
    c000:  b2 40 80 5a 	mov	#23168,	&0x0120	;#0x5a80
    c004:	20 01 

0000c006 <__init_stack>:
    c006:	31 40 00 04 	mov	#1024,	r1	;#0x0400

0000c00a <__do_clear_bss>:
    void __do_clear_bss(void) __attribute__((section(".init4"),naked));
    void __do_clear_bss() {
      __asm__(
          "\n"
          //"nop; empty __do_clear_bss() {} \n" // someplace to put a breakpoint
          );
    c00a:	d2 42 f9 10 	mov.b	&0x10f9,&0x0057	
    c00e:	57 00 
    c010:	d2 42 f8 10 	mov.b	&0x10f8,&0x0056	
    c014:	56 00 
    c016:	b0 12 2a c0 	call	#0xc02a	
    c01a:	b0 12 4e c0 	call	#0xc04e	
    c01e:	fd 3f       	jmp	$-4      	;abs 0xc01a

0000c020 <__stop_progExec__>:
    c020:	32 d0 f0 00 	bis	#240,	r2	;#0x00f0
    c024:	fd 3f       	jmp	$-4      	;abs 0xc020

0000c026 <__ctors_end>:
    c026:	30 40 7c c0 	br	#0xc07c	

0000c02a <setup()>:
      PORT::PDIR() &= ~MASK;
      low();
      PORT::PREN() |= MASK;
    }

    ALWAYS_INLINE static void setmode_output() { PORT::PDIR() |= MASK; }
    c02a:	d2 d3 22 00 	bis.b	#1,	&0x0022	;r3 As==01
    c02e:	f2 d0 40 00 	bis.b	#64,	&0x0022	;#0x0040
    c032:	22 00 
    static u8_SFR PREN()  { return PORT::PREN(); }

    ALWAYS_INLINE static void setmode_input() { PORT::PDIR() &= ~MASK; }

    ALWAYS_INLINE static void setmode_inputpullup() {
      PORT::PDIR() &= ~MASK;
    c034:	f2 f0 f7 ff 	and.b	#-9,	&0x0022	;#0xfff7
    c038:	22 00 
        else if (mode == GPIO::INPUT_PULLDOWN) {
            setmode_inputpulldown();
        }
    }

    ALWAYS_INLINE static void high() { if ( MASK ) PORT::POUT() |= MASK; }
    c03a:	f2 d2 21 00 	bis.b	#8,	&0x0021	;r2 As==11
    ALWAYS_INLINE static void setmode_input() { PORT::PDIR() &= ~MASK; }

    ALWAYS_INLINE static void setmode_inputpullup() {
      PORT::PDIR() &= ~MASK;
      high();
      PORT::PREN() |= MASK;
    c03e:	f2 d2 27 00 	bis.b	#8,	&0x0027	;r2 As==11
            setmode_inputpulldown();
        }
    }

    ALWAYS_INLINE static void high() { if ( MASK ) PORT::POUT() |= MASK; }
    ALWAYS_INLINE static void low() { if ( MASK ) PORT::POUT() &= ~MASK; }
    c042:	f2 f0 bf ff 	and.b	#-65,	&0x0021	;#0xffbf
    c046:	21 00 
        else if (mode == GPIO::INPUT_PULLDOWN) {
            setmode_inputpulldown();
        }
    }

    ALWAYS_INLINE static void high() { if ( MASK ) PORT::POUT() |= MASK; }
    c048:	d2 d3 21 00 	bis.b	#1,	&0x0021	;r3 As==01
  PUSH2::setmode_inputpullup();

  GREEN_LED::low();
  RED_LED::high();

}
    c04c:	30 41       	ret			

0000c04e <loop()>:
    ALWAYS_INLINE static void low() { if ( MASK ) PORT::POUT() &= ~MASK; }
    ALWAYS_INLINE static void toggle() { if ( MASK) PORT::POUT() ^= MASK; }

    ALWAYS_INLINE static unsigned read() { return (PORT::PIN() & MASK ) != 0; }
    c04e:	5f 42 20 00 	mov.b	&0x0020,r15	
    c052:	3f f2       	and	#8,	r15	;r2 As==11

void loop() {
  
  // block loop if user holds down the button
  if ( !PUSH2::read() ) {
    c054:	07 20       	jnz	$+16     	;abs 0xc064
    do {
      delay_msecs(10); // debounce switch
    c056:	3f 40 54 d0 	mov	#-12204,r15	;#0xd054
    c05a:	1f 83       	dec	r15		
    c05c:	fe 23       	jnz	$-2      	;abs 0xc05a
    c05e:	03 43       	nop			
    c060:	03 43       	nop			
    c062:	f5 3f       	jmp	$-20     	;abs 0xc04e
    } while(!PUSH2::read());
  }

  delay_msecs(100);
    c064:	3e 40 09 00 	mov	#9,	r14	;#0x0009
    c068:	3f 40 4b 23 	mov	#9035,	r15	;#0x234b
    c06c:	1f 83       	dec	r15		
    c06e:	fe 23       	jnz	$-2      	;abs 0xc06c
    c070:	1e 83       	dec	r14		
    c072:	fc 23       	jnz	$-6      	;abs 0xc06c
        }
    }

    ALWAYS_INLINE static void set_pins(const uint8_t pins_mask) { PORT::POUT() |= pins_mask; }
    ALWAYS_INLINE static void clear_pins(const uint8_t pins_mask) { PORT::POUT() &= ~pins_mask; }
    ALWAYS_INLINE static void toggle_pins(const uint8_t pins_mask) { PORT::POUT() ^= pins_mask; }
    c074:	f2 e0 41 00 	xor.b	#65,	&0x0021	;#0x0041
    c078:	21 00 
  }
  else {
    RED_LED::toggle();
    GREEN_LED::toggle();
  }
}
    c07a:	30 41       	ret			

0000c07c <_unexpected_>:
    c07c:	00 13       	reti			

Disassembly of section .vectors:

0000ffe0 <__ivtbl_16>:
    ffe0:	26 c0 26 c0 26 c0 26 c0 26 c0 26 c0 26 c0 26 c0     &.&.&.&.&.&.&.&.
    fff0:	26 c0 26 c0 26 c0 26 c0 26 c0 26 c0 26 c0 00 c0     &.&.&.&.&.&.&...
</code>
</pre>
