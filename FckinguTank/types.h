#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long long  ulong;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef short               s16;
typedef int                 s32;
typedef long long           s64;


#define ARRAY_SIZE(x)       (sizeof(x) / sizeof((x)[0]))

#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = (__tmp);} while(0)

#define min(x,y)  ({     \
	typeof(x) _x = (x);  \
	typeof(y) _y = (y);  \
	(void) (&_x == &_y); \
	_x < _y ? _x : _y; })

#define max(x,y)  ({     \
	typeof(x) _x = (x);  \
	typeof(y) _y = (y);  \
	(void) (&_x == &_y); \
	_x > _y ? _x : _y; })

#define min_t(type, x, y) ({	\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({	\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1: __max2; })


#define roundup(x, y) (	{			\
	const typeof(y) __y = y;		\
	(((x) + (__y - 1)) / __y) * __y; })

#define rounddown(x, y) ({	\
	typeof(x) __x = (x);	\
	__x - (__x % (y));	})


#endif /* _TYPES_H_ */
