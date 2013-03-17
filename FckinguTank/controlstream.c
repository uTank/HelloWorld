#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

/**
 *  K&R P47 3.3
 *  在 v[0]<=v[1]<=v[2]<=...<=v[n-1] 中查找 x .
**/
int bin_search(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/**
 *  K&R P48 3.4
 *  统计各个数字、空白符及其他所有字符出现的次数
**/
void char_count(void)
{
    int c, i, nwhite, nother, ndigit[10];

    nwhite = nother = 0;
    for(i = 0; i < 10; i++)
        ndigit[i] = 0;

    while((c = getchar()) != EOF)
    {
        switch(c)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ndigit[c-'0']++;
                break;
            case ' ':
            case '\n':
            case '\t':
                nwhite++;
                break;
            case '#':
                goto end;
            default:
                nother++;
                break;
        }
    }
end:
    printf("digits : \n");
    for(i = 0; i < 10; i++)
        printf("%c = %d\n", i+'0', ndigit[i]);
    printf("\n");
    printf("nwhite space = %d\nnother = %d\n", nwhite, nother);
}

/**
 *  K&R P50 3.5
 *  将str转换为整型
**/
int my_atoi(char str[])
{
    int i, n, sign;

    for(i = 0; isspace(str[i]); i++)   /* 跳过空白符 */
        ;
    sign = (str[i] == '-') ? -1 : 1;   /* 空白符后只需考虑下一个字符是否为'-' */
    if(str[i] == '+' || str[i] == '-') /* 跳过符号 */
        i++;
    for(n = 0; isdigit(str[i]); i++)
        n = 10 * n + (str[i] - '0');
    return sign * n;
}

/**
 *  K&R P60 4.2
 *  将str转换为相应的双精度浮点数
**/
double my_atof(char str[])
{
    int i, sign;
    double val, power;
    
    for(i = 0; isspace(str[i]); i++)
        ;
    sign = (str[i] == '-') ? -1 : 1;
    if(str[i] == '+' || str[i] == '-')
        i++;
    for(val = 0.0; isdigit(str[i]); i++)
        val = 10.0 * val + (str[i] - '0');
    if(str[i] == '.')
        i++;
    for(power = 1.0; isdigit(str[i]); i++)
    {
        val = 10.0 * val + (str[i] - '0');
        power *= 10;
    }

    return val * sign / power;
}

/**
 *  K&R P62 4-2
 *  扩展my_atof使它可以处理形如123.45e-6的科学表示法
**/
double my_atof_ext(char str [])
{
    int i, sign, exp;
    double val, power;
    
    for(i = 0; isspace(str[i]); i++)
        ;
    sign = (str[i] == '-') ? -1 : 1;
    if(str[i] == '+' || str[i] == '-')
        i++;
    for(val = 0.0; isdigit(str[i]); i++)
        val = 10.0 * val + (str[i] - '0');
    if(str[i] == '.')
        i++;
    for(power = 1.0; isdigit(str[i]); i++)
    {
        val = 10.0 * val + (str[i] - '0');
        power *= 10;
    }
    val = sign * val / power;
    
    if(str[i] == 'e' || str[i] == 'E')
    {
        sign = (str[++i] == '-') ? -1 : 1;
        if(str[i] == '+' || str[i] == '-')
            i++;
        for(exp = 0; isdigit(str[i]); i++)
            exp = 10 * exp + (str[i] - '0');
        if(sign == 1)
            while(exp-- > 0)
                val *= 10;
        else
            while(exp-- > 0)
                val /= 10;
    }

    return val;
}

/**
 *  K&R P51 3.5
 *  倒置字符串str中各个字符的位置
**/
char *reverse(char str[])
{
    int c, i, j;
    for(i = 0, j = strlen(str)-1; i < j; i++, j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
    return str;
}

/**
 *  K&R P52 3-3
 *  将字符串str1中类似于a-z一类的速记符在字符串str2中扩展
 *  为等价的完整列表abc..xyz.
**/
void expand(char *str1, char str2[])
{
}

/**
 *  K&R P52 3.6
 *  将整型n转换为字符串并保存到str中
**/
char *my_itoa(int n, char str[])
{
    int i = 0, sign;

    if((sign = n) < 0)
        n = -n;

    do{
        str[i++] = n % 10 + '0';
    }while((n /= 10) > 0);

    if(sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    return reverse(str);

//    return str;
}

/**
 *  K&R P53 3-5
 *  将整型n转换为以b为低的数,并将转换结果以字符的形式保存在字符串str中
**/
char *itob(int n, char str[], int b)
{
    int i = 0, j, sign;
    if((sign = n) < 0)
        n = -n;
    do{
        j = n % b;
        str[i++] = (j < 10) ? j + '0' : j + 'a' - 10;
    }while((n /= b) > 0);

    if(sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    return reverse(str);

//    return str;
}
/**
 *  K&R P53 3-6
 *  将整型n转换为字符串并保存到str中,最小宽度为w.
**/
char *itoa_ext(int n, char str[], int w)
{
    int i = 0, sign;
    if((sign = n) < 0)
        n = -n;
    do{
        str[i++] = n % 10 + '0';
    }while((n /= 10) > 0);
    if(sign < 0)
        str[i++] = '-';

    while(i < w)
        str[i++] = ' ';
    str[i] = '\0';

    return reverse(str);

//    return str;
}

/**
 *  K&R P53 3.7
 *  删除字符串尾部的空格符、制表符与换行符
**/
int trim(char str[])
{
    int n;
    for(n = strlen(str)-1; n >= 0; n--)
        if(str[n] != ' ' && str[n] != '\t' && str[n] != '\t')
            break;
    str[n+1] = '\0';

    return n;
}

void my_atoif_test(void)
{
    char str[30];
//    int i = 0;
    printf(" == my_atoif_test ==\n");
    printf("input any char : \n");
//    while(i < 20)
//    {
        scanf("%s", str);
//    }
    printf("atoi(str) = %d\n", atoi(str));
    printf("atof(str) = %g\n", atof(str));
    printf("my_atoi(str) = %d\n", my_atoi(str));
    printf("my_atof(str) = %g\n", my_atof(str));
}

void itob_test(void)
{
    int n, b;
    char str[20];
    printf(" == itob_test ==\n");
    printf("input i : ");
    scanf("%d", &n);
    printf("input b : ");
    scanf("%d", &b);
    printf("itob(%d, str, %d) = %s\n", n, b, itob(n, str, b));
}

void ctrlstream_test(int sel)
{
    switch(sel)
    {
        case 1:
            my_atoif_test();
            break;
        case 2:
            itob_test();
            break;
        case 3:
            break;
        default:
            break;
    }
}

int main(void)
{
//    char_count();
    ctrlstream_test(1);
    return 0;
}

