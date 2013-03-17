#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

/**
 * ˳��� : ����˳��洢�ṹ�����Ա�.
**/

void SqListInit(SqList *L)
{
     L->length = 0;
}

Status SqListEmpty(SqList L)
{
     return (L.length == 0);
}

/**
 * �����㷨��˼·��
 * �������λ�ò������׳��쳣��
 * ������Ա��ȴ��ڵ������鳤�ȣ����׳��쳣��̬����������
 * �����һ��Ԫ�ؿ�ʼ��ǰ��������i��λ�ã��ֱ����Ƕ�����ƶ�һ��λ�ã�
 * ��Ҫ����Ԫ������λ��i����
 * ����1
**/
Status SqListInsert(SqList *L, int i, ElemType e)
{
     int k;

     if(L->length == MAX_LIST_SIZE)
          return -1;

     if(i < 1 || i > L->length + 1)
          return -1;

     if(i <= L->length) /* ��������λ�ò��ڱ�β */
     {
          for(k = L->length - 1; k >= i - 1; k--)
               L->data[k+1] = L->data[k];
     }
     L->data[i-1] = e;
     L->length++;

     return 0;
}


/**
 * ɾ���㷨��˼·��
 * ���ɾ��λ�ò������׳��쳣��
 * ȡ��ɾ��Ԫ�أ�
 * ��ɾ��Ԫ��λ�ÿ�ʼ���������һ��Ԫ��λ�ã��ֱ����Ƕ���ǰ�ƶ�һ��λ�ã�
 * ����1��
**/
Status SqListDelete(SqList *L, int i, ElemType *e)
{
     int k;

     if(L->length == 0)
          return -1;
     if(i < 1 || i > L->length)
          return -1;

     *e = L->data[i-1];
     if(i < L->length) /* ɾ�������ݲ��ڱ�β */
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

/* ɾ��A�г���B��Ԫ�� */
void SqListDelElem(SqList *A, SqList B)
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

/* ˳���A��˳���B��Ԫ�ض��Ƿǵݼ�����, ��A��B�ϲ���C, C��Ԫ��Ҳ�Ƿǵݼ����� */
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
     printf("��ʼ���ɹ���L.length = %d\n", L.length);
     printf("\n1.�������Ա�\n2.���Ա�ֵ\n3.���Ա����\n0.�˳�\n��ѡ����Ĳ���:\n");
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

