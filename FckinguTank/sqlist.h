#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

/* æ≤Ã¨∑÷≈‰À≥–Ú¥Ê¥¢Ω·ππ */
#define MAX_LIST_SIZE     100
typedef int ElemType;
typedef int Status;

typedef struct sqlist{
     ElemType data[MAX_LIST_SIZE];
     int length;
}SqList;


void SqListInit(SqList *L);
Status SqListEmpty(SqList L);
Status SqListInsert(SqList *L, int i, ElemType e);
Status SqListDelete(SqList *L, int i, ElemType *e);
Status SqListGetElem(SqList L, int i, ElemType *e);
int SqListLocateElem(SqList L, ElemType e);
int SqListLength(SqList L);
void SqListClear(SqList *L);

#endif



