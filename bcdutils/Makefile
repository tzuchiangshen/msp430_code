#
# bcd_test makefile
#

TARGET?=bcd_test
MCU?=msp430g2553
F_CPU?=16000000

CC = msp430-gcc

CFLAGS= -g -Os -Wall -Wunused \
 		-fdata-sections -ffunction-sections \
		-flto -fwhole-program -fwrapv -fomit-frame-pointer \
		-mmcu=$(MCU) -DF_CPU=$(F_CPU)
CCFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)
LDFLAGS=-Wl,--gc-sections,-Map=$(TARGET).map,-umain -mdisable-watchdog

MSPDEBUG=mspdebug

OBJECTS = $(TARGET).o bcdutils.o

all : $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET).elf

clean:
	rm -f $(OBJECTS) $(TARGET).map $(TARGET).elf
 
install: all
	$(MSPDEBUG) rf2500 "prog $(TARGET).elf"
 
size: all
	msp430-size $(TARGET).elf
