#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

typedef struct{
    char nume[32];
    int prim_fiu;
    int frate_dr;
}nod;

typedef struct{
    nod nodes[N];
    int size;
}Tree;


Tree init(Tree a)
{
    for(int i=0;i<N;i++)
    {
        strcpy(a.nodes[i].nume,"");
        a.nodes[i].prim_fiu=0;
        a.nodes[i].frate_dr=0;
    }
    a.size=0;
    return a;
}
Tree insert(Tree a,const char *nume,int parinte)
{
    a.size++;
    strcpy(a.nodes[a.size].nume,nume);
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
        while(a.nodes[copil].frate_dr!=0)
        {
            copil=a.nodes[copil].frate_dr;
        }
        a.nodes[copil].frate_dr=a.size;
    }
    return a;
}
void display(Tree a)
{
    printf("INDEX:    ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%3d ",i);
    }
    printf("\nCHEIE:    ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%3s ",a.nodes[i].nume);
    }
    printf("\nPRIM_FIU: ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%3d ",a.nodes[i].prim_fiu);
    }
    printf("\nFRATE_DR: ");
    for(int i=0;i<=a.size;i++)
    {
        printf("%3d ",a.nodes[i].frate_dr);
    }
    printf("\n\n");
}
void citire(Tree *a,const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    char nume[32];int parinte;
    while(fscanf(f,"%s %d",nume,&parinte)==2)
    {
        *a=insert(*a,nume,parinte);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
}
void preordine(Tree a,int refnode,int nivel,int *nivel_max,int afiseaza)
{
    if(refnode<=0 || refnode>a.size)
        return;
    
    if(afiseaza) printf("%s ",a.nodes[refnode].nume);
    if(nivel_max!=NULL && nivel>*nivel_max)
    {
        *nivel_max=nivel;
    }
    preordine(a,a.nodes[refnode].prim_fiu,nivel+1,nivel_max,afiseaza);
    int copil=a.nodes[refnode].prim_fiu;
    while((copil=a.nodes[copil].frate_dr)!=0)
    {
        preordine(a,copil,nivel+1,nivel_max,afiseaza);
    }
}

int main()
{
    Tree a={0};
    a=init(a);
    citire(&a,"in.txt");
    display(a);
    int cale=0;
    preordine(a,1,1,&cale,0);
    printf("cale:%d \n",cale);
    return 0;
}