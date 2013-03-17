#include <stdio.h>
#include "base.h"
 
/**
 *  K&R P39 2.9
 *  返回x中从右边数第p位开始向右数n位的字段
 *  x = 0xFFAACCDD , p = 11, n = 4
 *  1111,1111,1010,1010,1100,1100,1101,1101
 *                           ^^^^
 *  ret = 1100
**/
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
 
/**
 *  K&R P40 2-6
 *  将x中从第p位开始的n个位设置为y中最右边的n位的值,x的其余各位保持不变 
 *  x = 0xabcdefab , p = 20 , n = 10 , y = 0xabcdefab
 *  1010,1011,1100,1101,1110,1111,1010,1011 
 *               ^ ^^^^,^^^^,^
 *               1,1101,0101,1
 *  1010,1011,1101,1101,0101,1111,1010,1011
 *  ret : 0xabdd5fab
**/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
#if 0
    debug_msg("~(~(~0 << (p+1)) & (~0 << (p+1-n))) = %.8x\n", 
        ~(~(~0 << (p+1)) & (~0 << (p+1-n))));
    debug_msg("(y & ~(~0 << n)) << (p+1-n) = %.8x\n",
        (y & ~(~0 << n)) << (p+1-n));

    return ~(~(~0 << (p+1)) & (~0 << (p+1-n))) & x | ((y & ~(~0 << n)) << (p+1-n));
#endif
    return (x & ~(~(~0 << n) << (p+1-n))) | ((y & ~(~0 << n)) << (p+1-n));
}

/**
 *  K&R P40 2-7
 *  将x中从第p位开始的n个位求反,x的其余各位保持不变
 *  x = 0xabcdefab , p = 20, n = 10
 *  1010,1011,1100,1101,1110,1111,1010,1011
 *               ^ ^^^^,^^^^,^
 *  0000,0000,0001,1111,1111,1000,0000,0000
 *
 *  1010,1011,1101,0010,0001,0111,1010,1011
 *  ret : 0xabd217ab
**/
unsigned invert(unsigned x, int p, int n)
{
//    return x ^ (~(~0 << (p+1)) & (~0 << (p+1-n)));
    return x ^ (~(~0 << n) << (p+1-n));
}

ushort swap_bytes(ushort s)
{
    return (s>>8)|(s<<8);
}

uint rotate_left(uint i, int n)
{
    return (i<<n)|(i>>(32-n));
}

uint rotate_right(uint i, int n)
{
    return (i>>n)|(i<<(32-n));
}

/**
 *  K&R P40 2.10
 *  统计x中值为1的二进制位数
**/
int bit_count(unsigned x)
{
    int count;
    for(count = 0; x != 0; x >>= 1)
        if(x & 1)
            count++;
    return count;
}
int bit_count_ext(unsigned x)
{
    int count = 0;
    while(x)
    {
        count++;
        x &= (x - 1);
    }
    return count;
}


void bitoperator_test(void)
{
    uint x, y;
    int p, n;
    int num;
    printf("x : ");
    scanf("%x", &x);
    printf("y : ");
    scanf("%x", &y);
    printf("p : ");
    scanf("%d", &p);
    printf("n : ");
    scanf("%d", &n);
    printf("invert(%x, %d, %d) = 0x%.8x\n", x, p, n, invert(x, p, n));
    printf("setbit(%x, %d, %d, %x) = 0x%.8x\n", x, p, n, y, setbits(x, p, n, y));

    printf("getbits(%x, %d, %d) = 0x%.8x\n", x, p, n, getbits(x, p, n));

    printf("input num : ");
    scanf("%d", &num);
    printf("bit_count(%d) = %d\n", num, bit_count(num));
    printf("bit_count_ext(%d) = %d\n", num, bit_count_ext(num));
}


int main(void)
{

    bitoperator_test();

    
    return 0;
}

