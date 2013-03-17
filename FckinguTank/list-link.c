#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"
#include "log.h"

/* 动态单链表 */


/* 带头结点的单链表的运算具体实现 */

/* 将单链表初始化为空, 动态生成一个头结点, 并将头结点的指针域置为空 */
int LinkListInit(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct Node));
	if(*L == NULL)
		return -1;
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

/* 判断单链表是否为空就是看单链表的头结点的指针域是否为空 */
Status LinkListEmpty(LinkList head)
{
	return head->next == NULL;
}

/**
 * 初始条件：线性表L已存在。
 * 操作结果：返回L中数据元素个数 
**/
int LinkListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* p指向第一个结点 */
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* L为带头结点的单链表的头指针。当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR */
/**
 * 声明一个结点p指向链表第一个结点，初始化j从1开始；
 * 当j < i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1;
 * 若到链表末尾P为空，则说明第i个元素不存在；
 * 否则査找成功，返回结点p的数据。
**/
Status LinkListGetElem(LinkList L, int i, ElemType *e)
{
	int j = 1;
	LinkList p;

	p = L->next; /* p指向链表L的第一个结点 */
	while(p && j < i)
	{
		p = p->next; /* p指向下一个结点 */
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
 * 初始条件：顺序线性表L已存在 
 * 操作结果：返回L中第1个与e满足关系的数据元素的位序。
 * 若这样的数据元素不存在，则返回值为0 
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

/**
 * 单链表第i个数据插入结点的算法思路：
 * 
 * 声明一结点p指向链表第一个结点，初始化j从1开始；
 * 当j < i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1;
 * 若到链表末尾p为空，则说明第i个元素不存在；
 * 否则査找成功，在系统中生成一个空结点s;
 * 将数据元素e賦值给s->data;
 * 单链表的插入标准语句s->next=p->next;	p->next=s;
 * 返回成功。
**/
Status LinkListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;

	p = *L; /* p指向头结点 */
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

/* 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值 */
/**
 * 单链表删除第i个数据结点的算法思路：
 * 
 * 声明一结点p指向链表第一个结点，初始化j从1开始;
 * 当j < i时，就遍历链表，让p的指针向后移动，不断指向下一个结点，j累加 1；
 * 若到链表末尾p为空，则说明第i个元素不存在；
 * 否则査找成功，将欲删除的结点p->next賦值给q;
 * 单链表的删除标准语句p->next=q->next;
 * 将q结点中的数据赋值给e,作为返回；
 * 释放q结点；
 * 返回成功。
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

void LinkListVisit(ElemType e)
{
	printf("-> %d ", e);
}

/**
 * 随机产生n个元素的值，建立带表头结点的单链线性表L（头插法）
 *
 * 单链表整表创建的算法思路：
 * 
 * 声明一结点p和计数器变量i；
 * 初始化一空链表L；
 * 让L的头结点的指针指向NULL,即建立一个带头结点的单链表；
 * 循环：
 *     生成一新结点賦值给p;
 *     随机生成一数字賦值给P的数据域p->data;
 *     将p插入到头结点与前一新结点之间。
**/
void LinkListCreateHead(LinkList *L, int n)
{
	LinkList p;
	int i;

	srand(time(NULL));
	*L = (LinkList)malloc(sizeof(struct Node));
	(*L)->next = NULL;  /*  先建立一个带头结点的单链表 */
	for(i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(struct Node));
		p->data = rand() % 100;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}


/* 随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法）*/
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
		r->next = p;  /* 将表尾终端结点的指针指向新结点 */
		r = p;
	}
	r->next = NULL;
}

/**
 * 单链表反转:
 *
 * 步骤:
 *  
 * 定义当前结点 current，初始值为首元结点，current = L->next;
 * 定义当前结点的后继结点 pnext， pnext = current->next; 
 * 只要 pnext 存在，就执行以下循环：
 * 定义新节点 prev，它是 pnext的后继结点，prev = pnext->next;
 * 把pnext的后继指向current, pnext->next = current;
 * 此时，pnext 实际上已经到了 current 前一位成为新的current，
 * 所以这个时候 current 结点实际上成为新的 pnext，current = pnext;
 * 此时，新的 current 就是 pnext，current = pnext;
 * 而新的 pnext 就是 prev，pnext = prev;
 * 最后将头结点与 current 重新连上即可，L->next = current;
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
	LinkList L; /* 头指针 ?? */
	
	iRet = LinkListInit(&L);
	printf("链表L初始化完毕, LinkListLength(L) = %d\n", LinkListLength(L));
	printf("\n1.遍历操作 \n2.插入操作 \n3.删除操作  \n0.退出 \n请选择你的操作：\n");

	while(opp != '0')
	{
		printf("\n1.遍历操作 \n2.插入操作 \n3.删除操作  \n0.退出 \n请选择你的操作：\n");
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
				printf("在L的表头依次插入10个随机数后：");				
				LinkListTraverse(L, LinkListVisit);
				printf("\n");
				break;
			case 3:
				printf("要删除第几个元素?");
				//scanf("%d" &pos);
				LinkListDelete(&L, 3, &e);
				printf("删除第%d个元素成功,现在链表为:\n", pos);
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
  1.单链表反转
  2.找出单链表的倒数第4个元素
  3.找出单链表的中间元素
  4.删除无头单链表的一个节点
  5.两个不交叉的有序链表的合并
  6.有个二级单链表，其中每个元素都含有一个指向一个单链表的指针。写程序把这个二级链表称一级单链表。
  7.单链表交换任意两个元素（不包括表头）
  8.判断单链表是否有环？如何找到环的"起始"点？如何知道环的长度？
  9.判断两个单链表是否相交
  10.两个单链表相交，计算相交点
  11.用链表模拟大整数加法运算
  12.单链表排序
  13.删除单链表中重复的元素
*/


