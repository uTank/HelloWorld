#include <stdio.h>

#define MAXSIZE            (10)

void swap_array(int *a, int i, int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void display_array(int *a, int l)
{
	int i;
	for(i = 0; i < l; i++)
		printf(i+1 == l ? "%d\n" : "%d ", a[i]);
}
/*
 * 让每一个关键字都和它后面的每一个关键字比较,如果大则交换,
 * 这样第一位置的关键字在一次循环后一定变成最小值
 */
void BubbleSort0(int *iArray, int iLen)
{
	int i, j;

	for(i = 0; i < iLen - 1; i++)
	{
		for(j = i + 1; j < iLen; j++)
		{
			if(iArray[i] > iArray[j])
			{
				swap_array(iArray, i, j);
			}
			printf("  j = %d: ", j);
			display_array(iArray, iLen);
		}
		printf("i = %d: ", i);
		display_array(iArray, iLen);
	}
}


/* 每次较小的都上浮 */
void BubbleSort1(int *iArray, int iLen)
{
	int i, j;

	for(i = 0; i < iLen - 1; i++)
	{
		for(j = iLen - 2; j >= i; j--) /* 从后向前两两比较 */
		{
			if(iArray[j] > iArray[j+1]) /* 若前者大于后者则交换 */
			{
				swap_array(iArray, j, j+1);
			}
			printf("  j = %d: ", j);
			display_array(iArray, iLen);

		}
		printf("i = %d: ", i);
		display_array(iArray, iLen);
	}
}

void BubbleSort2(int *iArray, int iLen)
{
	int i, j;
	int flag = 1;
	
	for(i = 0; i < iLen - 1 && flag == 1; i++)
	{
		flag = 0;
		for(j = iLen - 2; j >= i; j--) /* 从后向前两两比较 */
		{
			if(iArray[j] > iArray[j+1]) /* 若前者大于后者则交换 */
			{
				swap_array(iArray, j, j+1);
				flag = 1;
			}
			printf("  j = %d: ", j);
			display_array(iArray, iLen);

		}
		printf("i = %d: ", i);
		display_array(iArray, iLen);
	}
}


int main(void)
{
	int array[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	printf("start: ");
	display_array(array, 9);
	
	BubbleSort2(array, 9);
	
	printf("end: ");
	display_array(array, 9);
	return 0;
}
