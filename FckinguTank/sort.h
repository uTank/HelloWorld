#ifndef U_SORT_H
#define U_SORT_H

void printf_rands(int array[], int len);
void create_rands(int array[], int min, int max, int num);

void select_sort(int array[], int num);

void insert_sort(int array[], int num);

void bubble_sort(int array[], int num);

int quick_partition(int array[], int left, int right);
void quick_sort(int array[], int left, int right);


void sort_test(void);

#endif /* U_SORT_H */

/**
 *  �ߴ󾭵�����
 *  ����ʽ: ð�����򡢿�������
 *  ѡ��ʽ: ֱ��ѡ�����򡢶�����
 *  ����ʽ: ֱ�Ӳ�������ϣ������
 *  �鲢ʽ: �鲢����
**/
