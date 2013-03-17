#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue-link.h"


/* 单链队列 */
typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front; /* 队头 */
	QueuePtr rear;  /* 队尾 */
}LinkQueue;

Status LinkQueueInit(LinkQueue *Q)
{
	Q->front = Q->rear = malloc(sizeof(QNode));
	if(Q->front == NULL)
		return -1;

	Q->front->next = NULL;

	return 0;
}

void LinkQueueDestroy(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

void LinkQueueClear(LinkQueue *Q)
{
	QueuePtr p, q;

	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;

	while(p)
	{
		q = p;
		p = q->next;
		free(q);
	}
}

Status LinkQueueEmpty(LinkQueue *Q)
{
	if(Q->front->next == NULL)
		return 1;
	else
		return 0;
}

int LinkQueueLength(LinkQueue *Q)
{
	int i = 0;
	QueuePtr p;
	p = Q->front;
	while(Q->rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status LinkQueueGetHead(LinkQueue *Q, ElemType *e)
{
	QueuePtr p;

	if(Q->front == Q->rear)
		return -1;

	p = Q->front->next;

	*e = p->data;

	return 0;
}

Status LinkQueueEn(LinkQueue *Q, ElemType e)
{
	QueuePtr p = malloc(sizeof(QNode));
	if(p == NULL)
		return -1;
	p->data = e;
	p->next = NULL;

	Q->rear->next = p;
	Q->rear = p;

	return 0;
}

Status LinkQueueDe(LinkQueue *Q, ElemType *e)
{
	QueuePtr p;

	if(Q->front == Q->rear)
		return -1;

	p = Q->front->next;

	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)
	{
		Q->rear = Q->front;
	}
	free(p);

	return 0;
}

void LinkQueueTraverse(LinkQueue *Q, void (*vi)(ElemType))
{
	QueuePtr p;
	p = Q->front->next;
	while(p)
	{
		vi(p->data);
		p = p->next;
	}
}


