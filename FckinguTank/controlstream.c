#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

/**
 *  K&R P47 3.3
 *  �� v[0]<=v[1]<=v[2]<=...<=v[n-1] �в��� x .
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
 *  ͳ�Ƹ������֡��հ׷������������ַ����ֵĴ���
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
 *  ��strת��Ϊ����
**/
int my_atoi(char str[])
{
    int i, n, sign;

    for(i = 0; isspace(str[i]); i++)   /* �����հ׷� */
        ;
    sign = (str[i] == '-') ? -1 : 1;   /* �հ׷���ֻ�迼����һ���ַ��Ƿ�Ϊ'-' */
    if(str[i] == '+' || str[i] == '-') /* �������� */
        i++;
    for(n = 0; isdigit(str[i]); i++)
        n = 10 * n + (str[i] - '0');
    return sign * n;
}

/**
 *  K&R P60 4.2
 *  ��strת��Ϊ��Ӧ��˫���ȸ�����
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
 *  ��չmy_atofʹ�����Դ�������123.45e-6�Ŀ�ѧ��ʾ��
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
 *  �����ַ���str�и����ַ���λ��
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
 *  ���ַ���str1��������a-zһ����ټǷ����ַ���str2����չ
 *  Ϊ�ȼ۵������б�abc..xyz.
**/
void expand(char *str1, char str2[])
{
}

/**
 *  K&R P52 3.6
 *  ������nת��Ϊ�ַ��������浽str��
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
 *  ������nת��Ϊ��bΪ�͵���,����ת��������ַ�����ʽ�������ַ���str��
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
 *  ������nת��Ϊ�ַ��������浽str��,��С���Ϊw.
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
 *  ɾ���ַ���β���Ŀո�����Ʊ���뻻�з�
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

