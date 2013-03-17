#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define NUM_PER_LINE     10
#define MAX_NUM          10

void printf_rands(int array[], int len)
{
    int i;
    printf("\n====================array[]====================\n");
    for(i=0; i<len; i++)
        printf((i+1)%NUM_PER_LINE ? "%5d " : "%5d\n", array[i]);
    printf(len % NUM_PER_LINE 
           ? "\n===============================================\n"
           : "===============================================\n");
}

void create_rands(int array[], int min, int max, int num)
{
    srand(time(NULL));

    while(num > 0)
        array[--num] = rand() % (max-min+1) + min;
}

/*========================================================*/

/* 选择 */
void select_sort(int array[], int num)
{
    int i, j, tmp;
    int min;
    for(i=0; i<num-1; i++)  // 选择的次数
    {
        min = i;
//        tmp = array[min];
        for(j=i+1; j<num; j++)  // 找出最小的
        {
            if(array[min] > array[j])
            {
                min = j;
//                tmp = array[j];
            }
        }
        if(min != i)
        {
            tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }
    }
}

/* 堆排序 */
void heap_sort(int array[], int num)
{

}

/*========================================================*/

/* 插入 */
void insert_sort(int array[], int num)
{
    int i, j, tmp;
    for(i=1; i<num; i++)
    {
        tmp = array[i];
        for(j=i-1; j>=0 && array[j]>tmp; j--) // 符合条件的后移
            array[j+1] = array[j];
        array[j+1] = tmp;  // 插入的位置
    }
}
/* 希尔 */
void shell_sort(int array[], int num)
{
    int i, j, gap, tmp;
    gap = num / 2;

    while(gap > 0)
    {
        for(i=gap; i<num; i++)
        {
            j = i - gap;
            while(j >= 0)
            {
                if(array[j] > array[j+gap])
                {
                    tmp = array[j];
                    array[j] = array[j+gap];
                    array[j+gap] = tmp;
                    j = j - gap;
                }
                else
                {
                    j--;
                }
            }
        }
        gap = gap / 2;
    }
}

/**
 *  K&R P51 3.5
**/
void shell_sort_ext(int v[], int n)
{
    int gap, i, j, temp;

    for(gap = n/2; gap > 0; gap /= 2)
    {
        for(i = gap; i < n; i++)
        {
            for(j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

/*========================================================*/

/* 冒泡 */
void bubble_sort(int array[], int num)
{
    int i, j, tmp;
//    printf_rands(array , num);
    for(i=num; i>1; i--)
    {
        for(j=0; j<i-1; j++)
        {
            if(array[j]>array[j+1])
            {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
//        printf("%d\n", i);
//        printf_rands(array , num);
    }
}

/* 快速 */
int quick_partition(int array[], int left, int right)
{
    int tmp = array[left];

    while(left < right)
    {
        while(left < right && array[right] >= tmp)
            right--;
        if(left < right)
            array[left++] = array[right];

        while(left < right && array[left] <= tmp)
            left++;
        if(left < right)
            array[right--] = array[left];
    }
    array[left] = tmp;
    printf("partition1 = %d\n", left);
//    printf_rands(array, MAX_NUM);
    return left;
}
void quick_sort(int array[], int left, int right)
{
    int pivotpos;
    if(left < right)
    {
        pivotpos = quick_partition(array, left, right);
//        printf("partition2 = %d\n", pivotpos);
        quick_sort(array, left, pivotpos-1);
        quick_sort(array, pivotpos+1, right);
    }
}

void swap_v(int v[], int i, int j)
{
    int tmp;
    
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
void printf_v(int array[], int len)
{
    int i;
    for(i=0; i<len; i++)
        printf((i+1)%NUM_PER_LINE ? "%2d " : "%2d\n", array[i]);
}

void q_sort(int v[], int left, int right)
{
    int i, last;
    static int count = 0;

    printf("count = %d\nleft = %d, right = %d\n", 
        count++, left, right);

    if(left >= right)
        return;

    printf("(left + right) / 2 = %d\n", (left + right)/ 2);
    printf("after swap_v(%d, %d):\n", left, (left+right)/2);
    swap_v(v, left, (left + right)/2);

    printf_v(v, 10);

    last = left;
    printf("befor for() last = %d\n", last);
    for(i = left + 1; i <= right; i++)
        if(v[i] < v[left])
            swap_v(v, ++last, i);

    printf("after for() last = %d\n", last);

    swap_v(v, left, last);

    printf_v(v, 10);

    q_sort(v, left, last - 1);
    q_sort(v, last + 1, right);
}

void q_test(void)
{
    int v[] = {3, 2, 4, 1, 8, 7, 6, 5, 0, 9};
    printf(" == before ==\n");
    printf_rands(v, 10);
    q_sort(v, 0, 9);
    printf(" == after ==\n");
    printf_rands(v, 10);
}

/*========================================================*/
void sort_test()
{
    int i, j;
    int array[MAX_NUM];
    int num[MAX_NUM] = {0};
//    printf_rands(num, 10);
    create_rands(array, 0, 100, MAX_NUM);
    printf_rands(array, sizeof(array)/sizeof(int));
#if 0
    for(i=0; i<MAX_NUM; i++)
    {
        for(j=0; j<MAX_NUM; j++)
        {
            if(array[i] == j)
            {
                num[j]++;
                break;
            }
        }
    }
    printf_rands(num, 10);
#endif
    quick_sort(array, 0, MAX_NUM-1);
//    select_sort(array, MAX_NUM);
//    bubble_sort(array, MAX_NUM);
//    shell_sort(array, MAX_NUM);
    printf_rands(array, sizeof(array)/sizeof(int));

}
/*========================================================*/

/* 地精排序 */
void gnome_sort(int v[], int n)
{
    int i = 0;
    int tmp;
    
    while(i < n)
    {
        if(i == 0 || v[i-1] <= v[i)
        {
            i++;
        }
        else
        {
            tmp = v[i];
            v[i] = v[i-1];
            v[--i] = tmp;
        }
    }
}

/*========================================================*/

/* Comb Sort */
void comb_sort(int v[], int n)
{
    float factor = 1.3;
    int i, tmp;
    int g = n;
    int swapped = 1;

    while(g > 1 || swapped)
    {
        g = (g > 1) ? g / factor : g;
        swapped = 0;
        i = 0;
        while(g + i < n)
        {
            if(v[i] > v[g+i])
            {
                tmp = v[i];
                v[i] = v[g+i];
                v[g+i] = tmp;
                swapped = 1;
            }
            i++;
        }
    }

}
/*========================================================*/

int main(void)
{
    q_test();
    return 0;
}

