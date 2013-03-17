#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "queue-sq.h"

typedef int  ElemType;
typedef int  Status;

/* Ñ­»·¶ÓÁÐ */
#define MAX_QSIZE     100

typedef struct queue
{
	ElemType *base;
	int front;
	int rear;
}SqQueue;

Status QueueInit(SqQueue *Q)
{
	Q->base = malloc(MAX_QSIZE*sizeof(ElemType));
	if(Q->base == NULL)
		return -1;

	Q->front = 0;
	Q->rear = 0;

	return 0;
}

void DestroyQueue(SqQueue *Q)
{
	if(Q->base)
		free(Q->base);

	Q->base = NULL;
	Q->front = Q->rear = 0;
}

int QueueEmpty(SqQueue *Q)
{
	if(Q->front == Q->rear)
		return 1;
	else
		return 0;
}


int QueueLength(SqQueue *Q)
{
	return (Q->rear - Q->front + MAX_QSIZE) % MAX_QSIZE;
}

int GetHead(SqQueue *Q, ElemType *e)
{
	if(Q->front == Q->rear) // ¿Õ
		return -1;

	*e = Q->base[Q->front];

	return 0;
}

int EnQueue(SqQueue *Q, ElemType e)
{
	if((Q->rear + 1) % MAX_QSIZE == Q->front) // Âú
		return -1;

	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAX_QSIZE;

	return 0;
}

int DeQueue(SqQueue *Q, ElemType *e)
{
	if(Q->front == Q->rear) // ¿Õ
		return -1;

	*e = Q->base[Q->front];

	Q->front = (Q->front + 1) % MAX_QSIZE;

	return 0;
}

void QueueTraverse(SqQueue *Q, void (*vi)(ElemType))
{
	int i;

	i = Q->front;

	while(i != Q->rear)
	{
		vi(Q->base[i]);
		i = (i + 1) % MAX_QSIZE;
	}
}

void QueueVia(ElemType e)
{
	printf("QueueElem = %d\n", e*e);
}

void QueueTest(void)
{
	int i, iRet;
	int iTmp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9,};
	SqQueue q, *pQueue;
	pQueue = &q;

	iRet = QueueInit(pQueue);
	if(iRet != 0)
	{
		log("QueueInit - Failed\n");
	}
	printf("QueueLength = %d\n", QueueLength(pQueue));
	
	for(i = 0; i < 45; i++)
		printf("EnQueue(%d) = %d\n", i, EnQueue(pQueue, i));
	
	printf("QueueLength = %d\n", QueueLength(pQueue));

	QueueTraverse(pQueue, QueueVia);
}

int main(void)
{
	QueueTest();

	return 0;
}
