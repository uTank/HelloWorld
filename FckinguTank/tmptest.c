#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "base.h"

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

/* */
uint func(uint i, int m, int n)
{
    return (i>>(m+1-n) & ~(~0<<n));
}

void func_test(void)
{
    int n;
    uint num;

    printf("Enter a hex number : ");
    scanf("%x", &num);
    printf("Enter left / right : ");
    scanf("%d", &n);

    printf("%x rotate_left %d is : %8x\n", num, n, rotate_left(num, n));
    printf("%x rotate_right %d is : %8x\n", num, n, rotate_right(num, n));

    printf("func(%x, %d, %d) is : %8x\n", num, n+5, n, func(num, n+5, n));    

    int a, b, c;
    a = 8;
    b = 9;
    printf("%d\n", a >> 1 + b >> 1);
    a = 1;
    printf("%d\n", a & ~a);
    a = 2;
    b = 1;
    c = 0;
    printf("%d\n", ~a & b ^ c);
    a = 7;
    b = 8;
    c = 9;
    printf("%d\n", a ^ b);
    printf("%d\n", b & c);
    printf("%d\n", a ^ b & c);
}

int main(int argc, char *argv[])
{
    int i;
    char str[] = "mommove can be very usefull......";
    char tok[] = "- This , a , ohal mstrting .";
    char *pch;
    
    memmove(str+20, str+15, 11);
    puts(str);
    printf("argc = %d\n", argc);
    for(i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    printf("Splittiing string \"%s\" into tokens:\n", tok);
    pch = strtok(str, " ,.-");
    while(pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, " ,.-");
    }
    return 0;
}

