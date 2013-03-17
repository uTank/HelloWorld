#ifndef _K_FIFO_H_
#define _K_FIFO_H_

#include "base.h"

typedef struct kfifo{
	unsigned int in;
	unsigned int out;
	unsigned int mask;
	unsigned int esize;
	void         *data;
}KFIFO;

#if 0
kfifo_alloc
kfifo_init
kfifo_in
kfifo_out
kfifo_out_peek
kfifo_size
kfifo_len
kfifo_avail
kfifo_is_empty
kfifo_is_full
kfifo_reset
kfifo_free
#endif

#endif

