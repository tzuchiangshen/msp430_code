/**
 * ascii_table_extended.cpp - spew ASCII table print insertion operators
 *
 * Author: rick@kimballsoftware.com
 * Date: 2-28-2013
 *
 */

#include <fabooh.h>
#include <serial.h>

#define NO_DATA_INIT
#define NO_BSS_INIT
#include "main.h"

template <uint32_t BAUD, uint32_t MCLK_HZ, typename TXPIN, typename RXPIN>
struct serial_t:
  serial_base_usci_t<BAUD, MCLK_HZ, TXPIN, RXPIN>,
  print_t<serial_t<BAUD, MCLK_HZ, TXPIN, RXPIN>, uint16_t, uint32_t>
{
};

//------- File Globals ------
namespace {
  const uint32_t BAUD_RATE=9600;
  typedef serial_t<BAUD_RATE, CPU::frequency, P1_2, NO_PIN> serial;
  serial Serial;
  unsigned thisByte; // first visible ASCIIcharacter ' ' is number 32:
}

typedef print_t<serial> Print;

/*
 * print_t insertion operator support
 */
template<typename T>
inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

template<typename T>
struct _BASE {
  const T n;
  const base_e base;

  _BASE(const T _n, const base_e _base): n(_n), base(_base) {}
};

#define _RAW(n) _BASE<typeof((n))>(n,RAW)
#define _BIN(n) _BASE<typeof((n))>(n,BIN)
#define _OCT(n) _BASE<typeof((n))>(n,OCT)
#define _DEC(n) _BASE<typeof((n))>(n,DEC)
#define _HEX(n) _BASE<typeof((n))>(n,HEX)

template<typename T>
inline Print &operator <<(Print &obj, const _BASE<T> &arg) { obj.print(arg.n, arg.base); return obj; }

inline void setup(void)
{
  thisByte=' '; // first visible ASCIIcharacter ' ' is number 32:
  // initialize serial port pins. Note: speed is ignored here just for documentation
  // change the baud rate in the template definition
  Serial.begin(BAUD_RATE);

  // prints title with ending line break
  Serial.print("ASCII Table ~ Character Map\n");
}

void loop()
{

  // either of these methods should end up with the same code size
#if 1
  // use insertion operator style

  Serial  << _RAW(thisByte)
          << ", dec: " << thisByte
          << ", oct: 0" << _OCT(thisByte)
          << ", hex: 0x" << _HEX(thisByte)
          << ", bin: 0b" << _BIN(thisByte)
          << endl;
#else
  // use method call style

  Serial.print(thisByte, RAW);
  Serial.print(", dec: "); Serial.print(thisByte);
  Serial.print(", oct: 0"); Serial.print(thisByte,OCT);
  Serial.print(", hex: 0x"); Serial.print(thisByte,HEX);
  Serial.print(", bin: 0b"); Serial.print(thisByte,BIN);
  Serial.println();
#endif

  // if printed last visible character '~' or 126, stop:
  if( thisByte == '~') {
    // This loop loops forever and does nothing
    //while(1);
    LPM4;
  }

  // go on to the next character
  thisByte++;
}
