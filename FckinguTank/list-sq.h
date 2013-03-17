#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

/**
 * 顺序表 : 采用顺序存储结构的线性表.
**/

void SqListInit(SqList *L);
Status SqListEmpty(SqList L);
Status SqListInsert(SqList *L, int i, ElemType e);
Status SqListDelete(SqList *L, int i, ElemType *e);
Status SqListGetElem(SqList L, int i, ElemType *e);
int SqListLocateElem(SqList L, ElemType e);
int SqListLength(SqList L);
void SqListClear(SqList *L);

#endif

