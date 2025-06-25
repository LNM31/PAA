#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50
#define inf 99999

int matrice[N][N];
int w[N][N];
int T[N][N];
int fw[N][N];

void init(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(i!=j && matrice[i][j]==0)
                matrice[i][j]=inf;
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
void display(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(matrice[i][j]==inf)
                printf(" F ");
            else
                printf("%2d ",matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void warshall(int matrice[N][N],int w[N][N],int size)
{
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(matrice[i][j]!=0 && matrice[i][j]!=inf)
                w[i][j]=1;
    
    for(int k=0;k<size;k++)
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(w[i][j]==0)
                    w[i][j]=w[i][k] && w[k][j];
}
void floyd_warshall(int matrice[N][N],int fw[N][N],int size)
{
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fw[i][j]=matrice[i][j];
    
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            T[i][j]=-1;

    for(int k=0;k<size;k++)
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(fw[i][k] + fw[k][j] < fw[i][j])
                {
                    fw[i][j]=fw[i][k] + fw[k][j];
                    T[i][j]=k;
                }
}
void traseu(int i,int j)
{
    int k=T[i][j];
    if(k==-1)
        return;
    
    traseu(i,k);
    printf("%d ",k);
    traseu(k,j);
}
void TRASEU(int i,int j)
{
    printf("%d ",i);
    traseu(i,j);
    printf("%d\n",j);
}

int main()
{
    int size=citire("in.txt");
    warshall(matrice,w,size);
    floyd_warshall(matrice,fw,size);
    display(matrice,size);
    display(w,size);
    display(fw,size);
    display(T,size);
    TRASEU(0,1);
    return 0;
}