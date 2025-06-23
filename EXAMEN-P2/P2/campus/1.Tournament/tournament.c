#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct gg{
    int index;
    char winner[32];
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
void insert(nod *radacina,int index,const char *winner,int parinte)
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
        insert(radacina->st,index,winner,parinte);
        insert(radacina->dr,index,winner,parinte);
    }
}
nod* citire(const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error reading file!");
        exit(-1);
    }
    int parinte,index;
    char winner[32];
    if(fscanf(f,"%d %d %s",&parinte,&index,winner)!=3)
    {
        perror("Error root!");
        exit(-1);
    }
    nod *radacina=createNode(index,winner);
    while(fscanf(f," %d %d %s",&parinte,&index,winner)==3)
    {
        insert(radacina,index,winner,parinte);
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return radacina;
}
void each_round(nod *radacina,int afiseaza) //postordine
{
    if(radacina==NULL)
        return;

    each_round(radacina->st,afiseaza);
    each_round(radacina->dr,afiseaza);

    if(radacina->st!=NULL && afiseaza)
    {
        if(radacina->dr==NULL)
            printf("%s - empty -> %s\n",radacina->st->winner,radacina->st->winner);
        else
            printf("%s - %s -> %s\n",radacina->st->winner,radacina->dr->winner,radacina->winner);
    }
}
void final_position(nod *radacina,const char *team)
{
    if(radacina==NULL)
        return;
    final_position(radacina->st,team);
    final_position(radacina->dr,team);    
    if(strcmp(radacina->winner,team)==0 && radacina->st!=NULL)
    {
        if(radacina->dr==NULL)
            printf("%s - empty -> %s\n",radacina->st->winner,radacina->st->winner);
        else
            printf("%s - %s -> %s\n",radacina->st->winner,radacina->dr->winner,radacina->winner);
    }
}
void minimum_matches_needed(nod *radacina,int *rez)
{
    if(radacina==NULL || rez==NULL)
        return;
    if(radacina->st!=NULL && radacina->dr!=NULL)
        *rez+=1;
    minimum_matches_needed(radacina->st,rez);
    minimum_matches_needed(radacina->dr,rez);
}
void road_to_final(nod *radacina)
{
    final_position(radacina,radacina->winner);
}
int main()
{
    nod *radacina=citire("in.txt");
    each_round(radacina,1);
    printf("\n");
    final_position(radacina,"C");
    printf("\n");

    int rez=0;
    minimum_matches_needed(radacina,&rez);
    printf("%d\n\n",rez);

    road_to_final(radacina);
    return 0;
}