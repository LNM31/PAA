#include<stdio.h>
#include<stdlib.h>
#define N 50
int matrice[N][N];
int w[N][N];
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
    int a,b;
    while(fscanf(f,"%d %d",&a,&b)==2)
    {
        matrice[a%n][b%n]=1;
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return n;
}
void warshall(int matrice[N][N],int w[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            w[i][j]=matrice[i][j];
        }
    }

    for(int k=0;k<size;k++)
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(w[i][j]==0)
                    w[i][j]=w[i][k] && w[k][j];
}
void affect(int w[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("Furnizorul %d afecteaza: ",i);
        for(int j=0;j<size;j++)
        {
            if(w[j][i])
                printf("%d ",j);
        }
        printf("\n");
    }
}
void vulnerability(int w[N][N],int size)
{
    int maxim=0;
    for(int i=0;i<size;i++)
    {
        int sum=0;
        for(int j=0;j<size;j++)
        {
            sum+=w[i][j];
        }
        if(sum > maxim)
        {   
            maxim=sum;
        }
    }
    printf("Most vulnerable: ");
    for(int i=0;i<size;i++)
    {
        int sum=0;
        for(int j=0;j<size;j++)
        {
            sum+=w[i][j];
        }
        if(sum==maxim)
            printf("%d ",i);
    }
    printf("\n");
}
int main()
{
    int size=citire("in.txt");
    display(matrice,size);
    warshall(matrice,w,size);
    display(w,size);
    affect(w,size);
    vulnerability(w,size);
    return 0;
}