#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Item;

#define key(A)           (A)
#define less(A, B)       (key(A) < key(B))
#define more(A, B)       (key(A) > key(B))
#define exch(A, B)       {Item t = A; A = B; B = t;}
#define lessexch(A, B)   if(less(A,B)) exch(A, B)
#define moreexch(A, B)   if(more(A,B)) exch(A, B)

void insert_sort(Item a[], int l, int r)
{
    int i, j;
    for(i = l+1; i <= r; i++)
        for(j = i; j > l; j--)
            lessexch(a[j-1], a[j]);
}

int main(int argc, char *argv[])
{
    int i, N = atoi(argv[1]), sw = atoi(argv[2]);
    int *a = malloc(N*sizeof(int));

    srand(time(NULL));
    if(sw)
        for(i = 0; i < N; i++)
            a[i] = 1000*(1.0*rand()/RAND_MAX);
    else
        while(scanf("%d", &a[N]) == 1) 
            N++;
            
    for(i = 0; i < N; i++)
        printf("%3d ", a[i]);
    printf("\n\n");

    insert_sort(a, 0, N-1);

    for(i = 0; i < N; i++)
        printf("%3d ", a[i]);
    printf("\n");
    return 0;
}

