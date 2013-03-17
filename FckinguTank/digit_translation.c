#include <stdio.h>

void translation_A(int N);
void translation_B(int N);
void translation_C(int N);



char *data_1[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
	"ten", "eleven", "twelve", "thirteen", "forteen", "fifteen", "sixteen", "seventeen",
	"eighteen", "ninteen"};
char *data_2[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninty"};

void translation_A(int N)
{
	int a;

	if(N == 0)
	{
		printf("Zero\n");
		return;
	}
	a = N / 1000;
	if(a != 0)
	{
		translation_B(a);
		printf("thousand ");
	}
	a = N % 1000;
	if(a != 0)
	{
		translation_B(a);
	}
}

void translation_B(int N)
{
	int b;
	b = N / 100;
	if(b != 0)
	{
		translation_C(b);
		printf("hundred ");
	}
	b = N % 100;
	if(b != 0)
	{
		translation_C(b);
	}
}
void translation_C(int N)
{
	int c;

	if(N < 20)
	{
		printf("%s", data_1[N-1]);
	}
	else
	{
		c = N / 10;
		printf("%s ", data_2[c-2]);
		c = N % 10;
		if(c != 0)
		{
			printf("%s ", data_1[c-1]);
		}
	}
}

int main(void)
{
	int N;
	printf("Please input from 0~999999\n");
	scanf("%d", &N);
	translation_A(N);
	return 0;
}

