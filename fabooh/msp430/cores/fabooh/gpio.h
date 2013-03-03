/*
 * gpio.h - C++ template based GPIO port and pin methods
 *
 * Created: Nov-12-2012
 *  Author: rick@kimballsoftware.com
 *    Date: 03-02-2013
 * Version: 1.0.1
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
#define GPIO_BUILD   0x0001 /* build 1 */

typedef volatile uint8_t & u8_SFR;        /* 8 bit unsigned Special Function Register reference */
typedef const volatile uint8_t & u8_CSFR; /* 8 bit unsigned Constant Special Function Register reference */

/*
 * GPIO - enumerated values common to GPIO_XXX templates
 */

namespace GPIO {
    enum pin_mode { INPUT=0x0, OUTPUT=0x01, INPUT_PULLUP=0x02, INPUT_PULLDOWN=0x04 };
    enum pin_value { LOW=0x0, HIGH=0x01 };
}

/*
 * GPIO_PORT<> - port template
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
struct GPIO_PORT {
    static u8_CSFR PIN()  { return pin;  }
    static u8_SFR POUT()  { return pout; }
    static u8_SFR PDIR()  { return pdir; }
    static u8_SFR PIFG()  { return pifg; }
    static u8_SFR PIES()  { return pies; }
    static u8_SFR PIE()   { return pie; }
    static u8_SFR PSEL()  { return psel; }
    static u8_SFR PSEL2() { return psel2; }
    static u8_SFR PREN()  { return pren; }

    /**
     * pin direction configuration methods
     */
    ALWAYS_INLINE static void set_mode(uint8_t mask, GPIO::pin_mode mode) {
      if ( 0 ) {
      }
      else if (mode == GPIO::OUTPUT ) {
        setmode_output(mask);
      }
      else if ( mode == GPIO::INPUT ) {
        setmode_input(mask);
      }
      else if (mode == GPIO::INPUT_PULLUP) {
          setmode_inputpullup(mask);
      }
      else if (mode == GPIO::INPUT_PULLDOWN) {
          setmode_inputpulldown(mask);
      }
    }

    ALWAYS_INLINE static void setmode_input(uint8_t mask) { pdir &= ~mask; }

    ALWAYS_INLINE static void setmode_inputpullup(uint8_t mask) {
      pdir &= ~mask; set_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_inputpulldown(uint8_t mask) {
      pdir &= ~mask;  clear_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_output(uint8_t mask ) { pdir |= mask; }

    /*
     * get/set methods
     */
    ALWAYS_INLINE static void set_value(uint8_t value) { pout = value; }
    ALWAYS_INLINE static uint8_t get_value() { return pin; }

    ALWAYS_INLINE static void set_pins(uint8_t pin_mask) { pout |= pin_mask; }
    ALWAYS_INLINE static void clear_pins(uint8_t pin_mask) { pout &= ~pin_mask; }
    ALWAYS_INLINE static void toggle_pins(uint8_t pin_mask) { pout ^= pin_mask; }
};

/*
 * GPIO_PORT_NOIE<> - no interrupt port template
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
struct GPIO_PORT_NOIE {
    static u8_CSFR PIN()  { return pin;  }
    static u8_SFR POUT()  { return pout; }
    static u8_SFR PDIR()  { return pdir; }
    static u8_SFR PSEL()  { return psel; }
    static u8_SFR PSEL2() { return psel2; }
    static u8_SFR PREN()  { return pren; }

    /**
     * pin direction configuration methods
     */
    ALWAYS_INLINE static void set_mode(uint8_t mask, GPIO::pin_mode mode) {
      if ( 0 ) {
      }
      else if (mode == GPIO::OUTPUT ) {
        setmode_output(mask);
      }
      else if ( mode == GPIO::INPUT ) {
        setmode_input(mask);
      }
      else if (mode == GPIO::INPUT_PULLUP) {
          setmode_inputpullup(mask);
      }
      else if (mode == GPIO::INPUT_PULLDOWN) {
          setmode_inputpulldown(mask);
      }
    }

    ALWAYS_INLINE static void setmode_input(uint8_t mask) { pdir &= ~mask; }

    ALWAYS_INLINE static void setmode_inputpullup(uint8_t mask) {
      pdir &= ~mask; set_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_inputpulldown(uint8_t mask) {
      pdir &= ~mask;  clear_pins(mask); pren |= mask;
    }

    ALWAYS_INLINE static void setmode_output(uint8_t mask ) { pdir |= mask; }

    /*
     * get/set methods
     */
    ALWAYS_INLINE static void set_value(uint8_t value) { pout = value; }
    ALWAYS_INLINE static uint8_t get_value() { return pin; }

    ALWAYS_INLINE static void set_pins(uint8_t pin_mask) { pout |= pin_mask; }
    ALWAYS_INLINE static void clear_pins(uint8_t pin_mask) { pout &= ~pin_mask; }
    ALWAYS_INLINE static void toggle_pins(uint8_t pin_mask) { pout ^= pin_mask; }
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
    static u8_SFR PIFG()  { return PORT::PIFG(); }
    static u8_SFR PIES()  { return PORT::PIES(); }
    static u8_SFR PIE()   { return PORT::PIE(); }
    static u8_SFR PSEL()  { return PORT::PSEL(); }
    static u8_SFR PSEL2() { return PORT::PSEL2(); }
    static u8_SFR PREN()  { return PORT::PREN(); }

    ALWAYS_INLINE static void setmode_input() { PORT::PDIR() &= ~MASK; }

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

    ALWAYS_INLINE static void setmode_output() { PORT::PDIR() |= MASK; }

    ALWAYS_INLINE static void pinMode(const GPIO::pin_mode mode) {
        if ( 0 ) {
        }
        else if (mode == GPIO::OUTPUT) {
            setmode_output();
        }
        else if (mode == GPIO::INPUT) {
            setmode_input();
        }
        else if (mode == GPIO::INPUT_PULLUP) {
            setmode_inputpullup();
        }
        else if (mode == GPIO::INPUT_PULLDOWN) {
            setmode_inputpulldown();
        }
    }

    ALWAYS_INLINE static void high() { if ( MASK ) PORT::POUT() |= MASK; }
    ALWAYS_INLINE static void low() { if ( MASK ) PORT::POUT() &= ~MASK; }
    ALWAYS_INLINE static void toggle() { if ( MASK) PORT::POUT() ^= MASK; }

    ALWAYS_INLINE static unsigned read() { return (PORT::PIN() & MASK ) != 0; }
    ALWAYS_INLINE static void write(GPIO::pin_value value) {
        if (value == GPIO::HIGH) {
            high();
        }
        else if (value == GPIO::LOW) {
            low();
        }
    }

    ALWAYS_INLINE static void set_pins(const uint8_t pins_mask) { PORT::POUT() |= pins_mask; }
    ALWAYS_INLINE static void clear_pins(const uint8_t pins_mask) { PORT::POUT() &= ~pins_mask; }
    ALWAYS_INLINE static void toggle_pins(const uint8_t pins_mask) { PORT::POUT() ^= pins_mask; }

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

    ALWAYS_INLINE T operator =(GPIO::pin_value value) {
        write(value);
        return *this;
    }
#endif
};

/*
 * DummyGPIO - minimal template that looks like a GPIO but does nothing
 *
 * Useful to provide NOP pin as in the case of a output only serial port.
 * This will satisfy the compiler but not add to the code size.
 *
 */
template<uint8_t PORTPIN>
struct DummyGPIO {
    struct {
        uint16_t PIN() { return 0; }
        uint16_t POUT() { return 0; }
        uint16_t PSEL() { return 0; }
        uint16_t PREN() { return 0; }
        uint16_t PSEL2() { return 0; }
        uint8_t PINMASK() { return 0; }
    } port;
    static const uint8_t pin_mask=0;

    static void setmode_input() {}
    static void setmode_inputpullup() {}
    static void setmode_inputpulldown() {}
    static void setmode_output() { }
    static void pinMode(GPIO::pin_mode) { }

    static void high() { }
    static void low() { }
    static void toggle() { }

    static unsigned read() { return 0; }
    static void write(GPIO::pin_value) {}
};

typedef DummyGPIO<0> NO_PIN;

#endif /* GPIO_H_ */
