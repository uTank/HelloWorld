#include <stdio.h>
#include "base.h"

unsigned long gcd(unsigned long a, unsigned long b)
{
	unsigned long r;

	if(a < b)
		swap(a, b);

	while((r = a % b) != 0) {
		a = b;
		b = r;
	}

	return b;
}

int my_memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for(su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if((res = *su1 - *su2) != 0)
			break;

	return res;
}

#define UNIT_TEST
#ifdef UNIT_TEST

int main(void)
{
#if 0	
	unsigned long a, b;

	printf("input a :");
	scanf("%ld", &a);
	printf("input b :");
	scanf("%ld", &b);

	printf("gcd(%ld,%ld) = %ld\n", a, b, gcd(a, b));
#endif
	char dst[100];
	char *src = "hello world\n";
	char *tmp = dst;
	int i, count;

	printf("input count : ");
	scanf("%d", &count);
	
	for(i = 0; i < sizeof(dst); i++)
		dst[i] = i;

	while(count) {
		if((*tmp = *src) != 0)
			src++;
		tmp++;
		count--;
	}

	for(i = 0; i < sizeof(dst); i++)
		printf((i+1)%16 ? "%.2x " : "%.2x\n", dst[i]);

	printf("\nmemcmp = %d\n", my_memcmp("aahh", "aaa", 3));
	
	return 0;
}

#endif
