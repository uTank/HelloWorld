#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "base.h"

#undef debug_msg
#define debug_msg
#define MAXOP     100
#define NUMBER    '0'

#define MAXVAL    100
int sp = 0;
double val[MAXVAL];

#define BUFSIZE   100
char buf[BUFSIZE];
int bufp = 0;

void push(double f);
double pop(void);
int getop(char s[]);
int getch(void);
void ungetch(int);


int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF)
    {
        debug_msg("type = %c\n", type);
        switch(type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error : zero divisor\n");
                break;
            case '\n':
                printf("\n ret = %.8g\n", pop());
                break;
            default:
                printf("error: unknow command %s\n", s);
                break;
        }
    }
    
    return 0;
}

void push(double f)
{
    if(sp < MAXVAL)
    {
        val[sp++] = f;
        debug_msg("push(f) = %g\n", f);
        debug_msg("sp = %d\n", sp);
    }
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if(sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[])
{
    int i, c;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if(!isdigit(c) && c != '.')
        return c;
    i = 0;
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()))
            ;
    if(c == '.')
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if(c != EOF)
        ungetch(c);

    return NUMBER;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#if 0
// The reverse Polish notation
while (next operator or operand is not end-of-file indicator)
    if(number)
        push it
    else if(operator)
        pop operands
        do  operation
        push result
    else if (newline)
        pop and print top of stack
    else
        error
#endif

