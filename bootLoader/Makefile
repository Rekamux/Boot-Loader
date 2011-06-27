.PHONY: all clean

TARGETS = bootLoader
LSTs = $(patsubst %,%.lst,$(TARGETS))
MAPs = $(patsubst %,%.map,$(TARGETS))
CSOURCES = $(shell echo ../lib/*.c)
VPATH = . ../lib
OBJs = $(patsubst %.c,%.o,$(CSOURCES))
HFILES = $(patsubst %.c,%.h,$(CSOURCES))

all: $(TARGETS) $(LSTs) $(MAPs)

_START = 0x00000000

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
DMP = arm-none-eabi-objdump
CFLAGS = -Wall -Werror -O2
LFLAGS = -e $(_START) -T linkerScript.ld
ASFLAGS = -g -mcpu=arm7tdmi
ASFLAGS += $(CFLAGS)
LMFLAGS = --print-map --cref
DFLAGS = -D
OBJDUMP = arm-none-eabi-objdump

%.lst: %
	$(DMP) $(DFLAGS) $< > $@

%.map: %.o $(OBJs)
	$(LD) $^ $(LFLAGS) $(LMFLAGS) > $@

bootLoader: bootLoader.o $(OBJs) crt0.o
	$(LD) $(LFLAGS) -o $@ $^

clean:
	rm -f *.o $(TARGETS) *~ *.lst *.map a.out

dummy:
	echo $(OBJs)
