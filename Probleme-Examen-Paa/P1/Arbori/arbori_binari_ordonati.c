#include<stdio.h>
#include<stdlib.h>
typedef struct gg{
    int cheie;
    struct gg *st;
    struct gg *dr;
}nod;

nod *creareNod(int cheie)
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

nod *adauga(nod *radacina,int x)
{
    if(radacina==NULL)
    {
        radacina = creareNod(x);
        return radacina;
    }
    
    if(x<radacina->cheie)
        radacina->st = adauga(radacina->st,x);
    else
        radacina->dr = adauga(radacina->dr,x);
    
    return radacina;
}

void preordine(nod *radacina,int afiseaza)
{
    if(radacina==NULL)
        return;
    if(afiseaza) printf("%d ",radacina->cheie);
    preordine(radacina->st,afiseaza);
    preordine(radacina->dr,afiseaza);
}

void inordine(nod *radacina,int nivel,int *inaltime,int afiseaza)
{
    if(radacina==NULL)
        return;
    if(nivel>*inaltime) *inaltime=nivel;
    inordine(radacina->st,nivel+1,inaltime,afiseaza);
    if(afiseaza) printf("%d ",radacina->cheie);
    inordine(radacina->dr,nivel+1,inaltime,afiseaza);
}
int main()
{
    nod *radacina=NULL;
    radacina=adauga(radacina,4);
    radacina=adauga(radacina,5);
    radacina=adauga(radacina,3);
    radacina=adauga(radacina,1);
    radacina=adauga(radacina,2);
    radacina=adauga(radacina,7);
    radacina=adauga(radacina,6);
    radacina=adauga(radacina,9);
    radacina=adauga(radacina,8);

    preordine(radacina,1);

    int inaltime=0;
    inordine(radacina,0,&inaltime,0);
    printf("\nInaltime %d\n",inaltime);
    return 0;
}