#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/* ������ */

/* �������������һ���յľ��Ա�L */
/* */
Status LinkListInit(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode)); /* �a��ͷ���c���KʹLָ���ͷ���c */
	if(*L == NULL)
	{
	  return -1;
	}
	(*L)->next = NULL;

	return 0;
}

/**
* ��ʼ�l�������Ա�L�Ѵ��ڡ�
* ������������پ��Ա�L
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
* ��ʼ���������Ա�L�Ѵ��ڡ�
* �����������L����Ϊ�ձ�
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
* ��ʼ���������Ա�L�Ѵ��ڡ�
* �����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
**/
Status LinkListEmpty(LinkList L)
{
	return L->next == NULL;
}

/**
* ��ʼ���������Ա�L�Ѵ��ڡ�
* �������������L������Ԫ�ظ���
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

/* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
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
* ��ʼ����: ���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1������Ϊ0)
* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0
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
* ��ʼ����: ���Ա�L�Ѵ���
* �������: ��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��������OK��
*           �������ʧ�ܣ�pre_e�޶��壬����INFEASIBLE
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
* ��ʼ���������Ա�L�Ѵ���
* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�
*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE
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

/* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
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

/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
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
* ��ʼ���������Ա�L�Ѵ��ڡ�
* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()
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
	
	printf("����L��ʼ�����, LinkListLength(L) = %d\n", iLen);

	return 0;
}

int main(void)
{
	LinkListTest();
	return 0;
}

