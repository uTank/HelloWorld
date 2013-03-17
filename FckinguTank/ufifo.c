#include <stdio.h>
#include "base.h"

struct fifo{
	uint in;
	uint out;
	uint mask;
	uint esize;
	void *data;
};

int fifo_alloc(struct *fifo, uint size, uint esize)
{

}
