#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 64
typedef struct{
    char cheie[64];
    int prim_fiu;//prim-fiu
    int frate_dr;//frate-dreapta
}nod;

typedef struct{
    nod nodes[N];
    int size;
}Tree;

Tree init(Tree a)
{
    for(int i=0;i<N;i++)
    {
        strcpy(a.nodes[i].cheie,"");
        a.nodes[i].prim_fiu=0;
        a.nodes[i].frate_dr=0;
    }
    a.size=0;
    return a;
}

Tree insertNode(Tree a,int parinte,char *cheie)
{
    a.size++;
    strcpy(a.nodes[a.size].cheie,cheie);
    if(parinte==0)
    {
        a.nodes[a.size].frate_dr=0;
        return a;
    }
    if(a.nodes[parinte].prim_fiu==0)
    {
        a.nodes[parinte].prim_fiu=a.size;
    }
    else
    {
        int frate=a.nodes[parinte].prim_fiu;
        while(a.nodes[frate].frate_dr!=0)
        {
            frate=a.nodes[frate].frate_dr;
        }
        a.nodes[frate].frate_dr=a.size;
    }
    return a;
}

int firstChild(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return 0;
    return a.nodes[refnode].prim_fiu;
    
}
int rightSibling(Tree a,int refnode)
{
    if(refnode<=0 || refnode>a.size)
        return 0;
    return a.nodes[refnode].frate_dr;
    
}
void afisare(Tree a)
{
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",i);
    }
    printf("\n");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2s ",a.nodes[i].cheie);
    }
    printf("\n");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].prim_fiu);
    }
    printf("\n");
    for(int i=0;i<=a.size;i++)
    {
        printf("%2d ",a.nodes[i].frate_dr);
    }
    printf("\n\n");
}
void citire(Tree *a,const char *file_name)
{
    FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error opening file!");
		exit(-1);
	}
	int parinte;
    char cheie[64];
    while(fscanf(f,"%d %63s",&parinte,cheie)==2)
    {
        *a=insertNode(*a,parinte,cheie);
    }
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
}

void preordine(Tree a,int refnode,int nivel,int *inaltime,int afiseaza)
{
    if(refnode>0 && refnode<=a.size)
    {
        if(nivel>*inaltime)
            *inaltime=nivel;
        if(afiseaza) printf("%s ",a.nodes[refnode].cheie);
        int copil=a.nodes[refnode].prim_fiu;
        preordine(a,copil,nivel+1,inaltime,afiseaza);
        while((copil=a.nodes[copil].frate_dr)!=0)
        {
            preordine(a,copil,nivel+1,inaltime,afiseaza);
        }
    }
}
void inordine(Tree a,int refnode)
{
    if(refnode>0 && refnode<=a.size)
    {
        int copil=a.nodes[refnode].prim_fiu;
        inordine(a,copil);
        printf("%s ",a.nodes[refnode].cheie);
        while((copil=a.nodes[copil].frate_dr)!=0)
        {
            inordine(a,copil);
        }
    }
}
void postordine(Tree a,int refnode)
{
    if(refnode>0 && refnode<=a.size)
    {
        int copil=a.nodes[refnode].prim_fiu;
        postordine(a,copil);
        while((copil=a.nodes[copil].frate_dr)!=0)
        {
            postordine(a,copil);
        }
        printf("%s ",a.nodes[refnode].cheie);
    }
}
int main()
{
    Tree a;
    a=init(a);
    citire(&a,"2_directoare_in.txt");
    afisare(a);
    inordine(a,1);
    printf("\n");
    postordine(a,1);
    printf("\n");

    int inaltime=0;
    preordine(a,1,1,&inaltime,0);
    printf("Inaltime: %d\n",inaltime);
    return 0;
}