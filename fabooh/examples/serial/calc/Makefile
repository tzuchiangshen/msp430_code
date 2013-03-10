#
# fabooh example makefile
#

TARGET?=calc
LDLIBS?=
USEROBJS=scanner.o
USERCLEAN=scanner.o scanner.cpp

include ../../../includes.mk

scanner.cpp: scanner.re
	re2c -is -o $@ $<

