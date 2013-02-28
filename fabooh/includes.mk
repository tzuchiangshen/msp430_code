#
# includes.mk - common include used by fabooh example makefiles
#
#    Date: 02-28-2013
# Version: 1.0.0
#

FABOOH_DIR?=../..
FABOOH_TLD?=$(FABOOH_DIR)/msp430

CORE?=fabooh
MCU?=msp430g2553
F_CPU?=16000000
BOARD?=msp430g2553in20

# user command line additional CFLAGS
FLAGS?=

MSPDEBUG = mspdebug
CC = msp430-gcc

INCLUDE=-I $(FABOOH_TLD)/cores/$(CORE) \
		-I $(FABOOH_TLD)/variants/$(BOARD) \
		-I $(FABOOH_TLD)/cores/$(CORE)/drivers

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
	msp430-stdlst $(TARGET).elf

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

