#include "common.h"
#include "lcd.h"
#include "keymatrix.h"

static void put_dec(int num)
{
	char buf[5];
	unsigned char i;

	for (i = 0; num; i++) {
		buf[i] = (num % 10) + '0';
		num /= 10;
	}
	for (; i > 0; i--)
		put_char(buf[i - 1]);
}

int main(void)
{
	char c;
	int term[2], result;
	unsigned int current_term;

	lcd_init();
	keymatrix_init();

	while (1) {
		put_char('>');
		term[0] = 0;
		term[1] = 0;
		current_term = 0;
		while (1) {
			c = get_char();
			put_char(c);
			if ('0' <= c && c <= '9') {
				term[current_term] = (term[current_term] * 10) + (c - '0');
			} else if (c == '*') {
				current_term++;
			} else if (c == '\n') {
				result = term[0] * term[1];
				put_dec(result);
				get_char();	/* 演算結果表示後、何らかのキー入力を待つ */
				break;
			}
		}
		put_char('\n');
	}

	return 0;
}
