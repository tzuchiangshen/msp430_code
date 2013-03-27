#
# fabooh example makefile
#

TARGET?=fixmath_table
LDLIBS?=
USEROBJS=fix16_trig.o fix16.o fix16_str.o

#
# minimize size by turning off some memory and flash hungry features
#
FLAGS=-DFIXMATH_NO_CACHE -DFIXMATH_NO_64BIT -DFIXMATH_NO_ROUNDING

include ../../../common.mk

fix16_trig.o: libfixmath/fix16_trig.c
	$(CC) $(CFLAGS) -c $< -o $@

fix16.o: libfixmath/fix16.c
	$(CC) $(CFLAGS) -c $< -o $@

fix16_str.o: libfixmath/fix16_str.c
	$(CC) $(CFLAGS) -c $< -o $@
