#include <stdio.h>
#include <string.h>


int CheckPalindrome(char *str, int len)
{
    if(len <= 1)
        return 1;
    else
        return (str[0] == str[len-1] && CheckPalindrome(str+1, len-2));
}

int CheckPalindrome2(char *str, int len)
{
    int i;
    if(len <= 1)
        return 1;
    for(i = 0; i < len / 2 && str[i] == str[len-1-i]; i++)
        ; 
    if(i >= len /2)
        return 1;
    else
        return 0;
}

int IsPalindrome(char *str)
{
    return CheckPalindrome(str, strlen(str));
}

 
int main(void)
{
    char fck[100];
    while(1)
    {
        printf("please input any str:\n");
        scanf("%s", fck);
        printf("IsPalindrome ret = %d\n", IsPalindrome(fck));
        printf("CheckPalindrome2 ret = %d\n", CheckPalindrome2(fck, strlen(fck)));
    }
    return 0;
}


