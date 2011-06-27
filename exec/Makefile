.PHONY: all clean

CEXEC = $(wildcard *.c)
TARGETS = $(patsubst %.c,%.bin,$(CEXEC))
ELFs = $(patsubst %.bin,%.elf,$(TARGETS))
LSTs = $(patsubst %.bin,%.lst,$(TARGETS))
MAPs = $(patsubst %.bin,%.map,$(TARGETS))
CSOURCES = $(shell echo ../lib/*.c)
OBJs = $(patsubst %.c,%.o,$(CSOURCES))

all: $(TARGETS) $(LSTs) $(MAPs) $(ELFs)

_START = 0x0c000000

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
DMP = arm-none-eabi-objdump
CFLAGS = -Wall -Werror -O2
LFLAGS = -e $(_START) -T linkerScript.ld
ASFLAGS = -g -mcpu=arm7tdmi
LMFLAGS = --print-map --cref
DFLAGS = -D
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
CPFLAGS = -O binary

%.lst: %.elf
	$(DMP) $(DFLAGS) $< > $@

%.map: %.o $(OBJs)
	$(LD) $^ $(LFLAGS) $(LMFLAGS) > $@

%.elf: $(OBJs) %.o crt0.o
	$(LD) $(LFLAGS) -o $@ $^

%.bin: %.elf
	$(OBJCOPY) $(CPFLAGS) $^ $@

clean:
	rm -f *.o $(TARGETS) *~ *.lst *.map *.elf a.out
