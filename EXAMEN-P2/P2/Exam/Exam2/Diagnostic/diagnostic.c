#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct gg{
    int index;
    int raspuns;
    struct gg *st;
    struct gg *dr;
}nod;

int tab[40];
int size;

nod *createNod(int index,int raspuns)
{
    nod *nou=(nod *)malloc(sizeof(nod));
    if(nou==NULL)
    {
        perror("Error creating node!");
        exit(-1);
    }
    nou->index=index;
    nou->raspuns=raspuns;
    nou->st=NULL;
    nou->dr=NULL;
    return nou;
}
void insert(nod *radacina,int index,int raspuns,int parinte)
{
    if(radacina==NULL)
        return;
    
    if(radacina->index==parinte)
    {
        if(raspuns==0 && radacina->st==NULL)
        {
            radacina->st=createNod(index,raspuns);
            return;
        }
        else if(raspuns==1 && radacina->dr==NULL)
        {
            radacina->dr=createNod(index,raspuns);
            return;
        }
    }
    else
    {
        insert(radacina->st,index,raspuns,parinte);
        insert(radacina->dr,index,raspuns,parinte);
    }
}
void citire1(nod **radacina,const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    int n=0,aux;
    if(fscanf(f,"%d",&n)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    if(fscanf(f,"%d",&aux)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    *radacina=createNod(1,0);
    for(int i=1;i<n;i++)
    {
        if(fscanf(f,"%d",&aux)!=1)
        {
            perror("Error readin for aux!");
            exit(-1);
        }
        insert(*radacina,i+1,(i+1)%2,aux);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file");
        exit(-1);
    }
}
void citire2(const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    while(fscanf(f,"%d",&tab[size])==1)
    {
        size++;
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file");
        exit(-1);
    }
}
void preordine(nod *radacina,int nivel,int *nivel_maxim,int afiseaza)
{
    if(radacina==NULL)
        return;
    
    if(afiseaza) printf("(%d,%d) ",radacina->index,radacina->raspuns);
    if(nivel_maxim && nivel > *nivel_maxim)
    {
        *nivel_maxim=nivel;
    }

    preordine(radacina->st,nivel + 1,nivel_maxim,afiseaza);
    preordine(radacina->dr,nivel + 1,nivel_maxim,afiseaza);
}
void diagnostic(nod *radacina,int tab[40],int size)
{
    if(radacina==NULL)
        return;

    nod *p=radacina;
    for(int i=0;i<size;i++)
    {
        if(tab[i]==0 && p!=NULL)
            p=p->st;
        else if(tab[i]==1 && p!=NULL)
            p=p->dr;
        else if(p==NULL)
        {
            printf("S-a ajuns la un diagnostic.\n");
            return;
        }
    }
    int rest=0;
    preordine(p,0,&rest,0);
    printf("Mai trebuie puse %d intrebari pana la diagostic\n",rest);
}
int main(int argc,char **argv)
{
    if(argc!=3)
    {
        perror("Error arguments!");
        exit(-1);
    }
    nod *radacina=NULL;
    citire1(&radacina,argv[1]);
    citire2(argv[2]);
    //preordine(radacina,0,NULL,1);
    diagnostic(radacina,tab,size);
    int rest=0;
    preordine(radacina,0,&rest,0);
    printf("%d\n",rest);
    return 0;
}