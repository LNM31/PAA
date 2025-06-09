#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct gg{
    int index;
    char winner[64];
    struct gg *st;
    struct gg *dr;
}nod;

nod *createNode(int index,const char *winner)
{
    nod *nou=(nod *)malloc(sizeof(nod));
    if(nou==NULL)
    {
        perror("Error creating node!");
        exit(-1);
    }
    nou->index=index;
    strcpy(nou->winner,winner);
    nou->st=NULL;
    nou->dr=NULL;
    return nou;
}
void adauga(nod *radacina,int index,const char *winner,int parinte)
{
    if(radacina==NULL)
        return;

    if(radacina->index==parinte)
    {
        if(radacina->st==NULL)
            radacina->st=createNode(index,winner);
        else if(radacina->dr==NULL)
            radacina->dr=createNode(index,winner);
        return;
    }
    else
    {
        adauga(radacina->st,index,winner,parinte);
        adauga(radacina->dr,index,winner,parinte);
    }
}
void postordine(nod *radacina,int afiseaza)
{
    if(radacina==NULL || radacina->dr==NULL)
        return;
    
    postordine(radacina->st,afiseaza);
    postordine(radacina->dr,afiseaza);
    if(afiseaza) printf("%s vs %s -> winner :%s\n",radacina->st->winner,radacina->dr->winner,radacina->winner);
}

void path(nod *radacina,const char *team)
{
    if(radacina==NULL || radacina->dr==NULL)
        return;
        
    if(strcmp(radacina->winner,team)==0)
        printf("%s vs %s -> winner :%s\n",radacina->st->winner,radacina->dr->winner,radacina->winner);

    path(radacina->st,team);
    path(radacina->dr,team);
}

void minimum_matches(nod *radacina,int *matches)
{
    if(radacina==NULL || radacina->dr==NULL)
        return;
    
    *matches+=1;

    minimum_matches(radacina->st,matches);
    minimum_matches(radacina->dr,matches);
}
nod *citire(nod *radacina,const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    int index,parinte;
    char team[64];
    if(fscanf(f,"%d %63s %d",&index,team,&parinte)!=3)
    {
        perror("Error");
        exit(-1);
    }
    radacina=createNode(index,team);
    while(fscanf(f,"%d %63s %d",&index,team,&parinte)==3)
    {
        adauga(radacina,index,team,parinte);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return radacina;
}
int main()
{
    nod *radacina=NULL;
    radacina=citire(radacina,"in.txt");
    postordine(radacina,1);
    
    printf("\nPath :\n");
    path(radacina,"E");

    int matches=0;
    minimum_matches(radacina,&matches);
    printf("\nMinimul de meciuri: %d\n",matches);

    printf("\nWinner - Road to Final:\n");
    path(radacina,radacina->winner);
    return 0;
}