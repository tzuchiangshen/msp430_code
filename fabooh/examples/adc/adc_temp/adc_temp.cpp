/*
 * adc_temp - read temp from ADC10 and convert to Farenheit and Celsius
 *            This code uses libfixmath to convert adc samples from millivolts
 *            to F and C. It also provides some reference code that uses
 *            straight integer math to accomplish the same thing.
 *
 * $ msp430-size adc_temp.elf
 *    text    data     bss     dec     hex filename
 *    1032       0       0    1032     408 adc_temp.elf
 *
 * see also:
 *   http://forum.43oh.com/topic/1954-using-the-internal-temperature-sensor/
 */

#include <fabooh.h>
#define SMALL_INIT4
#include <main.h>
#include <serial.h>

typedef serial_default_t<9600,CPU::frequency,TX_PIN,NO_PIN> serial_t;

// conditional compiles let you compare sizes and code generated
#define USE_FIX16
#undef  USE_INTEGER_MATH

void setup() {
  serial_t Serial;

#ifdef USE_FIX16
  // create fix16_t constants
  Fix16 c_0_413(413);    c_0_413 = c_0_413 / 1000;
  Fix16 c_277_75(27775); c_277_75 = c_277_75 / 100;
  Fix16 c_1_8(9);        c_1_8 = c_1_8/5;
  Fix16 c_32(32);
#endif

  // configure ADC to take temperature samples
  ADC10CTL0 = 0;
  ADC10CTL1 = INCH_10 | ADC10DIV_3;
  ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;

  Serial.begin(9600);

  __enable_interrupt();

  unsigned sample;

  while(1) {
    // enable ADC sample, sleep till complete
    ADC10CTL0 |= ENC + ADC10SC;
    LPM3;

    sample = ADC10MEM;

    // output F and C temps
#ifdef USE_FIX16
    // working variable for cal
    Fix16 f,c;

    // convert sample to C = sample*0.413 - 277.75
    c = int16_t(sample);
    c= (c * c_0_413) - c_277_75;
    Serial << _FIX16(c + 0.5f, 0) << " C" << endl;

    // convert sample to F = C*9/5 + 32
    f = (c * c_1_8) + c_32;
    Serial << _FIX16(f + 0.5f, 0) << " F" << endl;
#endif

#ifdef USE_INTEGER_MATH
    int conversion;
    conversion = ((27069L * sample) -  18169625L) >> 16;
    Serial << conversion << " C (43oh)" << endl;

    conversion = ((48724L * sample ) - 30634388L) >> 16;
    Serial << conversion << " F (43oh)" << endl;
#endif

    Serial << endl;
    delay(5000);
  }
}

/*
 * when sample is complete, wake up main thread
 */
#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
  LPM3_EXIT;
}

void loop() {}
