/**
 * fixmath_table.cpp - print a table of angles and sine using fix16_t
 *                     type from libfixmath and its trig functions
 *
 * see: http://en.wikipedia.org/wiki/Libfixmath
 *
 * $ msp430-size fixmath.elf
 *    text    data     bss     dec     hex filename
 *    1592       0       0    1592     638 fixmath_table.elf
 *
 */

#include <fabooh.h>
#include <main.h>
#include <serial.h>
#include "libfixmath/fix16.h"

namespace {
  const uint32_t BAUD_RATE = 9600;
  typedef serial_default_t<BAUD_RATE, CPU::frequency, TX_PIN, NO_PIN> serial; /* TX=P?.? varies, RX=NO_PIN */
  serial Serial;
};

inline void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  int angle;
  char angle_str[1+1+1+4+1];

  Serial << "Table of Sin(a)" << endl;

  for (angle = -90; angle <= 90; angle++ ) {
    fix16_t sin_value = fix16_sin(fix16_deg_to_rad(fix16_from_int(angle)));

    // TODO: implement fix16_t as a valid type in print_t
    fix16_to_str(sin_value,angle_str,4);

    Serial  << "angle = " << angle
            << " sin = " << angle_str
            << endl;
  }

  LPM4; // stop here when done., press reset button to see again
}
