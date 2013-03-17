#include <stdio.h>
#include <string.h>
#include "base.h"

int u_strlen(char *str)
{
    char *s = str;

    while(*str != '\0')
        str++;
        
    return (int)(str-s);
}


char *u_strcat(char *dst, char *src)
{
    int i = 0, j = 0;
    char *pdst = dst;
    while(dst[i] != '\0')
        i++;
    while((dst[i] = src[j]) != '\0')
        ;
    return pdst;
}

/* K&R P37 2.8 */
/* 从字符串str中删除字符c */
void squeeze(char *str, int c)
{
    int i, j;

    for(i = 0, j = 0; str[i] != '\0'; i++)
    {
        if(str[i] != c)
            str[j++] = str[i];
    }
    str[j] = '\0';
}

/* K&R P38 2-4 */
/* 将字符串str1中任何与字符串str2中字符匹配的字符都删除 */
void squeeze_ext(char *str1, char *str2)
{
    int i, j, k;
    for(i = k = 0; str1[i] != '\0'; i++)
    {
        for(j = 0; str2[j] != '\0' && str1[i] != str2[j]; j++)
            ;
        if(str2[j] == '\0')
            str1[k++] = str1[i];
    }
    str1[k] = '\0';
}

/* K&R P38 2-5 */
/* 字符串str2中的任一字符在字符串str1中第一次出现的位置 */
int any_match(char *str1, char *str2)
{
    int i, j;
#if 0
    for(i = 0; str1[i] != '\0'; i++)
    {
        for(j = 0; str2[j] != '\0' && str1[i] != str2[j]; j++)
            ;
        if(str2[j] != '\0')
            return i;
    }
#endif
    for(i = 0; str1[i] != '\0'; i++)
        for(j = 0; str2[j] != '\0'; j++)
            if(str1[i] == str2[j])
                return i;

    return -1;
}

/**
 *  K&R P60 4.1
 *  
**/
int strindex(char *str, char *sub)
{
    int i, j, k;

    for(i = 0; str[i] != '\0'; i++)
    {
        for(j=i, k=0; sub[k] != '\0' && str[j] == sub[k]; j++, k++)
            ;
        if(k > 0 && sub[k] == '\0')
            return i;
    }
    return -1;
}
/**
 *  K&R P60 4-1
 *  返回字符串t在s中最右边出现的位置,如果s中不包含t,则返回-1.
**/
int strrindex(char *s, char *t)
{
    int i, j, k, pos;

    pos = -1;
    for(i = 0; s[i] != '\0'; i++)
    {
        for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if(k > 0 && t[k] == '\0')
            pos = i;
    }
    return pos;
}

int strrindex_ext(char *s, char *t)
{
    int i, j, k;
    for(i = strlen(s) - strlen(t); i >= 0; i--)
    {
        for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if(k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int ustring_test(void)
{
    int ret;
    char str[] = "15621869612146512156";
    char str1[] = "adcceoidf5632xcbeckjnuejkdja156";
    char str2[] = "ix56";

    printf("str  = %s\n", str);
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    printf("\n");
    printf("u_strlen(str) = %d\n", u_strlen(str));
    printf("u_strlen(str1) = %d\n", u_strlen(str1));
    printf("u_strlen(str2) = %d\n", u_strlen(str2));
    printf("\n");
    squeeze(str, '6');
    printf("after squeeze(str, '6')\n");
    printf("str  = %s\n", str);
    printf("\n");
    ret = any_match(str1, str2);
    printf("any_match(str1, str2) ret = %d\n", ret);
    printf("\n");
    squeeze_ext(str1, str2);
    printf("after squeeze_ext(str1, str2)\n");
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
    return 0;
}

#if 0
int main(void)
{
    ustring_test();
    return 0;
}
#endif
