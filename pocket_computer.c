#include "common.h"
#include "lcd.h"
#include "keymatrix.h"

int main(void)
{
	char recog_row, str[2] = { 0 };
	unsigned char i = 0;

	lcd_init();
	keymatrix_init();

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
