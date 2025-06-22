#include <stdio.h>
#include <stdlib.h>
#define N 50

int matrice[N][N];
int citire(const char* file_name)
{
	FILE *f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error opening file!");
		exit(-1);
	}
	int n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n!");
		exit(-1);
	}
	int a = 0, b = 0;
	while (fscanf(f, "%d %d", &a, &b) == 2)
	{
		matrice[a % n][b % n] = 1;
		matrice[b % n][a % n] = 1;
	}
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
	return n;
}

void dfs(int matrice[N][N],int vizitat[N],int size,int start,int afiseaza,int *nodes_visited)
{
    vizitat[start]=1;
    if(nodes_visited!=NULL) *nodes_visited+=1;
    if(afiseaza) printf("%d ",start);
    for(int i=0;i<size;i++)
    {
        if(matrice[start][i] && vizitat[i]==0)
        {
            dfs(matrice,vizitat,size,i,afiseaza,nodes_visited);
        }
    }
}
int componenteConexe(int matrice[N][N],int size,int *max_circle,int afiseaza)
{
    int count=0,aux=0;
    *max_circle=0;
    int vizitat[N]={0};
    for(int i=0;i<size;i++)
    {
        if(vizitat[i]==0)
        {
            aux=0;
            count++;
            printf("Grupul %d: ",count);
            dfs(matrice,vizitat,size,i,afiseaza,&aux);
            if(aux>*max_circle)
                *max_circle=aux;
            printf("\n");
        }
    }
    return count;
}

int nr_componenteConexe(int matrice[N][N],int size,int ignorat)
{
    int count=0;
    int vizitat[N]={0};
    for(int i=0;i<size;i++)
    {
        if(vizitat[i]==0 && i!=ignorat)
        {
            count++;
            dfs(matrice,vizitat,size,i,0,NULL);
        }
    }
    return count;
}
void func(int matrice[N][N],int aux[N][N],int nod,int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
            aux[i][j]=matrice[i][j];
    }

    for(int i=0;i<size;i++)
    {
        aux[nod][i]=0;
        aux[i][nod]=0;
    }
}
void noduriArticulatie(int matrice[N][N],int size)
{
    int aux[N][N];
    int original=nr_componenteConexe(matrice,size,-1);
    printf("\nNoduri de art: ");
    for(int i=0;i<size;i++)
    {
        func(matrice,aux,i,size);
        int comp=nr_componenteConexe(aux,size,i);
        if(comp>original)
            printf("%d ",i);
    }
    printf("\n");
}

void bfs(int matrice[N][N],int size,int start,int afiseaza)
{
    int vizitat[N]={0};
    int coada[N],prim=0,ultim=0;

    vizitat[start]=1;
    coada[ultim++]=start;
    while(prim < ultim)
    {
        int curent=coada[prim++];
        if(afiseaza) printf("%d ",curent);
        for(int i=0;i<size;i++)
        {
            if(vizitat[i]==0 && matrice[curent][i])
            {
                vizitat[i]=1;
                coada[ultim++]=i;
            }
        }
    }
    printf("\n");
}
int main()
{
    int n=citire("in.txt");
    int max_circle=0;
    printf("\nNumarul de grupuri : %d\n",componenteConexe(matrice,n,&max_circle,1));
    printf("Cel mai mare grup are %d persoane\n",max_circle);
    noduriArticulatie(matrice,n);
   
    bfs(matrice,n,13,1);
    return 0;
}