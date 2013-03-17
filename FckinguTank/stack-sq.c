#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqstack.h"

/* Ë³ÐòÕ» */

typedef int ElemType;
typedef int Status;

#define SQ_STACK_MAX_SIZE       100

typedef struct sqstack{
	ElemType data[SQ_STACK_MAX_SIZE];
	int top;
}SqStack;

Status SqStackInit(SqStack *S)
{
	S->top = -1;
	return 0;
}

Status SqStackPush(SqStack *S, ElemType e)
{
	if(S->top == SQ_STACK_MAX_SIZE - 1)
	{
		return -1;
	}
	S->top++;
	S->data[S->top] = e;

	return 0;
}

Status SqStackPop(SqStack *S, ElemType *e)
{
	if(S->top == -1)
		return -1;
	*e = S->data[S->top];
	S->top--;

	return 0;
}

Status SqStackGetTop(SqStack S, ElemType *e)
{
	if(S.top == -1)
		return -1;
	else
		*e = S.data[S.top];

	return 0;
}

Status SqStackEmpty(SqStack S)
{
	return (S.top == -1);
}

Status SqStackClear(SqStack *S)
{
	S->top = -1;
	return 0;
}

int SqStackLength(SqStack S)
{
	return (S.top + 1);	
}

void SqStackTraverse(SqStack S, void (*vi)(ElemType ))
{
	int i = 0;
	while(i <= S.top)
	{
		vi(S.data[i++]);
	}
	return 0;
}

int main(void)
{

}

