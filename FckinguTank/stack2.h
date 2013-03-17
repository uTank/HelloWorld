#ifndef __STACK2_H__
#define __STACK2_H__

#define ElemType    int

int StackCreate(size_t size);

void StackDestroy(void);

void StackPush(ElemType value);

void StackPop(void);

ElemType StackTop(void);

int StackEmpty(void);

int StackFull(void);

#endif

