#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ar{
    struct ar* litere[27];
    int frec;
}nod;

typedef struct{
    char cuvant[128];
    int frec;
}com;

com completari[50];
int size=0;

void init(nod * ref)
{
    for(int i=0;i<27;i++)
        ref->litere[i]=NULL;
    ref->frec=0;
}
nod* creareNod()
{
    nod *nou=(nod*)malloc(sizeof(nod));
    if(nou==NULL)
    {
        perror("Error creating node!");
        exit(-1);
    }
    init(nou);
    return nou;
}
void insereazaCuvant(nod *radacina,const char *cuvant)
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
            curent->litere[index]=creareNod();
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
    if(radacina->litere['[' - 'A'] == radacina)
    {
        buffer[index]='\0';
        if(afiseaza) printf("%s\n",buffer);

        if(size < 50)
        {
            strcpy(completari[size].cuvant,buffer);
            completari[size++].frec=radacina->frec;
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
            printf("Nu exista cuvant care incepe cu acest prefix!\n");
            return;
        }  
        curent=curent->litere[index];  
    }

    char buffer[200];
    strcpy(buffer,prefix);
    parcurgereRecursiva(curent,buffer,strlen(prefix),afiseaza);
}

int compare(const void *p1,const void *p2)
{
    const com*e1=(com*)p1;
    const com*e2=(com*)p2;
    return e2->frec-e1->frec;
}
void autocomplete(nod *radacina,const char *prefix,int top)
{
    size=0;
    prefix_matching(radacina,prefix,0);

    qsort(completari,size,sizeof(com),compare);

    for(int i=0;i<size && i<top;i++)
    {
        printf("%s %d\n",completari[i].cuvant,completari[i].frec);
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
    char query[200];
    while(fscanf(f,"%199s",query)==1)
    {
        insereazaCuvant(*radacina,query);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
}
int main()
{
    nod *radacina=creareNod();
    citire(&radacina,"in.txt");

    char buffer[200];
    parcurgereRecursiva(radacina,buffer,0,1);
    printf("\n");

    prefix_matching(radacina,"CAS",1);
    printf("\n");

    autocomplete(radacina,"SU",3);
    printf("\n");
    autocomplete(radacina,"TI",4);
    printf("\n");
    return 0;
}