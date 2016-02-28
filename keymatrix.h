#ifndef _KEYMATRIX_H_
#define _KEYMATRIX_H_

#define KEY_COLS	3
#define KEY_ROWS	4

extern const char key_map[KEY_COLS][KEY_ROWS];

void keymatrix_init(void);
char check_key(unsigned char c);

#endif /* _KEYMATRIX_H_ */
