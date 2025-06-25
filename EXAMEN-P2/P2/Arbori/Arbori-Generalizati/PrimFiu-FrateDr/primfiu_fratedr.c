#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 128
typedef struct {
    int cheie;
    int prim_fiu;
    int frade_dr;
}nod;

typedef struct{
    int size;
    nod nodes[N];
}Tree;

Tree init(Tree a)
{
    a.size=0;
    for(int i=0;i<N;i++)
    {
        a.nodes[i].cheie=0;
        a.nodes[i].prim_fiu=0;
        a.nodes[i].frade_dr=0;
    }
    return a;
}
Tree insert(Tree a,int cheie,int parinte)
{
    a.size++;
    a.nodes[a.size].cheie=cheie;
    
    if(parinte==0)
    {
        return a;
    }
    if(a.nodes[parinte].prim_fiu==0)
    {
        a.nodes[parinte].prim_fiu=a.size;
    }
    else
    {
        int copil=a.nodes[parinte].prim_fiu;
        while(a.nodes[copil].frade_dr!=0)
        {
            copil=a.nodes[copil].frade_dr;
        }
        a.nodes[copil].frade_dr=a.size;
    }
    return a;
}
void display(Tree a)
{
    printf("Index:    ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",i);
    }
    printf("\nCheie:    ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].cheie);
    }
    printf("\nPrim-Fiu: ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].prim_fiu);
    }
    printf("\ncopil-Dr: ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].frade_dr);
    }
    printf("\n");
}
void citire(Tree *a,const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    int cheie,parinte;
    while(fscanf(f,"%d %d",&cheie,&parinte)==2)
    {
        *a=insert(*a,cheie,parinte);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
}
int primFiu(Tree a,int refnode)
{
    if(refnode<=0 || refnode>=a.size)
        return 0;
    
    return a.nodes[refnode].prim_fiu;
}
int frateDr(Tree a,int refnode)
{
    if(refnode<=0 || refnode>=a.size)
        return 0;
    
    return a.nodes[refnode].frade_dr;
}
int parinte(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return 0;
    
    int copil=0;
    for(int i=1;i<=a.size;i++)
    {
        copil=a.nodes[i].prim_fiu;
        while(copil!=0)
        {
            if(refnode==copil)
                return i;
            
            copil=a.nodes[copil].frade_dr;
        }
    }
    return 0;
}
void preordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;

    printf("%d ",a.nodes[refnode].cheie);
    
    int copil=a.nodes[refnode].prim_fiu;
    preordine(a,copil);
    while((copil=a.nodes[copil].frade_dr)!=0)
    {
        preordine(a,copil);
    }
}
void inordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;

    
    int copil=a.nodes[refnode].prim_fiu;
    inordine(a,copil);

    printf("%d ",a.nodes[refnode].cheie);
    
    while((copil=a.nodes[copil].frade_dr)!=0)
    {
        inordine(a,copil);
    }
}
void postordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;
    
    int copil=a.nodes[refnode].prim_fiu;
    postordine(a,copil);
    while((copil=a.nodes[copil].frade_dr)!=0)
    {
        postordine(a,copil);
    }
    printf("%d ",a.nodes[refnode].cheie);
}

int main()
{
    Tree a={0};
    a=init(a);
    citire(&a,"in.txt");
    display(a);
    printf("\n");
    preordine(a,1);
    printf("\n");
    inordine(a,1);
    printf("\n");
    postordine(a,1);
    printf("\n");
    printf("%d\n",parinte(a,15));
    printf("%d\n",parinte(a,8));
    return 0;
}