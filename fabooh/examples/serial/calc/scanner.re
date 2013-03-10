/*
 * scanner.re - sample scanner implementation
 *
 * Desc: this re2c code scans an input line and turns it into tokens and values.
 *
 * Author: rick@kimballsoftware.com
 *
 * See also: http:re2c.org
 *
 */

#include <fabooh.h>
#include <stdlib.h>
#include "scanner.h"

#define YYCURSOR (s.start)

/*
 * _fabooh_atol - lexer helper ascii to decimal stored in long
 *
 * Why? strtol sucks in a bunch of stuff we don't care about,
 * this version doesn't use any extra space and we know the start
 * and end of the string, also we are only converting to decimal.
 */

long _fabooh_atol(const char *lexeme_start, const char *lexeme_end) {
  long n = 0;
  unsigned sign=0;

  if ( *lexeme_start == '-' ) sign=1, lexeme_start++;

  while (lexeme_start < lexeme_end ) {
    n = (n * 10) + (*lexeme_start++ - '0');
  }
  n = (sign) ? -n : n;

  return n;
}

/*
 * scan - scan a buffer and produce tokens
 */
int scan(scanner_state &s, scanner_token &token) {
  char *lexeme = s.start; // keep initial start

  while (1) {/*!re2c
     re2c:indent:top=1;
     re2c:indent:string="  ";
     re2c:define:YYCTYPE="char";
     re2c:yyfill:enable=0;

     ws = [ \t\v\f]+;
     integer = [0-9]+;
     opcode = [\+\-\/\%\*];

     ws { // ignore whitespace
       lexeme = YYCURSOR;
       continue;
     }

     integer { // collapse digits into numbers
       long n = _fabooh_atol(lexeme,YYCURSOR);

       if ( n < 65536 ) {
         token.opcode = T_INT16;
         token.n16 = n;
       }
       else {
         token.opcode = T_INT32;
         token.n32 = n;
       }
       return token.opcode;
     }

     opcode { // lump all the operators into one token
       token.opcode = T_OPERATOR;
       token.n16 = *lexeme;
       return token.opcode;
     }

     "=" { // end of input equals style
       token.opcode = T_EOI;
       token.n16 = *lexeme;
       return token.opcode;
     }

     "\r" { // end of input enter style
       token.opcode = T_EOI;
       token.n16 = *lexeme;
       return token.opcode;
     }

     [^] { // everthing else, let the grammar deal with it
       token.opcode = (tokens_e)*lexeme;
       return token.opcode;
     }

     */
  }

  return -2; // shouldn't see this value
}
