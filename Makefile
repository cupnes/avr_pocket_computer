CFLAGS	=	-mmcu=atmega168
CFLAGS	+=	-Wall -Wextra

.c.o:
	avr-gcc $(CFLAGS) -o $@ $<

pocket_computer.hex: pocket_computer.o
	avr-objcopy -O ihex $< $@

program: pocket_computer.hex
	sudo avrdude -p m168 -c avrisp2 -U $<

clean:
	rm -f *~ *.o *.hex

.PHONY: program clean
