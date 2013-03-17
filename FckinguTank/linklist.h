#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

typedef int ElemType;
typedef int Status;


typedef struct LNode{
     ElemType data;
     struct LNode *next;
}ListNode, *LinkList;


int LinkListInit(LinkList *L);
void LinkListDestroy(LinkList *L);
void LinkListClear(LinkList L);
Status LinkListEmpty(LinkList L);
int LinkListLength(LinkList L);
Status LinkListGetElem(LinkList L, int i, ElemType *e);
int LinkListLocateElemExt(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));
Status LinkListPriorElem(LinkList L, ElemType cur, ElemType *pre);
Status LinkListNextElem(LinkList L, ElemType cur, ElemType *next);
Status LinkListInsert(LinkList *L, int i, ElemType e);
Status LinkListDelete(LinkList *L, int i, ElemType *e);
void LinkListTraverse(LinkList L, void (*vi)(ElemType));

#endif

