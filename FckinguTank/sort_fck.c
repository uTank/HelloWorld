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
 * ��ÿһ���ؼ��ֶ����������ÿһ���ؼ��ֱȽ�,������򽻻�,
 * ������һλ�õĹؼ�����һ��ѭ����һ�������Сֵ
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


/* ÿ�ν�С�Ķ��ϸ� */
void BubbleSort1(int *iArray, int iLen)
{
	int i, j;

	for(i = 0; i < iLen - 1; i++)
	{
		for(j = iLen - 2; j >= i; j--) /* �Ӻ���ǰ�����Ƚ� */
		{
			if(iArray[j] > iArray[j+1]) /* ��ǰ�ߴ��ں����򽻻� */
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
		for(j = iLen - 2; j >= i; j--) /* �Ӻ���ǰ�����Ƚ� */
		{
			if(iArray[j] > iArray[j+1]) /* ��ǰ�ߴ��ں����򽻻� */
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
