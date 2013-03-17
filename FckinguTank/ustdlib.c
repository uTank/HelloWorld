#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* - - */
int u_atoi(const char *str)
{
    int i = 0;
    int flag = 1;
    while(isspace(*str))
        str++;
    if(*str != '+' && *str != '-' && !isdigit(*str))
        return 0;
    if(*str == '+' || *str == '-')
    {
        flag = (*str == '+' ? 1 : -1);
        if(!isdigit(*++str))
            return 0;
    }
    
    while(isdigit(*str))
        i = i * 10 + *str++ - '0';

    return i*flag;
}

void printf_libmacro(void)
{
    printf(" EXIT_FAILURE = %d\n", EXIT_FAILURE);
    printf(" EXIT_SUCCESS = %d\n", EXIT_SUCCESS);
    printf(" MB_CUR_MAX   = %d\n", MB_CUR_MAX);
    printf(" RAND_MAX     = %d\n", RAND_MAX);
}

int main(void)
{
    printf(" %d\n", atoi("  +000309afcc 3d"));
    printf(" isdigit ret = %d\n", isdigit('a'));
    printf(" %d, %d\n", u_atoi("00123"), 3*u_atoi("00-124"));
    printf_libmacro();
    return 0;
}
