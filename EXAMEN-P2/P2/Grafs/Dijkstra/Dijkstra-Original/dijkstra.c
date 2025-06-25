#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50
#define inf 9999
int matrice[N][N];
int vizitat[N];
int dist[N];
int parinte[N];

void init(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(i!=j && matrice[i][j]==0)
            {
                matrice[i][j]=inf;
            }
        }
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
    int n=0;
    if(fscanf(f,"%d",&n)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    int a,b,c;
    while(fscanf(f,"%d %d %d",&a,&b,&c)==3)
    {
        matrice[a%n][b%n]=c;
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    init(matrice,n);
    return n;
}
void display(int dist[N],int parinte[N],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%2c ",'A' + i);
    }
    printf("\n");
    for(int i=0;i<size;i++)
    {
        printf("%2d ",dist[i]);
    }
    printf("\n");
    for(int i=0;i<size;i++)
    {
        printf("%2c ",'A' + parinte[i]);
    }
    printf("\n");
}
void dijkstra(int matrice[N][N],int size,int s)
{
    for(int i=0;i<size;i++)
    {
        vizitat[i]=0;
        dist[i]=matrice[s][i];
        parinte[i]=s;
    }

    vizitat[s]=1;
    for(int pas=0;pas<size-1;pas++)
    {
        int pmin=-1;
        for(int i=0;i<size;i++)
        {
            if(vizitat[i]==0 && (pmin==-1 || dist[i]<dist[pmin]))
            {
                pmin=i;
            }
        }
        vizitat[pmin]=1;
        for(int i=0;i<size;i++)
        {
            if(vizitat[i]==0 && dist[pmin] + matrice[pmin][i] < dist[i])
            {
                dist[i] =  dist[pmin] + matrice[pmin][i];
                parinte[i]=pmin;
            }
        }
    }
}
void drum(int matrice[N][N],int size,int source,int finish)
{
    int path[N]={0};
    int lung=0;

    dijkstra(matrice,size,source);

    int i=finish;
    path[lung++]=i;
    while(i!=source)
    {
        path[lung++]=parinte[i];
        i=parinte[i];
    }
    
    for(int i=lung-1;i>=0;i--)
    {
        printf("%c ",'A' + path[i]);
    }
    printf("\n");
}
int main()
{
    int size=citire("in.txt");
    dijkstra(matrice,size,0);
    display(dist,parinte,size);
    drum(matrice,size,0,2);
    return 0;
}