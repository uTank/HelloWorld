#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"
#include "log.h"

/* ��̬������ */


/* ��ͷ���ĵ�������������ʵ�� */

/* ���������ʼ��Ϊ��, ��̬����һ��ͷ���, ����ͷ����ָ������Ϊ�� */
int LinkListInit(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct Node));
	if(*L == NULL)
		return -1;
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
void LinkListClear(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
}

/* �жϵ������Ƿ�Ϊ�վ��ǿ��������ͷ����ָ�����Ƿ�Ϊ�� */
Status LinkListEmpty(LinkList head)
{
	return head->next == NULL;
}

/**
 * ��ʼ���������Ա�L�Ѵ��ڡ�
 * �������������L������Ԫ�ظ��� 
**/
int LinkListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* pָ���һ����� */
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
/**
 * ����һ�����pָ�������һ����㣬��ʼ��j��1��ʼ��
 * ��j < iʱ���ͱ���������p��ָ������ƶ�������ָ����һ��㣬j�ۼ�1;
 * ��������ĩβPΪ�գ���˵����i��Ԫ�ز����ڣ�
 * ������ҳɹ������ؽ��p�����ݡ�
**/
Status LinkListGetElem(LinkList L, int i, ElemType *e)
{
	int j = 1;
	LinkList p;

	p = L->next; /* pָ������L�ĵ�һ����� */
	while(p && j < i)
	{
		p = p->next; /* pָ����һ����� */
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
int LinkListLocateElemExt(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
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
 * ��ʼ������˳�����Ա�L�Ѵ��� 
 * �������������L�е�1����e�����ϵ������Ԫ�ص�λ��
 * ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 
**/
int LinkListLocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		if(p->data == e)
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

/**
 * �������i�����ݲ�������㷨˼·��
 * 
 * ����һ���pָ�������һ����㣬��ʼ��j��1��ʼ��
 * ��j < iʱ���ͱ���������p��ָ������ƶ�������ָ����һ��㣬j�ۼ�1;
 * ��������ĩβpΪ�գ���˵����i��Ԫ�ز����ڣ�
 * ������ҳɹ�����ϵͳ������һ���ս��s;
 * ������Ԫ��e�xֵ��s->data;
 * ������Ĳ����׼���s->next=p->next;	p->next=s;
 * ���سɹ���
**/
Status LinkListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;

	p = *L; /* pָ��ͷ��� */
	j = 1;
	while(p && j < i)
	{
		p = p->next;
		j++;
	}

	if(!p || j > i)
		return -1;

	s = (LinkList)malloc(sizeof(struct Node));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return 0;
}

/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
/**
 * ������ɾ����i�����ݽ����㷨˼·��
 * 
 * ����һ���pָ�������һ����㣬��ʼ��j��1��ʼ;
 * ��j < iʱ���ͱ���������p��ָ������ƶ�������ָ����һ����㣬j�ۼ� 1��
 * ��������ĩβpΪ�գ���˵����i��Ԫ�ز����ڣ�
 * ������ҳɹ�������ɾ���Ľ��p->next�xֵ��q;
 * �������ɾ����׼���p->next=q->next;
 * ��q����е����ݸ�ֵ��e,��Ϊ���أ�
 * �ͷ�q��㣻
 * ���سɹ���
**/
Status LinkListDelete(LinkList *L, int i, ElemType *e)
{
	int j = 1;
	LinkList p, q;

	p = *L;
	while(p->next && j < i)
	{
		p = p->next;
		j++;
	}
	if(!(p->next) || j > i)
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

void LinkListVisit(ElemType e)
{
	printf("-> %d ", e);
}

/**
 * �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨��
 *
 * ���������������㷨˼·��
 * 
 * ����һ���p�ͼ���������i��
 * ��ʼ��һ������L��
 * ��L��ͷ����ָ��ָ��NULL,������һ����ͷ���ĵ�����
 * ѭ����
 *     ����һ�½���xֵ��p;
 *     �������һ�����xֵ��P��������p->data;
 *     ��p���뵽ͷ�����ǰһ�½��֮�䡣
**/
void LinkListCreateHead(LinkList *L, int n)
{
	LinkList p;
	int i;

	srand(time(NULL));
	*L = (LinkList)malloc(sizeof(struct Node));
	(*L)->next = NULL;  /*  �Ƚ���һ����ͷ���ĵ����� */
	for(i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(struct Node));
		p->data = rand() % 100;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}


/* �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��β�巨��*/
void LinkListCreateTail(LinkList *L, int n)
{
	LinkList p, r;
	int i;

	srand(time(NULL));

	*L = (LinkList)malloc(sizeof(struct Node));
	r = *L;
	for(i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(struct Node));
		p->data = rand() % 100;
		r->next = p;  /* ����β�ն˽���ָ��ָ���½�� */
		r = p;
	}
	r->next = NULL;
}

/**
 * ������ת:
 *
 * ����:
 *  
 * ���嵱ǰ��� current����ʼֵΪ��Ԫ��㣬current = L->next;
 * ���嵱ǰ���ĺ�̽�� pnext�� pnext = current->next; 
 * ֻҪ pnext ���ڣ���ִ������ѭ����
 * �����½ڵ� prev������ pnext�ĺ�̽�㣬prev = pnext->next;
 * ��pnext�ĺ��ָ��current, pnext->next = current;
 * ��ʱ��pnext ʵ�����Ѿ����� current ǰһλ��Ϊ�µ�current��
 * �������ʱ�� current ���ʵ���ϳ�Ϊ�µ� pnext��current = pnext;
 * ��ʱ���µ� current ���� pnext��current = pnext;
 * ���µ� pnext ���� prev��pnext = prev;
 * ���ͷ����� current �������ϼ��ɣ�L->next = current;
**/
Status LinkListReverse(LinkList L)
{
	LinkList current, pnext, prev;

	if(L->next == NULL)
		return -1;

	current = L->next;
	pnext = current->next;
	current->next = NULL;

	while(pnext)
	{
		prev = pnext->next;
		pnext->next = current;
		current = pnext;
		pnext = prev;
	}
	L->next = current;

	return 0;
}


Status LinkListGetNthNodeFromBack(LinkList L, int n, ElemType *e)
{
	int i = 0;
	LinkList firstNode, secNode;
	firstNode = L;
	secNode = L;
	while(i < n && firstNode->next != NULL)
	{
		i++;
		firstNode = firstNode->next;
	}
	if(firstNode->next == NULL && i < n - 1)
	{
		return -1;
	}

	while(firstNode != NULL)
	{
		secNode = secNode->next;
		firstNode = firstNode->next;
	}

	*e = secNode->data;

	return 0;
}

Status LinkListGetMidNode(LinkList L, ElemType *e)
{
	LinkList search, mid;
	mid = search = L;
	while(search->next != NULL)
	{
		if(search->next->next != NULL)
		{
			search = search->next->next;
			mid = mid->next;
		}
		else
		{
			search = search->next;
		}
	}

	*e = mid->data;

	return 0;
}

int LinkListHasLoop(LinkList L)
{
	LinkList p, q;

	p = q = L;

	while(p != NULL && q != NULL && q->next != NULL)
	{
		p = p->next;
		if(q->next != NULL)
			q = q->next->next;

		if(p == q)
			return 1;
	}

	return 0;
}

Status LinkListBulidLoop(LinkList *L, int num)
{
	int i = 0;
	LinkList cur = *L;
	LinkList tail = NULL;

	if(num <= 0 || L == NULL)
	{
		return -1;
	}
	for(i = 1; i < num; i++)
	{
		if(cur == NULL)
		{
			return -1;
		}
		cur = cur->next;
	}
	tail = cur;
	while(tail->next)
	{
		tail = tail->next;
	}
	tail->next = cur;

	return 0;
}

LinkList LinkListRemoveDupNode(LinkList L)
{
	LinkList p, q, r;

	p = L->next;
	while(p)
	{
		q = p;
		while(q->next)
		{
			if(q->next->data == p->data)
			{
				r = q->next;
				q->next = r->next;
				free(r);
			}
			else
			{
				q = q->next;
			}
		}
		p = p->next;
	}

	return L;
}

void LinkListTest(void)
{
	int opp = 0;
	Status iRet;
	int i, j;
	int pos;
	ElemType e;
	LinkList L; /* ͷָ�� ?? */
	
	iRet = LinkListInit(&L);
	printf("����L��ʼ�����, LinkListLength(L) = %d\n", LinkListLength(L));
	printf("\n1.�������� \n2.������� \n3.ɾ������  \n0.�˳� \n��ѡ����Ĳ�����\n");

	while(opp != '0')
	{
		printf("\n1.�������� \n2.������� \n3.ɾ������  \n0.�˳� \n��ѡ����Ĳ�����\n");
		scanf("%d", &opp);
		log("opp = %d\n", opp);
		switch(opp)
		{
			case 1:
				LinkListTraverse(L, LinkListVisit);
				printf("\n");
				break;
			case 2:
				srand((unsigned)time(NULL));
				for(j = 1; j <= 10; j++)
				{
					iRet = LinkListInsert(&L, j, rand()%100);
				}
				printf("��L�ı�ͷ���β���10���������");				
				LinkListTraverse(L, LinkListVisit);
				printf("\n");
				break;
			case 3:
				printf("Ҫɾ���ڼ���Ԫ��?");
				//scanf("%d" &pos);
				LinkListDelete(&L, 3, &e);
				printf("ɾ����%d��Ԫ�سɹ�,��������Ϊ:\n", pos);
				LinkListTraverse(L, LinkListVisit);
				printf("\n");
				break;
			case 0:
				exit(0);
			default:
				break;
		}
	}
}

int main(void)
{
	LinkListTest();

	return 0;
}


/*
  1.������ת
  2.�ҳ�������ĵ�����4��Ԫ��
  3.�ҳ���������м�Ԫ��
  4.ɾ����ͷ�������һ���ڵ�
  5.�������������������ĺϲ�
  6.�и���������������ÿ��Ԫ�ض�����һ��ָ��һ���������ָ�롣д�����������������һ��������
  7.����������������Ԫ�أ���������ͷ��
  8.�жϵ������Ƿ��л�������ҵ�����"��ʼ"�㣿���֪�����ĳ��ȣ�
  9.�ж������������Ƿ��ཻ
  10.�����������ཻ�������ཻ��
  11.������ģ��������ӷ�����
  12.����������
  13.ɾ�����������ظ���Ԫ��
*/


