#ifndef U_BASE_H
#define U_BASE_H

#define U_DEBUG
//#undef U_DEBUG

#ifdef U_DEBUG
#define debug_msg printf
#else
#define debug_msg
#endif

typedef unsigned long  ulong;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned char  BYTE;

#ifndef byte
#define byte unsigned char
#endif

#ifndef word
#define word unsigned short
#endif

#ifndef dword
#define dword unsigned int
#endif


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
#endif

#ifndef swap
#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = (__tmp);} while(0)
#endif

#ifndef is_power_of_2
#define is_power_of_2(x) ((x) != 0 && (((x) & ((x)-1))==0))
#endif
#define roundown_pow_of_2(x)


#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define min(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x < _y ? _x : _y; })

#define max(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x > _y ? _x : _y; })


enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,			/* enumerating */
	USB_SPEED_LOW, USB_SPEED_FULL,	/* usb 1.1 */
	USB_SPEED_HIGH,				    /* usb 2.0 */
	USB_SPEED_WIRELESS,			    /* wireless (usb 2.5) */
	USB_SPEED_SUPER,			    /* usb 3.0 */
};

/* -.- */
#if 0

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* 需要释放内存 */
char *make_message(const char *fmt, ...)
{
	int n, size = 100;
	char *p, *np;
	va_list ap;

	if((p = malloc(size)) == NULL)
		return NULL;

	while(1) {
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);

		if(n > -1 && n < size)
			return p;
		if(n > -1)
			size = n+1;
		else
			size *= 2;

		if((np = realloc(p, size)) == NULL) {
			free(p);
			return NULL;
		} else {
			p = np;
		}
	}
}

#endif
/* -.- */

#endif /* U_BASE_H */
