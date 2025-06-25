#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 128
typedef struct {
    int cheie;
    int parinte;
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
        a.nodes[i].parinte=0;
    }
    return a;
}
Tree insert(Tree a,int cheie,int parinte)
{
    a.size++;
    a.nodes[a.size].cheie=cheie;
    a.nodes[a.size].parinte=parinte;
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
    printf("\nParinte:  ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].parinte);
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
        
    for(int i=1;i<=a.size;i++)
    {
        if(a.nodes[i].parinte==refnode)
            return i;
    }
    return 0;
}
int frateDr(Tree a,int refnode)
{
    if(refnode<=0 || refnode>=a.size)
        return 0;
    
    for(int i=refnode+1 ;i<=a.size;i++)
    {
        if(a.nodes[i].parinte==a.nodes[refnode].parinte)
            return i;
    }
    return 0;
}
int parinte(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return 0;
    
    return a.nodes[refnode].parinte;
}
void preordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;

    printf("%d ",a.nodes[refnode].cheie);
    
    int copil=primFiu(a,refnode);
    preordine(a,copil);
    while((copil=frateDr(a,copil))!=0)
    {
        preordine(a,copil);
    }
}
void inordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;

    
    int copil=primFiu(a,refnode);
    inordine(a,copil);

    printf("%d ",a.nodes[refnode].cheie);
    
    while((copil=frateDr(a,copil))!=0)
    {
        inordine(a,copil);
    }
}
void postordine(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return;
    
    int copil=primFiu(a,refnode);
    postordine(a,copil);
    while((copil=frateDr(a,copil))!=0)
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