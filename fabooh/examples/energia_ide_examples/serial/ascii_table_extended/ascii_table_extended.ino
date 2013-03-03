/**
 * ascii_table_extended.cpp - spew ASCII table print insertion operators
 *
 * Author: rick@kimballsoftware.com
 * Date: 03-03-2013
 *
 * $ msp430-size ascii_table_extended.elf
 *   text    data     bss     dec     hex filename
 *    500       2       0     502     1f6 ascii_table_extended.elf
 *
 */
#include <fabooh.h>
#include <serial.h>
#include "main.h"

template <uint32_t BAUD, uint32_t MCLK_HZ, typename TXPIN, typename RXPIN>
struct serial_t:
  serial_base_sw_t<BAUD, MCLK_HZ, TXPIN, RXPIN>,
  print_t<serial_t<BAUD, MCLK_HZ, TXPIN, RXPIN>, uint16_t, uint32_t>
{
};

//------- File Globals ------
namespace {
  const uint32_t BAUD_RATE=9600;
  typedef serial_t<BAUD_RATE, CPU::frequency, TX_PIN, NO_PIN> serial;
  typedef print_t<serial> Print;

  serial Serial;
  unsigned thisByte=' '; // first visible ASCIIcharacter ' ' is number 32:
}

#include "ascii_table_extended.h"

inline void setup(void)
{
  // initialize serial port pins. Note: speed is ignored here just for documentation
  // change the baud rate in the template definition
  Serial.begin(BAUD_RATE);

  // prints title with ending line break
  Serial.print("ASCII Table ~ Character Map\n");
}

void loop()
{

  // use insertion operator style
  Serial  << _RAW(thisByte)
          << ", dec: " << thisByte
          << ", oct: 0" << _OCT(thisByte)
          << ", hex: 0x" << _HEX(thisByte)
          << ", bin: 0b" << _BIN(thisByte)
          << endl;

  // if printed last visible character '~' or 126, stop:
  if( thisByte == '~') {
    LPM4;
  }

  // go on to the next character
  thisByte++;
}
