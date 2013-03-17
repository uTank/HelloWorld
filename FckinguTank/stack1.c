#include "stack1.h"
#include <stdio.h>
#include <assert.h>

#define STACK_SIZE   100

static ElemType stack[STACK_SIZE];
static int      top_element = -1;

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
	return (top_element == -1);
}

int StackFull(void)
{
	return (top_element == STACK_SIZE - 1);
}

void StackTest(void)
{

}

