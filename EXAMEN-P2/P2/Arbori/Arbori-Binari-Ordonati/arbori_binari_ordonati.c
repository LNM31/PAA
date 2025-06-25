#include<stdio.h>
#include<stdlib.h>
typedef struct gg{
    int cheie;
    struct gg *st;
    struct gg *dr;
}nod;

nod *createNod(int cheie)
{
    nod *nou=(nod *)malloc(sizeof(nod));
    if(nou==NULL)
    {
        perror("Error creating node!");
        exit(-1);
    }
    nou->cheie=cheie;
    nou->st=NULL;
    nou->dr=NULL;
    return nou;
}
nod *insert(nod *radacina,int cheie)
{
    if(radacina==NULL)
        return createNod(cheie);
    
    if(cheie < radacina->cheie)
        radacina->st=insert(radacina->st,cheie);
    else
        radacina->dr=insert(radacina->dr,cheie);
    
    return radacina;
}
void preordine(nod *radacina)
{
    if(radacina==NULL)
        return;
    
    printf("%d ",radacina->cheie);
    preordine(radacina->st);
    preordine(radacina->dr);
}
void inordine(nod *radacina)
{
    if(radacina==NULL)
        return;
    
    inordine(radacina->st);
    printf("%d ",radacina->cheie);
    inordine(radacina->dr);
}
void postordine(nod *radacina)
{
    if(radacina==NULL)
        return;
    
    postordine(radacina->st);
    postordine(radacina->dr);
    printf("%d ",radacina->cheie);
}

int main()
{
    nod *radacina=NULL;
    radacina=insert(radacina,4);
    radacina=insert(radacina,5);
    radacina=insert(radacina,3);
    radacina=insert(radacina,1);
    radacina=insert(radacina,2);
    radacina=insert(radacina,7);
    radacina=insert(radacina,6);
    radacina=insert(radacina,9);
    radacina=insert(radacina,8);

    preordine(radacina);
    printf("\n");
    inordine(radacina);
    printf("\n");
    postordine(radacina);
    printf("\n");

    return 0;
}