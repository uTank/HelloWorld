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
 *  七大经典排序
 *  交换式: 冒泡排序、快速排序
 *  选择式: 直接选择排序、堆排序
 *  插入式: 直接插入排序、希尔排序
 *  归并式: 归并排序
**/
