/**
 * sin_table.cpp - using configurable print_t template
 *
 * 11956 bytes .. hmm pretty useless
 *
 * TBD: implement CORDIC floating point routines
 *
 */

#include <fabooh.h>
#include <serial.h>
#include <math.h>
#include <main.h>

/*
 * serial - declare output only bit banged/cycle counting UART with output
 *
 * use mixins to compose a minimal sized and flexible serial class
 *
 */
template<uint32_t BPS, uint32_t MCLK_HZ, typename TXPIN, typename RXPIN>
struct serial_t:
  //serial_base_sw_t<BPS, MCLK_HZ, TXPIN, RXPIN>    /* use software only UART */
  serial_base_usci_t<BPS, MCLK_HZ, TXPIN, RXPIN> /* use hardware USCI UART */
  ,print_t<serial_t<BPS, MCLK_HZ, TXPIN, RXPIN>, uint32_t, uint32_t>
{
  // implementation is mashup of UART and print_t mix-ins
};

namespace {
  const uint32_t BAUD_RATE = 9600;
  typedef serial_t<BAUD_RATE, CPU::frequency, P1_2, NO_PIN> serial; /* TX=P1.2, RX=NO_PIN */
  typedef print_t<serial> Print;
  serial Serial;
};

float deg2rad(float deg) {
  return (deg * M_PI) / 180.0f;
}

inline void setup() {
  Serial.begin(BAUD_RATE);    // go fast just because we can
}

void loop() {
  unsigned angle;
  float sin_value;

  Serial.print("Table of Sin(a)\n");

  for (angle = 0; angle < 360; angle++) {
    float a = (float) angle;
    sin_value = sinf(deg2rad(a));
    Serial.print("angle="); Serial.print(angle);
    Serial.print(" sin="); Serial.print(sin_value, 5);
    Serial.println();
  }

  LPM4; // stop here when done., press reset button to see again
}
