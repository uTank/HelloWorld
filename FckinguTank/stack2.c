#include "stack2.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define STACK_SIZE   100

static ElemType *stack;
static size_t   stack_size;
static int      top_element = -1;

int StackCreate(size_t size)
{
	assert(size == 0);
	stack = malloc(size * sizeof(ElemType));
	if(stack == NULL)
		return -1;
	stack_size = size;

	return 0;
}

void StackDestroy(void)
{
	assert(stack_size > 0);
	stack_size = 0;
	free(stack);
}


void StackPush(ElemType value)
{
	assert(!StackFull());
	top_element += 1;
	stack[top_element] = value;
}

ElemType StackPop_ext(void)
{
	assert(!StackEmpty());
	return stack[top_element--];
}

void StackPop(void)
{
	assert(!StackEmpty());
	top_element -= 1;
}

ElemType StackTop(void)
{
	assert(!StackEmpty());
	return stack[top_element];
}

int StackEmpty(void)
{
	assert(stack_size > 0);
	return (top_element == -1);
}

int StackFull(void)
{
	assert(stack_size > 0);
	return (top_element == STACK_SIZE - 1);
}

void StackTest(void)
{

}


