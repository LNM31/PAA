#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
void citire(TTree* a, char* str)
{
    FILE* f = fopen(str, "r");
    if (f == NULL)
    {
        perror(NULL);
        exit(-1);
    }
    int b, c;
    while (fscanf(f, "%d %d", &b, &c) == 2)
    {
        *a = InsertNode(*a, c, b);
    }
    if (fclose(f) != 0)
    {
        perror("eroare inchidere");
        exit(-2);
    }
}
int main()
{
    TTree a = {0,0};
    a=InitTree(a);
    citire(&a, "in.txt");
    printArray(a);
    printf("preordine: ");
    preordine(a, getRoot(a));
    printf("\ninordine: ");
    inordine(a, getRoot(a));
    printf("\npostordine: ");
    postordine(a, getRoot(a));
    printf("\n");
    deleteNode(a, 2);
    printf("dsafas");
    //deleteNode(a, 5);
    return 0;
}