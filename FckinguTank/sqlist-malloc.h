#ifndef __SQLIST_MALLOC_H__
#define __SQLIST_MALLOC_H__

/* 线性表的动态分配顺序存储结构 */
typedef int ElemType;
typedef int Status;

#define LIST_INIT_SIZE        100
#define LIST_INCREMENT        20

typedef struct msqlist{
	ElemType *data;
	int      length;
	int      listsize;
}MSqList;



#endif

