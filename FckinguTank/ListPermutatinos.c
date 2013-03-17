#include <stdio.h>
#include <string.h>

static void ExchangeCharacters(char *str, int p1, int p2)
{
    char tmp;
    tmp = str[p1];
    str[p1] = str[p2];
    str[p2] = tmp;
}

static void RecursivePermute(char *str, int k)
{
    int i;
    static int fck = 0;
    static int f1 = 0, f2 = 0, f3 = 0;
    printf("Being Call iCount = %d\n", fck++);
//    printf("strlen(str) = %d\n", strlen(str));
    if(k == strlen(str))
        printf("======================================== %s\n", str);
    else
    {
        for(i = k; i < strlen(str); i++)
        {
            printf("i = %d, k = %d\n", i, k);
            printf("Enter for : %s\n", str);
            ExchangeCharacters(str, k, i);
            printf("After ExchangeCharacters1(%d) : %s\n", f1++, str);
            RecursivePermute(str, k+1);
            printf("After RecursivePermute(%d)/(%d) : %s\n", k+1, f2++, str);
            ExchangeCharacters(str, k, i);
            printf("After ExchangeCharacters2(%d) : %s\n", f3++, str);
        }
    }
}

static void ListPermutations(char *str)
{
    RecursivePermute(str, 0);
}

int main(void)
{
//    ListPermutations("abc");
    char p[100];
    printf("please input string :\n");
    scanf("%s", p);
    printf("\n\n\n");
    RecursivePermute(p, 0);
    return 0;
}
