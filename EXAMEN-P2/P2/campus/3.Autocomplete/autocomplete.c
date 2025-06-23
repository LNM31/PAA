#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct ar{
    struct ar* litere[27];
    int frec;
}nod;

typedef struct{
    char cuvant[256];
    int frec;
}com;

com tab[100];
int size;

nod *createNode()
{
    nod *nou=(nod*)malloc(sizeof(nod));
    if(nou==NULL)
    {
        perror("Error creating node!");
        exit(-1);
    }
    for(int i=0;i<27;i++)
        nou->litere[i]=NULL;
    nou->frec=0;

    return nou;
}
void insereaza(nod *radacina,const char *cuvant)
{
    if(radacina==NULL)
        return;
    nod *curent=radacina;
    curent->frec++;
    for(int i=0;i<strlen(cuvant);i++)
    {
        char ch=cuvant[i];
        int index=ch - 'A';
        if(curent->litere[index]==NULL)
        {
            curent->litere[index]=createNode();
        }
        curent=curent->litere[index];
        curent->frec++;
    }
    curent->litere['[' - 'A']=curent;
}
void parcurgereRecursiva(nod *radacina,char *buffer,int index,int afiseaza)
{
    if(radacina==NULL)
        return;
    if(radacina->litere['[' - 'A']==radacina)
    {
        buffer[index]='\0';
        if(afiseaza) printf("%s\n",buffer);

        if(size<100)
        {
            strcpy(tab[size].cuvant,buffer);
            tab[size++].frec=radacina->frec;
        }
    }

    for(int i=0;i<26;i++)
    {
        if(radacina->litere[i]!=NULL)
        {
            buffer[index]='A' + i;
            parcurgereRecursiva(radacina->litere[i],buffer,index+1,afiseaza);
        }
    }
}
void citire(nod **radacina,const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    char cuvant[256];
    while(fscanf(f,"%s",cuvant)==1)
    {
        insereaza(*radacina,cuvant);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
}
void prefix_matching(nod *radacina,const char *prefix,int afiseaza)
{
    if(radacina==NULL)
        return;
    nod *curent=radacina;
    for(int i=0;i<strlen(prefix);i++)
    {
        char ch=prefix[i];
        int index=ch - 'A';
        if(curent->litere[index]==NULL)
        {
            printf("Nu exista cuvant cu acest prefix!\n");
            return;
        }
        curent=curent->litere[index];
    }

    char buffer[256];
    strcpy(buffer,prefix);
    parcurgereRecursiva(curent,buffer,strlen(prefix),afiseaza);

}
int compare(const void *p1,const void *p2)
{
    const com *e1=(com *)p1;
    const com *e2=(com *)p2;
    return e2->frec-e1->frec;
}
void autocomplete(nod *radacina,const char *prefix,int top)
{
    size=0;
    if(radacina==NULL)
        return;
    
    prefix_matching(radacina,prefix,0);
    qsort(tab,size,sizeof(com),compare);

    for(int i=0;i<top && i<size;i++)
    {
        printf("%s -> %d\n",tab[i].cuvant,tab[i].frec);
    }
}
int main()
{
    nod *radacina=createNode();
    citire(&radacina,"in.txt");
    
    char buffer[256];
    parcurgereRecursiva(radacina,buffer,0,0);
    prefix_matching(radacina,"CAS",1);
    printf("\n");
    autocomplete(radacina,"SU",3);
    printf("\n");
    autocomplete(radacina,"TI",3);
    return 0;
}