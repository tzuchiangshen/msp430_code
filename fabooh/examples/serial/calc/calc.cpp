/**
 * calc.cpp - simple serial integer only calculator
 *
 * Desc: Implements a serial calculator using the re2c tool to scan the
 *       input stream and turn it into tokens.  Calculator implementation
 *       left as an exercise. Only implements:  1+2=3
 *
 * $ msp430-size calc.elf * on the msp430g2231 w/serial_sw_uart
 *   text    data     bss     dec     hex filename
 *   1642       0       2    1644     66c calc.elf
 *
 */

#include <fabooh.h>
#include <main.h>

#include <serial.h>
#include "scanner.h"

namespace {
  const uint32_t BAUD_RATE = 9600;
  serial_default_t<BAUD_RATE, CPU::frequency, TX_PIN, RX_PIN > Serial; // TX=varies, RX=varies

  const char *prompt = "\r\nexpr> ";
}

void showtoken(scanner_token &token); // forward declaration

void blink() {
  unsigned cnt = 6;
  do {
    RED_LED::toggle();
    delay(100);
  } while(--cnt);

  RED_LED::low();
}

void setup() {
  Serial.begin(BAUD_RATE);
  RED_LED::setmode_output();
  RED_LED::low();
}


ALWAYS_INLINE
void parse_expr() {
  scanner_state scanner; // use default 24 byte buffer

  scanner.init();

  /*
   * get a line of input from the serial port with echo and delete support
   */
  do {
    int c = Serial.read();

    if ( c == 127 ) { // delete key
      if ( scanner.start > scanner.inbuf ) {
        scanner.start--;
        Serial.write(c);
      }
      continue;
    }

    if ( c == '\r' || c == '=' ) { // end of input
      *scanner.start = c;
      break;
    }

    if ( scanner.start < scanner.endbuf ) { // are we going to exceed the buffer?
      *(scanner.start++) = c;
      Serial.write(c);
    }
    else {
      blink(); //  ring the bell, they exceeded the buffer size
    }

  } while(1);


  scanner.end = scanner.start;
  scanner.start = scanner.inbuf;

  const int MAX_TOKENS=6; /* 2+4 bytes 36 bytes */

  scanner_token opstack[MAX_TOKENS], *token;
  unsigned opcode;

  token = opstack;

  do {
    opcode = scan(scanner, *token);
    showtoken(*token);
    if (token + 1 < &opstack[MAX_TOKENS]) {
      token++; // just overwrite the last op if they provide too many
    }
    else {
      blink();
    }
  } while (opcode != T_EOI);

  // OK, I parsed the string into tokens for you. I'll leave
  // the calculator implementation to you

  // To get you started, the sample below can deal with 1+2=3

  if ( opstack[0].opcode == T_INT16 &&
       opstack[1].opcode == T_OPERATOR &&
       opstack[2].opcode == T_INT16 ) {
    long n0 = (unsigned)opstack[0].n16, n1=(unsigned)opstack[2].n16;

    switch(opstack[1].n16) {
    case '+': n0 += n1; break;
    case '-': n0 -= n1; break;
    case '/': n0 /= n1; break;
    case '*': n0 *= n1; break;
    case '%': n0 %= n1; break;
    default: break;
    }

    // repeat back what they told us
    Serial << endl << opstack[0].u16 << _RAW(opstack[1].n16) << n1 << "=" << n0 << endl;
  }
  else {
    Serial << endl << "error!\n";
  }
}

/*
 * calculator implementation using re2c parser
 */
void loop() {
  do {
    Serial.print(prompt);
    parse_expr();
  } while(1);
}

/*
 * debug helper turns unprintable to '.'
 */
uint8_t guard_raw(unsigned c) {
  if ( c >= ' ' && c < 127 ) {
    return c;
  }
  else {
    return '.';
  }
}

/*
 * debug output to show the results of parser the input stream into tokens
 */
void showtoken(scanner_token &token) {
#if 0
    Serial << "\ntoken.opcode=0x" << _HEX(token.opcode);

    if ( token.opcode == T_INT16 ) {
      Serial << ", .n16=" << token.n16 << endl;
    }
    else if ( token.opcode == T_INT32 ) {
      Serial << ", .n32=" << token.n32 << endl;
    }
    else {
      Serial  << ", .opcode='"<< _RAW(guard_raw(token.opcode)) << "'"
              << ", .n16=0x" << _HEX(token.n16)
              << ", .n16='" << _RAW(guard_raw(token.n16)) << "'"
              << endl;
    }
#endif
}
