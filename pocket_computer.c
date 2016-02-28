#include "common.h"
#include "lcd.h"
#include "keymatrix.h"

int main(void)
{
	char str[2] = { 0 };

	lcd_init();
	keymatrix_init();

	while (1) {
		str[0] = get_char();
		put_str(str);
	}

	return 0;
}
