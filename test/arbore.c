#include<stdio.h>
#include<stdlib.h>
#define N 50

typedef struct gg{
  int index;
  int raspuns; // 0-nu 1-da
  struct gg *st;
  struct gg *dr;
}nod;

int size=0; //nr noduri
int tab[N];

int size_pacient=0;
int pacient[N];

nod* creareNod(int index,int raspuns)
{
  nod *nou=(nod *)malloc(sizeof(nod));
  if(nou==NULL)
    {
      perror("err cre");
      exit(-1);
    }
  nou->index=index;
  nou->raspuns=raspuns;
  nou->st=NULL;
  nou->dr=NULL;
  return nou;
}

void insereazaNod(nod *radacina,int index,int raspuns,int parinte)
{
  if(radacina==NULL)
    return;
  if(radacina->index==parinte)
    {
      if(raspuns==0 && radacina->st==NULL) //NU
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
      insereazaNod(radacina->st,index,raspuns,parinte);
      insereazaNod(radacina->dr,index,raspuns,parinte);
    }
}

void preordine(nod *radacina,int nivel,int *nivel_max,int afisare)
{
  if(radacina==NULL)
    return;
  if(afisare) printf("(%c %d) ",radacina->index + 'A' -1,radacina->raspuns);
  if(nivel_max!= NULL && nivel>*nivel_max) *nivel_max += 1;
  preordine(radacina->st, nivel+1,nivel_max, afisare);
  preordine(radacina->dr, nivel+1,nivel_max, afisare);
}



void citire1(const char *file_name)
{
  FILE *f=fopen(file_name,"r");
  if(f==NULL)
    {
      perror("err 1");
      exit(-1);
    }
  if(fscanf(f,"%d",&size)!=1)
    {
      perror("err 1");
      exit(-1);
    }
  int index=0;
  for(int i=0;i<size;i++)
    {
      if(fscanf(f,"%d",&index)!=1)
      {
	perror("err index for");
	exit(-1);
      }
      tab[i]=index;
    }
  if(fclose(f)!=0)
    {
      perror("err cl1");
      exit(-1);
    }
}
void citire2(const char *file_name)
{
  FILE *f=fopen(file_name,"r");
  if(f==NULL)
    {
      perror("err 1 citire 2");
      exit(-1);
    }
  int raspuns=0;
  while(fscanf(f,"%d",&raspuns)==1)
    {
      pacient[size_pacient++]=raspuns;
    }
  if(fclose(f)!=0)
    {
      perror("err cl1");
      exit(-1);
    }
}
int main(int argc,char **argv)
{
  if(argc!=3)
    {
      perror("err argc");
      exit(-1);
    }

  citire1(argv[1]);
  citire2(argv[2]);

  for(int i=0;i<size;i++)
    printf("%d ",tab[i]);
  printf("\n");
  for(int i=0;i<size_pacient;i++)
    printf("%d ",pacient[i]);
  printf("\n");

  int index=2;
  nod *radacina=creareNod(1,1);
  for(int i=1;i<size;i++)
    insereazaNod(radacina,i+1,(i+1)%2,tab[i]);

  printf("Preordine: ");
  int nivel = 0;
  preordine(radacina,1,&nivel, 1);
  printf("\nNivelul maxim: %d\n", nivel);
  return 0;
}
