#include<stdio.h>
#include<stdlib.h>
typedef struct gg {
    int cheie;
    struct gg* st;
    struct gg* dr;
}ab;
ab* insert(ab* r, int x)
{
    if (r != NULL)
    {
        if (x < r->cheie)
        {
            r->st = insert(r->st, x);
        }
        else
        {
            r->dr = insert(r->dr, x);
        }
    }
    else
    {
        r = (ab*)malloc(sizeof(ab));
        if (r == NULL)
        {
            perror(NULL);
            exit(-1);
        }
        r->cheie = x;
        r->st = NULL;
        r->dr = NULL;
    }
    return r;
}
void preordine(ab* r)
{
    if (r != NULL)
    {
        printf("%d ", r->cheie);
        preordine(r->st);
        preordine(r->dr);
    }
}
void inordine(ab* r)
{
    if (r != NULL)
    {
        inordine(r->st);
        printf("%d ", r->cheie);
        inordine(r->dr);
    }
}
void postordine(ab* r)
{
    if (r != NULL)
    {
        postordine(r->st);
        postordine(r->dr);
        printf("%d ", r->cheie);
    }
}
void free_arbore(ab* r)
{
    if (r != NULL)
    {
        free_arbore(r->st);
        free_arbore(r->dr);
        free(r);
    }
}
int main()
{
    printf("arbori\n");
    ab* r = NULL;
    r = insert(r, 10);
    r = insert(r, 5);
    r = insert(r, 15);
    r = insert(r, 3);
    r = insert(r, 7);
    r = insert(r, 20);
    preordine(r);
    printf("\n");
    inordine(r);
    printf("\n");
    postordine(r);
    printf("\n");
    free_arbore(r);
    printf("\ndsafasw\n");
    return 0;
}
// post: E K P L F G B  H C  I M N O J D  A
// inord: E B K F P L G  A  H C I D M J N O  