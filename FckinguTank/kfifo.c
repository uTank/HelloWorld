#include <stdio.h>
#include <stdlib.h>
#include "kfifo.h"
#include "log.h"

unsigned int kfifo_unused(struct kfifo *fifo)
{
	return (fifo->mask + 1) - (fifo->in - fifo->out);
}


int kfifo_alloc(struct kfifo *fifo, unsigned int size, unsigned int esize)
{
//	if(!(is_power_of_2(size)))
//		size = roundown_pow_of_2(size);

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;

	if(size < 2)
	{
		fifo->data = NULL;
		fifo->mask = 0;
		return -1;
	}

	fifo->data = malloc(size * esize);
	if(!fifo->data)
	{
		fifo->mask = 0;
		return -1;
	}
	fifo->mask = size - 1;
	return 0;
}


void kfifo_free(struct kfifo *fifo)
{
	free(fifo->data);
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = 0;
	fifo->data = NULL;
	fifo->mask = 0;
}


int kfifo_init(struct kfifo *fifo, void *buffer, unsigned int size, unsigned int esize)
{
	size /= esize;

//	if(!is_power_of_2(size))
//		size = roundown_pow_of_2(size);

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
	fifo->data = buffer;

	if(size < 2)
	{
		fifo->mask = 0;
		return -1;
	}

	return 0;
}

void kfifo_copy_in(struct kfifo *fifo, const void *src, 
		unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;

	off &= fifo->mask;
	if(esize != 1)
	{
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);

	memcpy(fifo->data + off, src, l);
	memcpy(fifo->data, src + l, len - l);
}

unsigned int kfifo_in(struct kfifo *fifo, 
		const void *buf, unsigned int len)
{
	unsigned int l;

	l = kfifo_unused(fifo);
	if(len > l)
		len = l;

	kfifo_copy_in(fifo, buf, len, fifo->in);

	fifo->in += len;

	return len;
}

void kfifo_copy_out(struct kfifo *fifo, void *dst,
		unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;

	off &= fifo->mask;
	if(esize != 1)
	{
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);

	memcpy(dst, fifo->data + off, l);
	memcpy(dst + l, fifo->data, len - l);
}

unsigned int kfifo_out_peek(struct kfifo *fifo, void *buf, unsigned int len)
{
	unsigned int l;

	l = fifo->in - fifo->out;
	if(len > l)
		len = l;

	kfifo_copy_out(fifo, buf, len, fifo->out);

	return len;
}

unsigned int kfifo_out(struct kfifo *fifo, void *buf, unsigned int len)
{
	len = kfifo_out_peek(fifo, buf, len);
	fifo->out += len;

	return len;
}

void kfifo_disp_info(struct kfifo *fifo)
{
	printf("fifo->in = %d\n", fifo->in);
	printf("fifo->out = %d\n", fifo->out);
	printf("fifo->mask = %d\n", fifo->mask);
	printf("fifo->esize = %d\n", fifo->esize);
	printf("fifo->data = %p\n", fifo->data);
}

int main(void)
{
	struct kfifo fck;
	struct kfifo *fifo = &fck;
	int tmp, array[256];
	int out[256];
	int i;
	tmp = kfifo_alloc(fifo, 256, sizeof(int));
	printf("\nkfifo_alloc ret = %d\n", tmp);
	kfifo_disp_info(fifo);
	for(i = 0; i < ARRAY_SIZE(array); i++)
		array[i] = i;
//	for(i = 0; i < 100; i++)
	tmp = kfifo_in(fifo, array, 100);
	printf("\nkfifo_in ret = %d\n", tmp);
	kfifo_disp_info(fifo);
	
	tmp = kfifo_out(fifo, out, 10);
	printf("\nkfifo_out ret = %d\n", tmp);
	kfifo_disp_info(fifo);
	for(i = 0; i < 10; i++)
		printf("out[%d]= %d\n", i, out[i]);
	kfifo_free(fifo);

	return 0;
}

