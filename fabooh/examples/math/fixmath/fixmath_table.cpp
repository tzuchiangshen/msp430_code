/**
 * fixmath_table.cpp - print a table of angles and sine using a fix16_t
 *                     data type from libfixmath and its trigonometry functions
 *
 * see: http://en.wikipedia.org/wiki/Libfixmath
 *
 * $ msp430-size fixmath_table.elf
 * text    data     bss     dec     hex filename
 * 1406       0       2    1408     580 fixmath_table.elf
 */

#include <fabooh.h>
#include <main.h>
#include <serial.h>

namespace {
  const uint32_t BAUD_RATE = 9600;
  typedef serial_default_t<BAUD_RATE, CPU::frequency, TX_PIN, NO_PIN> serial; /* TX=P?.? varies, RX=NO_PIN */
  serial Serial;
};

inline void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  Fix16 angle; // use fix16_t for calculations

  Serial << "Table of Sin(a)" << endl;

  for (angle = -90; angle <= 90; angle += 1) {
    fix16_t sin_value = angle.sind(); // calc sine from degrees

    Serial << "angle = " << _FIX16(angle, 0)
           << " sin =  " << _FIX16(sin_value, 4) /* 5 is max with fix16_t */
           << endl;
  }

  LPM4; // stop here when done., press reset button to see again
}
