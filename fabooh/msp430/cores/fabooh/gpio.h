/*
 * gpio.h - C++ template based GPIO port and pin methods
 *
 * Created: Nov-12-2012
 *  Author: rick@kimballsoftware.com
 *    Date: 03-??-2013
 * Version: 1.0.4
 *
 * =========================================================================
 *  Copyright © 2013 Rick Kimball
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_VERSION 0x0100 /* 1.0 */
#define GPIO_BUILD   0x0003 /* build #*/

typedef volatile uint8_t & u8_SFR;        /* 8 bit unsigned Special Function Register reference */
typedef const volatile uint8_t & u8_CSFR; /* 8 bit unsigned Constant Special Function Register reference */

enum yesno_e { NO=0, YES=1 };

/*
 * pin_mode - settings for port/pin direction
 * Note: values used coincide with the optimized constant
 *       generator values that result in faster msp430 instructions
 */
enum pin_mode {
  INPUT=0x00
  ,OUTPUT=0x01
  ,INPUT_PULLUP=0x02
  ,INPUT_PULLDOWN=0x04
};

enum pin_value {
  LOW=0x00
  ,HIGH=0x01
};

/*
 * GPIO_PORT_BASE0<> - port template for basic ports
 *
 */
template <
    u8_CSFR pin
    ,u8_SFR pout
    ,u8_SFR pdir
    ,u8_SFR psel
    ,u8_SFR pren
>
struct GPIO_PORT_BASE0 {
    static u8_CSFR PIN()  { return pin;  }
    static u8_SFR POUT()  { return pout; }
    static u8_SFR PDIR()  { return pdir; }
    static u8_SFR PSEL()  { return psel; }
    static u8_SFR PREN()  { return pren; }
    static yesno_e hasPSEL2() { return NO; }
    static yesno_e hasInterrupt() { return NO; }

    /**
     * pin direction configuration methods
     */
    ALWAYS_INLINE static void set_mode(const uint8_t mask, pin_mode mode) {
      if ( 0 ) {
      }
      else if (mode == OUTPUT ) {
        setmode_output(mask);
      }
      else if ( mode == INPUT ) {
        setmode_input(mask);
      }
      else if (mode == INPUT_PULLUP) {
          setmode_inputpullup(mask);
      }
      else if (mode == INPUT_PULLDOWN) {
          setmode_inputpulldown(mask);
      }
    }

    ALWAYS_INLINE static void setmode_input(const uint8_t mask) {
      pdir &= ~mask;
    }

