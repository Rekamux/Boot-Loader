.PHONY: all program clean music jump

prog ?= playMusic.bin
mid ?= still_alive.mid
chan ?= 0

all:
	make -C exec
	make -C bootLoader
	make -C prog3000

program:
	make prog=$(prog) program -C loadBinary

music:
	make mid=$(mid) chan=$(chan) music -C loadBinary

jump:
	make jump -C loadBinary

clean:
	make clean -C exec
	make clean -C prog3000
	make clean -C bootLoader
	make clean -C loadBinary
	make clean -C lib
	make clean -C midi
	rm -f *~
