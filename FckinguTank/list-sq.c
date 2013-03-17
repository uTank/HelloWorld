#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list-sq.h"


typedef int ElemType;
typedef int Status;

#define MAX_LIST_SIZE     100

typedef struct sqlist{
	ElemType data[MAX_LIST_SIZE];
	int length;
}SqList;


void SqListInit(SqList *L)
{
	L->length = 0;
}

Status SqListEmpty(SqList L)
{
	return (L.length == 0);
}

/**
 * 插入算法的思路：
 * 如果插入位置不合理，抛出异常；
 * 如果线性表长度大于等于数组长度，则抛出异常或动态增加容量；
 * 从最后一个元素开始向前遍历到第i个位置，分别将它们都向后移动一个位置；
 * 将要插入元素填入位置i处；
 * 表长加1
**/
Status SqListInsert(SqList *L, int i, ElemType e)
{
	int k;

	if(L->length == MAX_LIST_SIZE)
		return -1;

	if(i < 1 || i > L->length + 1)
		return -1;

	if(i <= L->length) /* 插入数据位置不在表尾 */
	{
		for(k = L->length - 1; k >= i - 1; k--)
			L->data[k+1] = L->data[k];
	}
	L->data[i-1] = e;
	L->length++;

	return 0;
}


/**
 * 删除算法的思路： 
 * 如果删除位置不合理，抛出异常；
 * 取出删除元素；
 * 从删除元素位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置；
 * 表长减1。
**/
Status SqListDelete(SqList *L, int i, ElemType *e)
{
	int k;

	if(L->length == 0)
		return -1;
	if(i < 1 || i > L->length)
		return -1;

	*e = L->data[i-1];
	if(i < L->length) /* 删除的数据不在表尾 */
	{
		for(k = i; k < L->length; k++)
		{
			L->data[k-1] = L->data[k];
		}
	}
	L->length--;

	return 0;
}

Status SqListGetElem(SqList L, int i, ElemType *e)
{
	if(L.length == 0)
		return -1;
	if(i < 1 || i > L.length)
		return -1;

	*e = L.data[i-1];

	return 0;
}

int SqListLocateElem(SqList L, ElemType e)
{
	int i;
	if(L.length == 0)
		return -1;
	for(i = 0; i < L.length; i++)
	{
		if(L.data[i] == e)
			break;
	}
	if(i >= L.length)
		return -1;

	return (i+1);
}

int SqListLength(SqList L)
{
	return L.length;
}

void SqListClear(SqList *L)
{
	L->length = 0;
}

void SqListVisit(ElemType e)
{
	printf("%d ", e);
}


Status SqListTraverse(SqList L, void (*vi)(ElemType))
{
	int i;
	for(i = 0; i < L.length; i++)
	{
		vi(L.data[i]);
	}
	return 0;
}

/* 删除A中出现B的元素 */
void SqListDelElemAB(SqList *A, SqList B)
{
	int i, flag, pos;
	ElemType e;

	for(i = 0; i <= B.length; i++)
	{
		flag = SqListGetElem(B, i, &e);
		if(flag == 1)
		{
			pos = SqListLocateElem(*A, e);
			if(pos > 0)
				SqListDelete(A, pos, &e);
		}
	}
}

/* 顺序表A和顺序表B的元素都是非递减排列, 将A、B合并成C, C的元素也是非递减排序 */
void SqListMergeListAB(SqList A, SqList B, SqList *C)
{
	int i, j, k;
	ElemType e1, e2;
	i = 1;
	j = 1;
	k = 1;

	while(i <= A.length && j <= B.length)
	{
		SqListGetElem(A, i, &e1);
		SqListGetElem(B, j, &e2);
		if(e1 <= e2)
		{
			SqListInsert(C, k, e1);
			i++;
			k++;
		}
		else
		{
			SqListInsert(C, k, e2);
			j++;
			k++;
		}
	}
	while(i <= A.length)
	{
		SqListGetElem(A, i, &e1);
		SqListInsert(C, k, e1);
		i++;
		k++;
	}
	while(j <= B.length)
	{
		SqListGetElem(B, j, &e2);
		SqListInsert(C, k, e2);
		j++;
		k++;
	}
	C->length = A.length + B.length;
}

void SqListTest(void)
{
	SqList L;
	ElemType e;
	char opp = -1;
	int pos;
	Status ret;

	ret = SqListInit(&L);
	printf("初始化成功，L.length = %d\n", L.length);
	printf("\n1.遍历线性表\n2.线性表赋值\n3.线性表插入\n0.退出\n请选择你的操作:\n");
	while(opp != '0')
	{
		scanf("%c", &opp);
		switch(opp)
		{
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '0':
				break;
			default :
				break;
		}
	}
}

int main(void)
{
	SqListTest();

	return 0;
}

#if 0
#define LIST_INIT_SIZE     100
#define LIST_INCREMENT     10

typedef struct
{
	ElemType *elem;
	int len;
	int size;
}SqList;

int InitList(SqList *L)
{
	L->elem = malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(L->elem == NULL)
		return -1;
	L->len = 0;
	L->size = LIST_INCREMENT;

	return 0;
}

void DestroyList(SqList *L)
{
	free(L->elem);
	L->elem = NULL;
	L->len = 0;
	L->size = 0;
}

void ClearList(SqList *L)
{
	L->len = 0;
}

Status ListEmpty(SqList L)
{
	if(L.len == 0)
		return 1;
	else
		return 0;
}

int ListLength(SqList L)
{
	return L.len;
}

Status GetElem(SqList L, int i, ElemType *e)
{
	if(i < 1 || i > L.len)
		return -1;

	*e = *(L.elem + i - 1);

	return 0;
}

int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	ElemType *p;
	int i = 1;
	p = L.elem;

	while(i <= L.len && !compare(*p++, e))
		++i;

	if(i <= L.len)
		return i;
	else
		return 0;
}

Status PriorElem(SqList L, ElemType cur, ElemType *pre)
{
	int i = 2;
	ElemType *p = L.elem + 1;

	while(i <= L.len && *p != cur)
	{
		p++;
		i++;
	}

	if(i > L.len)
		return -1;
	else
		*pre = *--p;

	return 0;
}

Status NextElem(SqList L, ElemType cur, ElemType *next)
{
	int i = 1;
	ElemType *p = L.elem;

	while(i < L.len && *p != cur)
	{
		i++;
		p++;
	}

	if(i == L.len)
		return -1;
	else
		*next = *++p;

	return 0;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
	ElemType *newbase, *p, *q;

	if(i < 1 || i > L->len + 1)
		return -1;

	if(L->len >= L->size)
	{
		newbase = realloc(L->elem, (L->size + LIST_INCREMENT)*sizeof(ElemType));
		if(newbase == NULL)
			return -1;
		L->elem = newbase;
		L->size += LIST_INCREMENT;
	}

	q = L->elem + i - 1;

	for(p = L->elem + L->len - 1; p >= q; --p)
		*(p+1) = *p;

	*q = e;
	++L->len;

	return 0;
}

Status ListDelect(SqList *L, int i, ElemType *e)
{
	ElemType *p, *q;

	if(i < 1 || i > L->len)
		return -1;

	p = L->elem + i - 1;
	*e = *p;
	q = L->elem + L->len - 1;
	for(++p; p <= q; ++p)
		*(p-1) = *p;

	L->len--;

	return 0;	
}

void ListTraverse(SqList L, void (*vi)(ElemType *))
{
	ElemType *p;
	int i;
	p = L.elem;
	for(i = 1; i <= L.len; i++)
		vi(p++);
}
#endif


