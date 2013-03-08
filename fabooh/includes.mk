#
# includes.mk - common include used by fabooh example makefiles
#
# Created: Feb 28, 2012
#  Author: rick@kimballsoftware.com
#    Date: 03-02-2012
# Version: 1.0.2
#

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

FABOOH_DIR?=$(patsubst %/,%,$(SELF_DIR))
FABOOH_PLATFORM?=$(FABOOH_DIR)/msp430

#include $(FABOOH_DIR)/include-msp430g2231in14.mk
#include $(FABOOH_DIR)/include-msp430g2553in20.mk
include $(FABOOH_DIR)/include-msp430fr5739.mk

# user command line additional CFLAGS
FLAGS?=

MSP430_STDLST = $(FABOOH_DIR)/tools/msp430-stdlst
MSPDEBUG = mspdebug
CC = msp430-gcc

INCLUDE=-I $(FABOOH_PLATFORM)/cores/$(CORE) \
		-I $(FABOOH_PLATFORM)/variants/$(BOARD) \
		-I $(FABOOH_PLATFORM)/cores/$(CORE)/drivers

# -flto -fwhole-program -fwrapv -fomit-frame-pointer \

CFLAGS= -g -Os -Wall -Wunused -mdisable-watchdog \
		-std=gnu++98 \
 		-fdata-sections -ffunction-sections \
		-fwrapv -fomit-frame-pointer \
		-mmcu=$(MCU) -DF_CPU=$(F_CPU) $(INCLUDE) \
		$(STACK_CHECK) $(FLAGS)

ASFLAGS = $(CFLAGS)
CCFLAGS = $(CFLAGS)
LDFLAGS=-g -mmcu=$(MCU) -mdisable-watchdog \
		-Wl,--gc-sections,-Map=$(TARGET).map,-umain

LDLIBS?=

OBJECTS?=$(TARGET).o

all: $(TARGET).elf

$(TARGET).elf : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET).elf $(LDLIBS)
	$(MSP430_STDLST) $(TARGET).elf

clean:
	@echo "cleaning $(TARGET) ..."
	@rm -f $(OBJECTS) $(TARGET).map $(TARGET).elf $(TARGET).d
	@rm -f $(TARGET)_asm_mixed.txt
	@rm -f $(TARGET)_asm_count.txt
	@rm -f $(TARGET).hex
	@rm -f $(TARGET).map
 
install: all
	$(MSPDEBUG) rf2500 "prog $(TARGET).elf"
 
size: all
	msp430-size $(TARGET).elf
	
%.o : %.cpp 
	$(CC) $(CFLAGS) -c $<

%.o : %.c 
	$(CC) $(CFLAGS) -c $<

%.cpp:	%.ino
	echo "#include <fabooh.h>" > header.tmp
	cat header.tmp $< > $@
	rm header.tmp

