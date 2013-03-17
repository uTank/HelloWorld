#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/* 单链表 */

/* 操作结果：構造一个空的線性表L */
/* */
Status LinkListInit(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode)); /* 產生头结點，並使L指向此头结點 */
	if(*L == NULL)
	{
	  return -1;
	}
	(*L)->next = NULL;

	return 0;
}

/**
* 初始條件：線性表L已存在。
* 操作结果：销毁線性表L
**/
void LinkListDestroy(LinkList *L)
{
	LinkList q;
	while(*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}
}

/**
* 初始条件：线性表L已存在。
* 操作结果：将L重置为空表
**/
void LinkListClear(LinkList L)
{
	LinkList p, q;
	p = L->next;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

/**
* 初始条件：线性表L已存在。
* 操作结果：若L为空表，则返回TRUE，否则返回FALSE
**/
Status LinkListEmpty(LinkList L)
{
	return L->next == NULL;
}

/**
* 初始条件：线性表L已存在。
* 操作结果：返回L中数据元素个数
**/
int LinkListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* L为带头结点的单链表的头指针。当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR */
Status LinkListGetElem(LinkList L, int i, ElemType *e)
{
	int j = 1;
	LinkList p = L->next;
	while(p && j < i)
	{
		p = p->next;
		j++;
	}
	if(!p || j > i)
		return -1;
	*e = p->data;

	return 0;
}

/**
* 初始条件: 线性表L已存在，compare()是数据元素判定函数(满足为1，否则为0)
* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。
*           若这样的数据元素不存在，则返回值为0
**/
int LinkListLocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		if(compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

/**
* 初始条件: 线性表L已存在
* 操作结果: 若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK；
*           否则操作失败，pre_e无定义，返回INFEASIBLE
**/
Status LinkListPriorElem(LinkList L, ElemType cur, ElemType *pre)
{
	LinkList q, p = L->next;

	while(p->next)
	{
		q = p->next;
		if(p->data == cur)
		{
			*pre = p->data;
			return 0;
		}
		p = q;
	}
	return -1;
}

/**
* 初始条件：线性表L已存在
* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，
*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE
**/
Status LinkListNextElem(LinkList L, ElemType cur, ElemType *next)
{
	LinkList p = L->next;
	while(p->next)
	{
		if(p->data == cur)
		{
			*next = p->next->data;
			return 0;
		}
		p = p->next;
	}

	return -1;
}

/* 在带头结点的单链线性表L中第i个位置之前插入元素e */
Status LinkListInsert(LinkList *L, int i, ElemType e)
{
	int j = 0;
	LinkList p = *L, s;
	while(p && j < i - 1)
	{
		p = p->next;
		j++;
	}

	if(!p || j > i - 1)
		return -1;

	s = (LinkList)malloc(sizeof(struct LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return 0;
}

/* 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值 */
Status LinkListDelete(LinkList *L, int i, ElemType *e)
{
	int j = 1;
	LinkList p, q;

	p = *L;
	while(p && j < i)
	{
		p = p->next;
		j++;
	}
	if(!p->next || j > i - 1)
		return -1;

	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return 0;
}

/**
* 初始条件：线性表L已存在。
* 操作结果：依次对L的每个数据元素调用函数vi()
**/
void LinkListTraverse(LinkList L, void (*vi)(ElemType))
{
	LinkList p = L->next;
	while(p)
	{
		vi(p->data);
		p = p->next;
	}
}

int LinkListTest(void)
{
	LinkList L;
	Status iState, iLen;

	iState = LinkListInit(&L);
	if(iState != 0)
	{
		return -1;
	}
	iLen = LinkListLength(L);
	
	printf("链表L初始化完毕, LinkListLength(L) = %d\n", iLen);

	return 0;
}

int main(void)
{
	LinkListTest();
	return 0;
}

