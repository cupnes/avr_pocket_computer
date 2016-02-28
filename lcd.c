#include <avr/io.h>
#include "common.h"
#include "lcd.h"

#define	LCD_PORT	PORTD

#define	LCD_E(b) {			\
	if(b) LCD_PORT |= _BV(3);	\
	else LCD_PORT &= ~_BV(3);	\
}

#define	LCD_RS(b) {			\
	if(b) LCD_PORT |= _BV(2);	\
	else LCD_PORT &= ~_BV(2);	\
}

unsigned char current_row;

static void lcd_write8(unsigned char ch)
{
	LCD_PORT = (LCD_PORT & 0x0f) | (ch & 0xf0);

	LCD_E(1);
	waitus(1);
	LCD_E(0);
	waitus(100);
}

static void lcd_write4(unsigned char ch)
{
	lcd_write8(ch);
	lcd_write8(ch << 4);
}

static void line_feed(void)
{
	static unsigned char current_line = 0;

	LCD_RS(0);
	if (current_line == 0) {
		lcd_write4(0xc0);
		current_line = 1;
	} else {
		lcd_write4(0x80);
		current_line = 0;
	}
}

void lcd_init(void)
{
	PORTD = 0;
	DDRD = 0xfc;

	LCD_RS(0);
	LCD_E(0);
	waitms(100);

	lcd_write8(0b00110000);
	waitms(5);

	lcd_write8(0b00110000);
	waitus(100);

	lcd_write8(0b00110000);

	lcd_write8(0b00100000);

	lcd_write4(0b00101000);

	lcd_write4(0b00000110);
	lcd_write4(0b00001111);

	lcd_write4(0b00000001);
	waitms(2);
}

void put_char(char c)
{
	LCD_RS(1);
	lcd_write4(c);
	if (++current_row >= 16) {
		line_feed();
		current_row = 0;
	}
}

void put_str(char *s)
{
	LCD_RS(1);
	while (*s) {
		lcd_write4(*s++);
		if (++current_row >= 16) {
			line_feed();
			current_row = 0;
		}
	}
}
