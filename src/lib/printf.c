/*
Source form vsprintf.c of linux
*/

#include <stdarg.h>

#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define SMALL   64              /* use 'abcdef' instead of 'ABCDEF' */

static char buf[1024];

int printfk(const char *fmt,...)
{
	char * str;
	int flags;
	va_list args;
	int field_width;
	
	va_start(args, fmt);
	for(str = buf; *fmt; ++fmt) {
		if(*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
		flags = 0;
		repeat:
			++fmt;
			switch(*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
			}
		field_width = -1;
	}
	va_end(args);
	return 0;
}
