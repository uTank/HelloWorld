#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ustring.h"

#define MAXLEN       1000

char pattern[] = "ould";
#if 0
int getline(char s[], int lim)
{
    int c, i;
    
    for(i=0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if(c == '\n')
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';

    return i;
}
#endif

int getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if(c == '\n')
        s[i++] = '\0';

    return i;
}

#if 0
int main(int argc, char *argv[])
{
    char line[MAXLEN];
    int found = 0;

    while(getline(line, MAXLEN) > 0)
    {
        if(strindex(line, pattern) >= 0)
        {
            printf("%s\n", line);
            found++;
        }
    }
    printf("found = %d\n", found);
    return 0;
}
#endif

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

int main(void)
{
    double sum;
    char line[MAXLEN];

    sum = 0;
    while(getline(line, MAXLEN) > 0)
        printf("\t%g\n", sum += my_atof(line));

    return 0;
    
}
