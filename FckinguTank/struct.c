#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>

#if 0
static unsigned long next_rand = 1;

/* RAND_MAX assumed to be 32767 */
int my_rand(void) 
{
    next_rand = next_rand * 1103515245 + 12345;
    return ((unsigned)(next_rand/65536) % 32768);
}

void my_srand(unsigned seed) 
{
    next_rand = seed;
}

/*
int main(int argc, char *argv[])
{
    time_t tmp;
    tmp = time(NULL);
    time_t fck = 0;
	printf("the current time is %s", ctime(&fck));
	printf("the current time is %ld\n", tmp);

    printf("Hello World\n");
    printf("RAND_MAX = %d\n", RAND_MAX);
    return 0;
}
*/
#endif

#define min(a, b)    ((a) < (b) ? (a) : (b))
#define max(a, b)    ((a) > (b) ? (a) : (b))

struct point{
    int x;
    int y;
};

struct rect{
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y)
{
    struct point tmp;

    tmp.x = x;
    tmp.y = y;

    return tmp;
}

struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;

    return p1;
}

int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

struct rect canonrect(struct rect r)
{
    struct rect tmp;

    tmp.pt1.x = min(r.pt1.x, r.pt2.x);
    tmp.pt1.y = min(r.pt1.y, r.pt2.y);
    tmp.pt2.x = max(r.pt1.x, r.pt2.x);
    tmp.pt2.y = max(r.pt1.y, r.pt2.y);

    return tmp;
}

int main(void)
{
    struct point pt;
    struct point middle;
    struct rect screen;

    screen.pt1 = makepoint(2, 2);
    screen.pt2 = makepoint(20, 20);

    middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
                       (screen.pt1.y + screen.pt2.y)/2);
}
#if 0
int main(void)
{
    int c;
    printf("FILENAME_MAX = %d\n", FILENAME_MAX);
    printf("FOPEN_MAX = %d\n", FOPEN_MAX);
    printf("EOF = %d\n", EOF);
    while((c = getchar()) != EOF)
        putchar(tolower(c));
    return 0;
}
#endif
