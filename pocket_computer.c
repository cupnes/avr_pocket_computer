#include <avr/io.h>
#include "common.h"
#include "lcd.h"

#define KEY_COLS	3
#define KEY_ROWS	4
#define KEY_RECOG_THLD	20

static const char key_map[KEY_COLS][KEY_ROWS] = {
	{'3', '6', '9', '#'},
	{'2', '5', '8', '0'},
	{'1', '4', '7', '*'}
};

static char check_key(unsigned char c)
{
	static unsigned char key_counter[KEY_COLS] = { 0 };
	char i, recog_row = -1;

	PORTB = _BV(c);

	waitus(1);

	for (i = 0; i < KEY_ROWS; i++) {
		if (PINC & _BV(i)) {
			recog_row = i;
			key_counter[c]++;
			break;
		}
	}
	if (recog_row < 0)
		key_counter[c] = 0;
	else if (key_counter[c] < KEY_RECOG_THLD)
		recog_row = -1;

	return recog_row;
}

int main(void)
{
	char recog_row, str[2] = { 0 };
	unsigned char i = 0;

	PORTD = 0;
	DDRD = 0xfc;

	DDRB = 0x07;

	lcd_init();

	while (1) {
		if ((recog_row = check_key(i)) >= 0) {
			str[0] = key_map[i][(unsigned char)recog_row];
			lcd_puts(str);
		}
		if (++i >= KEY_COLS)
			i = 0;
	}

	return 0;
}
