#include "common.h"

void waitus(unsigned int _n)
{
	volatile unsigned int n = _n * 20;
	while (n-- > 0);
}

void waitms(unsigned int _n)
{
	volatile unsigned int n = _n * 20000;
	while (n-- > 0);
}
