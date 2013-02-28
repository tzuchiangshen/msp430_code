/**
 * ascii_table.cpp - ASCII table print using USCI serial template
 *
 * Note: the size of .elf is determined by typeof(counter_t)
 *
 * 468 bytes unsigned thisByte
 *   Writing  370 bytes at c000 [section: .text]...
 *   Writing   66 bytes at c172 [section: .rodata]...
 *   Writing   32 bytes at ffe0 [section: .vectors]...
 *
 * 498 bytes int8_t thisByte
 * 468 bytes uint8_t thisByte
 * 498 bytes int thisByte
 * 562 bytes unsigned long thisByte
 * 606 bytes long thisByte
 *
 */

#include <fabooh.h>
#include <serial.h>
#include <msp430/usciserial430.h>

#define NO_DATA_INIT /* 0 DATA, and thisByte is the only BSS variable we just set it in setup() */
#define NO_BSS_INIT /* thisByte is really a BSS value, set in setup() */
#include <main.h>

typedef unsigned counter_t; /* type we use for counting from ' ' -> '~' */

// mix-in some serial and print to form a working serial class
template <uint32_t BAUD, uint32_t MCLK_HZ, typename TXPIN, typename RXPIN>
struct serial_t:
#if defined(__MSP430_HAS_USCI__)
  serial_base_usci_t<BAUD, MCLK_HZ, TXPIN, RXPIN>,
#else
  serial_base_sw_t<BAUD, MCLK_HZ, TXPIN, RXPIN>,
#endif
  print_t<serial_t<BAUD, MCLK_HZ, TXPIN, RXPIN>, uint16_t, uint32_t >
{
};

//------- file space globals ------
namespace {

  const uint32_t BAUD_RATE=9600;
#if defined(__MSP430_HAS_USCI__)
  serial_t<BAUD_RATE, CPU::frequency, P1_2 /*P2_0*/, NO_PIN> Serial; // xmit only serial TX=P1.2
#else
  serial_t<BAUD_RATE, CPU::frequency, P1_1 /*P2_0*/, NO_PIN> Serial; // xmit only serial TX=P1.2
#endif

#if defined(NO_DATA_INIT)
  counter_t thisByte; // use less code by initializing in setup()
#else
  counter_t thisByte=' '; // use the standard __do_data_copy() routines from libc
#endif

}

inline void setup(void)
{
#if defined(NO_DATA_INIT)
  thisByte=' '; // first visible ASCII character ' ' is number 32:
#endif

  // Initialize serial port pins. Note: speed is ignored here just for documentation
  // change the baud rate in the template definition
  Serial.begin(BAUD_RATE);

  // prints title with ending line break
  Serial.print("ASCII Table ~ Character Map\n");
}

void loop()
{
  // prints value unaltered, i.e. the raw binary version of the
  // byte. The serial monitor interprets all bytes as
  // ASCII, so 32, the first number,  will show up as ' ' AKA a space

  Serial.print(thisByte, RAW);

  // base 10
  Serial.print(", dec: "); Serial.print(thisByte);

  // base 8
  Serial.print(", oct: 0"); Serial.print(thisByte,OCT);

  // base 16
  Serial.print(", hex: 0x"); Serial.print(thisByte,HEX);

  // base 2
  Serial.print(", bin: 0b"); Serial.print(thisByte,BIN);

  // new line
  Serial.println();

  // if printed last visible character '~' or 126, stop:
  if( thisByte == '~') {
    // this powers down the chip and sleeps forever
    LPM4; //while(1);
  }
  // go on to the next character
  thisByte++;
}