    ALWAYS_INLINE static void setmode_inputpullup(const uint8_t mask) {
      pdir &= ~mask; set_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_inputpulldown(const uint8_t mask) {
      pdir &= ~mask;  clear_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_output(const uint8_t mask ) {
      pdir |= mask;
    }

    /*
     * port wide (8bits) get/set methods
     */
    ALWAYS_INLINE static void set_value(const uint8_t value) {
      pout = value;
    }

    ALWAYS_INLINE static uint8_t get_value() {
      return pin;
    }

    ALWAYS_INLINE static void set_pins(const uint8_t pin_mask) {
      pout |= pin_mask;
    }

    ALWAYS_INLINE static void clear_pins(const uint8_t pin_mask) {
      pout &= ~pin_mask;
    }

    ALWAYS_INLINE static void toggle_pins(const uint8_t pin_mask) {
      pout ^= pin_mask;
    }

    /* TODO: fix this PSEL2 not available on some PORTS */
    /* TODO: devise generic scheme for setting alternate pin functions */
};

/*
 * GPIO_PORT_BASE2<> - port base template with psel2
 *
 */

template <
    u8_CSFR pin
    ,u8_SFR pout
    ,u8_SFR pdir
    ,u8_SFR psel
    ,u8_SFR psel2
    ,u8_SFR pren
>
struct GPIO_PORT_BASE2 :
  GPIO_PORT_BASE0<pin,pout,pdir,psel,pren>
{
    static u8_SFR PSEL2() { return psel2; }
    static yesno_e hasPSEL2() { return YES; }
};

/*
* GPIO_PORT0<> - port template for interrupt capable ports
*
*/

template <
  u8_CSFR pin
  ,u8_SFR pout
  ,u8_SFR pdir
  ,u8_SFR pifg
  ,u8_SFR pies
  ,u8_SFR pie
  ,u8_SFR psel
  ,u8_SFR pren
>
struct GPIO_PORT0 :
GPIO_PORT_BASE0<pin,pout,pdir,psel,pren>
{
  static u8_SFR PIFG()  { return pifg; }
  static u8_SFR PIES()  { return pies; }
  static u8_SFR PIE()   { return pie; }
  static yesno_e hasInterrupt() { return YES; }

  /* TODO: implement decent pin interrupt ISR handlers () */
};

/*
 * GPIO_PORT<> - port template for interrupt capable ports
 *
 */

template <
    u8_CSFR pin
    ,u8_SFR pout
    ,u8_SFR pdir
    ,u8_SFR pifg
    ,u8_SFR pies
    ,u8_SFR pie
    ,u8_SFR psel
    ,u8_SFR psel2
    ,u8_SFR pren
>
struct GPIO_PORT :
  GPIO_PORT_BASE2<pin,pout,pdir,psel,psel2,pren>
{
    static u8_SFR PIFG()  { return pifg; }
    static u8_SFR PIES()  { return pies; }
    static u8_SFR PIE()   { return pie; }

    /* TODO: implement decent pin interrupt ISR handlers () */
};

/*
 * GPIO_PIN<> - pin template
 *
 */

template <const uint8_t MASK, typename PORT>
struct GPIO_PIN {
    typedef GPIO_PIN<MASK,PORT> T;
    static const uint8_t pin_mask=MASK;

    static u8_CSFR PIN()  { return PORT::PIN();  }
    static u8_SFR POUT()  { return PORT::POUT(); }
    static u8_SFR PDIR()  { return PORT::PDIR(); }
    static u8_SFR PSEL()  { return PORT::PSEL(); }
    static u8_SFR PSEL2() { return PORT::PSEL2();}
    static u8_SFR PREN()  { return PORT::PREN(); }

    static u8_SFR PIFG()  { return PORT::PIFG(); }
    static u8_SFR PIES()  { return PORT::PIES(); }
    static u8_SFR PIE()   { return PORT::PIE(); }

    /*
     * pin direction functions
     */

    ALWAYS_INLINE static void setmode_input() {
      PORT::PDIR() &= ~MASK;
    }

    ALWAYS_INLINE static void setmode_inputpullup() {
      PORT::PDIR() &= ~MASK;
      high();
      PORT::PREN() |= MASK;
    }

    ALWAYS_INLINE static void setmode_inputpulldown() {
      PORT::PDIR() &= ~MASK;
      low();
      PORT::PREN() |= MASK;
    }

    ALWAYS_INLINE static void setmode_output() {
      PORT::PDIR() |= MASK;
    }

    ALWAYS_INLINE static void set_mode(const pin_mode mode) {
        if ( 0 ) {
        }
        else if (mode == OUTPUT) {
            setmode_output();
        }
        else if (mode == INPUT) {
            setmode_input();
        }
        else if (mode == INPUT_PULLUP) {
            setmode_inputpullup();
        }
        else if (mode == INPUT_PULLDOWN) {
            setmode_inputpulldown();
        }
    }

    /*
     * pin query functions
     */

    ALWAYS_INLINE static unsigned read() {
      return (PORT::PIN() & MASK ) != 0;
    }

    /*
     * pin modification functions
     */

    ALWAYS_INLINE static void write(pin_value value) {
        if (value == HIGH) {
            high();
        }
        else if (value == LOW) {
            low();
        }
    }

    ALWAYS_INLINE static void high() {
      if ( MASK )
        PORT::POUT() |= MASK;
    }

    ALWAYS_INLINE static void low() {
      if ( MASK )
        PORT::POUT() &= ~MASK;
    }

    ALWAYS_INLINE static void toggle() {
      if ( MASK)
        PORT::POUT() ^= MASK;
    }

    /*
     * port wide (8bits) direction using pin as port
     */
    ALWAYS_INLINE static void set_modes(const uint8_t pins_mask, pin_mode mode) {
      PORT::set_mode(pins_mask, mode);
    }

    /*
     * port wide (8bits) modifications using pin as port
     */
    ALWAYS_INLINE static void set_pins(const uint8_t pins_mask) {
      PORT::POUT() |= pins_mask;
    }

    ALWAYS_INLINE static void clear_pins(const uint8_t pins_mask) {
      PORT::POUT() &= ~pins_mask;
    }

    ALWAYS_INLINE static void toggle_pins(const uint8_t pins_mask) {
      PORT::POUT() ^= pins_mask;
    }

    /* TODO: fix this, not all pins have interrupt capability */

#if 0
    /* neat idea, however, this requires an instance which means we use data when we don't have to */
    ALWAYS_INLINE T operator =(int value) {
        if ( value ) {
            high();
        }
        else {
            low();
        }
        return *this;
    }

    ALWAYS_INLINE T operator =(pin_value value) {
        write(value);
        return *this;
    }
#endif
};

/*
 * DummyGPIO - minimal template that looks like a GPIO but does nothing
 *
 * Useful to provide NOP pin as in the case of an output only serial port.
 * This will satisfy the compiler but not add to the code size.
 *
 */
template<uint8_t PORTPIN>
struct DummyGPIO {
    struct {
        static uint16_t PIN() { return 0; }
        static uint16_t POUT() { return 0; }
        static uint16_t PSEL() { return 0; }
        static uint16_t PSEL2() { return 0; }
        static uint16_t PREN() { return 0; }
        static uint8_t PINMASK() { return 0; }

        static void set_mode(const uint8_t, pin_mode) {}
    } port;
    static const uint8_t pin_mask=0;

    static void setmode_input() {}
    static void setmode_inputpullup() {}
    static void setmode_inputpulldown() {}
    static void setmode_output() {}
    static void set_mode(pin_mode) {}

    static void high() { }
    static void low() { }
    static void toggle() { }

    static int read() { return 0; }
    static void write(pin_value) {}
};

typedef DummyGPIO<0> NO_PIN;

/*
 * port helper macros
 * assumes all pins are from the same port, no check performed , user tasked with being smart
 *
 */
#define portMode(B0,B1, _mode) B0::set_modes((const uint8_t)(B0::pin_mask|B1::pin_mask),_mode);
#define portMode3(B0,B1,B2, _mode) B0::set_modes((const uint8_t)(B0::pin_mask|B1::pin_mask|B2::pin_mask),_mode);
#define portMode4(B0,B1,B2,B3, _mode) B0::set_modes((const uint8_t)(B0::pin_mask|B1::pin_mask|B2::pin_mask|B3::pin_mask),_mode);

#define portToggle(B0,B1) B0::toggle_pins(B0::pin_mask|B1::pin_mask);
#define portToggle3(B0,B1,B2) B0::toggle_pins(B0::pin_mask|B1::pin_mask|B2::pin_mask);
#define portToggle4(B0,B1,B2,B3) B0::toggle_pins(B0::pin_mask|B1::pin_mask|B2::pin_mask|B3::pin_mask);

/*
 * nod to Arduino API
 */
#define digitalRead(PIN_T) PIN_T::read()
#define digitalWrite(PIN_T,_value) PIN_T::write(_value)
#define pinMode(PIN_T,_mode) PIN_T::set_mode(_mode)


#endif /* GPIO_H_ */
