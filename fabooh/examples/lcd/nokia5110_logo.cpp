/*
 * nokia5110_logo.cpp - demo xbmto5110
 *
 * Created: Feb-3-2012
 *  Author: rick@kimballsoftware.com
 *    Date: 02-28-2013
 * Version: 1.0.0
 *
 */

#include <fabooh.h>
#define USE_SPI 1
#include <drivers/nokia_5110.h>
#include <main.h>

#include "bitmaps/lp_logo.inc"

typedef P1_0 LCD_DC;
typedef P1_4 LCD_CE;
typedef P1_5 SCLK;
typedef P1_7 SDI;
typedef P1_6 LCD_BACKLIGHT;

inline void init_spi(void) {
#if defined(USE_SPI) && USE_SPI
  #define SPI_MODE_0 (UCCKPH)         /* CPOL=0 CPHA=0 */
  #define SPI_MODE_1 (0)              /* CPOL=0 CPHA=1 */
  #define SPI_MODE_2 (UCCKPL | UCCKPH)/* CPOL=1 CPHA=0 */
  #define SPI_MODE_3 (UCCKPL)         /* CPOL=1 CPHA=1 */

  UCB0CTL1 = UCSWRST | UCSSEL_2;             // Put USCI in reset mode, source USCI clock from SMCLK
  UCB0CTL0 = SPI_MODE_3 | UCMSB | UCSYNC | UCMST; // seems to work with either MODE 0 or MODE 3
  P1SEL |= SCLK::pin_mask | SDI::pin_mask;     // configure P1.5 and P1.7 for USCI
  P1SEL2 |= SCLK::pin_mask | SDI::pin_mask;     // more required SPI configuration
  UCB0BR0 = 1;
  UCB0BR1 = 0;                     // set SPI clock to 2MHz ... SMCLK/8, (16000000/8)
  UCB0CTL1 &= ~UCSWRST;                         // release USCI for operation
#else
  P1::set_mode(SCLK::pin_mask|SDI::pin_mask, GPIO::OUTPUT);
  SCLK::high();
#endif
}

void setup() {
  P1::set_mode(LCD_CE::pin_mask | LCD_DC::pin_mask | LCD_BACKLIGHT::pin_mask, GPIO::OUTPUT);
  P1::set_pins(LCD_DC::pin_mask | LCD_CE::pin_mask);

  init_spi();

  lcd::nokia::Nokia5110<P1_5, P1_7, P1_0, P1_4, 100> lcd;

  lcd.reset();
  lcd.init();
  lcd.clear();

  LCD_BACKLIGHT::high(); // turn off backlight

  do {
    lcd.clear();
    lcd.bitmap(lp_logo, (84 - 56) / 2, 0);
    LPM4;
  } while (1);
}

void loop() {}
