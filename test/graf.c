#include<stdio.h>
#include<stdlib.h>
#define N 20

int matrice[N][N];
int w[N][N]; //warshall
void display(int matrice[N][N],int size)
{
  for(int i=0;i<size;i++)
    {
      for(int j=0;j<size;j++)
	{
	  printf("%d ",matrice[i][j]);
	}
      printf("\n");
    }
  printf("\n");
}
int citire(const char *file_name,int *size)
{
  FILE *f=fopen(file_name,"r");
  if(f==NULL)
    {
      perror("error opening file");
      exit(-1);
    }
  int maxim=0;
  if(fscanf(f,"%d",&maxim)!=1)
    {
      perror("error maxim");
      exit(-1);
    }
  if(fscanf(f,"%d",size)!=1)
    {
      perror("error reading size");
      exit(-1);
    }
  int a=0,b=0;
  while(fscanf(f,"%d %d",&a,&b)==2)
    {
      matrice[a%(*size)][b%(*size)]=1;
    }
  if(fclose(f)!=0)
    {
      perror("error closing file");
      exit(-1);
    }
  return maxim;
}
void warshall(int matrice[N][N],int size)
{
  for(int i=0;i<size;i++)
    {
      for(int j=0;j<size;j++)
	w[i][j]=matrice[i][j];
    }
  for(int k=0;k<size;k++)
    for(int i=0;i<size;i++)
      for(int j=0;j<size;j++)
	if(w[i][j]==0)
	  {
	    w[i][j]=w[i][k] && w[k][j];
	  }
}
void permisiuni(int w[N][N],int size)
{
  int per=0;
  int per_max=0;
  for(int i=0;i<size;i++)
    {
      per=0;
      for(int j=0;j<size;j++)
	{
	  if(w[i][j])
	    per++;
	}
      if(per>per_max)
	per_max=per;
    }

  printf("\nangajatii cu pers max: ");
  for(int i=0;i<size;i++)
    {
      per=0;
      for(int j=0;j<size;j++)
	{
	  if(w[i][j])
	    per++;
	}
      if(per==per_max)
	printf("%d ",i);
    }
  printf("\n");
}

void risc(int w[N][N],int size,int maxim)
{
  int per=0;
  printf("\nangajatii cu risc de securitate: ");
  for(int i=0;i<size;i++)
    {
      per=0;
      for(int j=0;j<size;j++)
	{
	  if(w[i][j])
	    per++;
	}
      if(per>=maxim)
	printf("%d ",i);
    }
  printf("\n");
}
int main(int argc,char ** argv)
{
  
  if(argc!=2)
    {
      perror("error arguments");
      exit(-1);
    }
 
  int size=0;
  int maxim=citire("in.txt",&size);
  printf("maxim %d\n",maxim);
  display(matrice,size);

  warshall(matrice,size);
  display(w,size);

  permisiuni(w,size);

  risc(w,size,maxim);
  return 0;
}
