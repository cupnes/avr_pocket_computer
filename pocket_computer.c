#include "common.h"
#include "lcd.h"
#include "keymatrix.h"

int main(void)
{
	lcd_init();
	keymatrix_init();

	while (1)
		put_char(get_char());

	return 0;
}
