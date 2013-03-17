#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

/**
 * ˳��� : ����˳��洢�ṹ�����Ա�.
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

