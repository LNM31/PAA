#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50
typedef struct gg{
    int index;
    int raspuns;
    struct gg *st;
    struct gg *dr;
}nod;
int tab1[N],tab2[N];
int size1,size2;

nod *creareNod(int index,int raspuns)
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
void insereaza(nod *radacina,int index,int raspuns,int parinte)
{
    if(radacina==NULL)
        return;
    if(radacina->index==parinte)
    {
        if(raspuns==0 && radacina->st==NULL)
        {
            radacina->st=creareNod(index,raspuns);
        }
        else if(raspuns==1 && radacina->dr==NULL)
        {
            radacina->dr=creareNod(index,raspuns);
        }
    }
    else
    {
        insereaza(radacina->st,index,raspuns,parinte);
        insereaza(radacina->dr,index,raspuns,parinte);
    }
    
}
void citire1(const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    if(fscanf(f,"%d",&size1)!=1)
    {
        perror("size1");
        exit(-1);
    }
    for(int i=0;i<size1;i++)
    {
        if(fscanf(f,"%d",&tab1[i])!=1)
        {
            perror("Error parents");
            exit(-1);
        }
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
    while(fscanf(f,"%d",&tab2[size2])==1)
    {
        size2++;
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file");
        exit(-1);
    }
}
void preordine(nod *radacina,int nivel,int *nivel_max,int afiseaza)
{
    if(radacina==NULL)
        return;
    if(afiseaza) printf("%d ",radacina->index);
    if(nivel_max!=NULL && nivel>*nivel_max) 
        *nivel_max=nivel;
    preordine(radacina->st,nivel+1,nivel_max,afiseaza);
    preordine(radacina->dr,nivel+1,nivel_max,afiseaza);
}
void diagnostic(nod *radacina,int tab[N],int size)
{
    nod *p=radacina;
    for(int i=0;i<size;i++)
    {
        if(tab[i]==0 && p!=NULL)
            p=p->st;
        else if(tab[i]==1 && p!=NULL)
            p=p->dr;
        else if(p==NULL)
        {
            printf("S-a ajuns la un diagnostic\n");
            return;
        }
    }
    int rest=0;
    preordine(p,0,&rest,0);
    printf("Mai sunt %d intrebari pana la diagnostic\n",rest);
}
int main(int argc,char **argv)
{
    if(argc!=3)
    {
        perror("Error arguments");
        exit(-1);
    }
    citire1(argv[1]);
    citire2(argv[2]);

    nod *radacina=creareNod(1,1);
    for(int i=1;i<size1;i++)
    {
        insereaza(radacina,i+1,(i+1)%2,tab1[i]);
    }
    
    diagnostic(radacina,tab2,size2);
    int intrebari_maxime=0;
    preordine(radacina,0,&intrebari_maxime,0);
    printf("%d\n",intrebari_maxime);
    return 0;
}