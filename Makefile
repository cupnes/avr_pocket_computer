CFLAGS	=	-mmcu=atmega168
CFLAGS	+=	-Wall -Wextra
SRCS	=	common.c lcd.c pocket_computer.c

pocket_computer.hex: pocket_computer.elf
	avr-objcopy -O ihex $< $@

pocket_computer.elf: $(SRCS)
	avr-gcc $(CFLAGS) -o $@ $+

program: pocket_computer.hex
	sudo avrdude -p m168 -c avrisp2 -U $<

clean:
	rm -f *~ *.o *.elf *.hex

.PHONY: program clean
