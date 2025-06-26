#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50
int matrice[N][N];
void dfs(int matrice[N][N],int vizitat[N],int size,int start,int *nodes_visited,int afiseaza)
{
    vizitat[start]=1;
    if(afiseaza) printf("%d ",start);
    if(nodes_visited!=NULL) *nodes_visited+=1;
    for(int i=0;i<size;i++)
    {
        if(matrice[start][i] && vizitat[i]==0)
        {
            dfs(matrice,vizitat,size,i,nodes_visited,afiseaza);
        }
    }
}
int compConexe(int matrice[N][N],int *max_circle,int size)
{
    int vizitat[N]={0};
    int count=0;
    if(max_circle!=NULL) *max_circle=0;
    for(int i=0;i<size;i++)
    {
        if(vizitat[i]==0)
        {
            count++;
            printf("Grupul %d: ",count);
            int contor=0;
            dfs(matrice,vizitat,size,i,&contor,1);
            if(contor > *max_circle)
                *max_circle=contor;
            printf("\n");
        }
    }
    return count;
}
int nrCompConexe(int matrice[N][N],int size,int ignorat)
{
    int vizitat[N]={0};
    int count=0;
    for(int i=0;i<size;i++)
    {
        if(vizitat[i]==0 && i!=ignorat)
        {
            count++;
            dfs(matrice,vizitat,size,i,NULL,0);
        }
    }
    return count;
}
void func(int matrice[N][N],int aux[N][N],int nod,int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            aux[i][j]=matrice[i][j];
        }
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
    int original=nrCompConexe(matrice,size,-1);
    for(int i=0;i<size;i++)
    {
        func(matrice,aux,i,size);
        int comp_conexe=nrCompConexe(aux,size,i);
        if(comp_conexe>original)
        {
            printf("%d ",i);
        }
    }
}



void bfs(int matrice[N][N],int size,int start,int afiseaza)
{
    int vizitat[N]={0};
    int coada[N]={0},prim=0,ultim=0;

    coada[ultim++]=start;
    vizitat[start]=1;

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
void shortestPath(int matrice[N][N],int size,int start,int finish)
{
    int vizitat[N]={0};
    int parinte[N]={0};
    int coada[N]={0},prim=0,ultim=0;

    coada[ultim++]=start;
    vizitat[start]=1;
    parinte[start] = -1;

    while(prim < ultim)
    {
        int curent=coada[prim++];
        for(int i=0;i<size;i++)
        {
            if(vizitat[i]==0 && matrice[curent][i])
            {
                vizitat[i]=1;
                coada[ultim++]=i;
                parinte[i]=curent;
            }
        }
    }

    int drum[N]={0};
    int l=0;
    int i=finish;
    drum[l++]=i;
    while(i!=start)
    {
        drum[l++]=parinte[i];
        i=parinte[i];
    }
    for(int i=l-1;i>=0;i--)
    {
        printf("%d ",drum[i]);
    }
}
int citire(const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    int n;
    if(fscanf(f,"%d",&n)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    int a,b;
    while(fscanf(f,"%d %d",&a,&b)==2)
    {
        matrice[a%n][b%n]=1;
        matrice[b%n][a%n]=1;
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return n;
}



int DFS(int matrice[N][N],int vizitat[N],int size,int nod,int start,int depth)
{
    vizitat[nod]=1;
    int longestCycle=depth;
    for(int i=0;i<size;i++)
    {
        if(matrice[nod][i] && vizitat[i] && i==start && depth>1)
            return depth;
        else
        {
            int cycleLength=DFS(matrice,vizitat,size,i,start,depth + 1);
            if(cycleLength > longestCycle)
            {
                longestCycle = cycleLength;
            }
        }
    }
    vizitat[nod]=0;
    return longestCycle;
}
int main()
{
    int size=citire("in.txt");
    int max_circle=0;
    int count=compConexe(matrice,&max_circle,size);
    printf("\n%d grupuri\n",count);
    printf("Size of largest circle: %d\n\n",max_circle);
    noduriArticulatie(matrice,size);
    printf("\n");
    bfs(matrice,size,1,1);
    shortestPath(matrice,size,1,19);

   
    return 0;
}