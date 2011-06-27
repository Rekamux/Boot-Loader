.PHONY: program clean music jump

prog ?= playMusic.bin
p = ../exec/$(prog)
mid ?= still_alive.mid
chan ?= 0
full_mid =../midi/fichiers_midi/$(mid) 

bin = $(patsubst %.mid,%.bin,$(mid))
mus = $(patsubst %.mid,%.mus,$(mid))

music: mySleep $(full_mid) musToBinary
	../midi/midi_parse.py $(full_mid) $(chan) > $(mus)
	./musToBinary $(mus) $(bin)
	echo -n "l 0c500000" > /dev/ttyS0
	./mySleep
	cat $(bin) > /dev/ttyS0
	./mySleep 1500

$(p):
	make -C ../exec

program: mySleep $(p)
	echo -n "l 0c000000" > /dev/ttyS0
	./mySleep
	cat $(p) > /dev/ttyS0
	./mySleep 1500

jump:
	echo -n "g 0c000000" > /dev/ttyS0
	./mySleep 1500

clean:
	rm -f musToBinary *~ mySleep *.mus *.bin
