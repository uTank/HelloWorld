#include <stdio.h>
#include <string.h>

int u_strindex(char *str, char *sub, int n)
{
    int i, j, k;
  int str_len = strlen(str);
  int sub_len = strlen(sub);
//    int str_len = 0, sub_len = 0;

#if 0
    while(*str++)
        str_len++;
    while(*sub++)
        sub_len++;
#endif
    printf("str_len = %d\n", str_len);
    printf("sub_len = %d\n", sub_len);
    
    for(i = 0; i <= str_len - sub_len; i++)
    {
        for(k = i, j = 0; j < sub_len && str[k] == sub[j]; k++, j++)
            ;
//        printf("k = %d, j = %d\n", k, j);
        if(j >= sub_len)
            return i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int i ;

#if 1
    printf("argc = %d\n", argc);
    for(i=0; i<argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
#endif

    i = u_strindex(argv[1], argv[2], 0);
    printf("index = %d\n", i);

//    i = u_strindex(p1, p2, 0);
//    printf("index = %d\n", i);
    
    return 0;
}


