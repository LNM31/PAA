#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 20

int matrice[N][N];
int w[N][N];
int risc;

int citire(const char *file_name)
{
    FILE *f=fopen(file_name,"r");
    if(f==NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    if(fscanf(f,"%d",&risc)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    int n;
    if(fscanf(f,"%d",&n)!=1)
    {
        perror("Error reading n!");
        exit(-1);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(fscanf(f,"%d",&matrice[i][j])!=1)
            {
                perror("error reading matrix");
                exit(-1);
            }
        }    
    }
    if(fclose(f)!=0)
    {
        perror("Error closing file");
        exit(-1);
    }
    return n;
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
                    w[i][j]=w[i][k] && w[k][j];
}
int permisiuni(int w[N][N],int size,int ang)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        if(w[ang][i])
            sum++;
    }
    return sum;
}
void func1(int w[N][N],int size)
{
    int maxim=0,permi;
    for(int i=0;i<size;i++)
    {
        permi=permisiuni(w,size,i);
        if(permi>maxim)
            maxim=permi;
    }
    for(int i=0;i<size;i++)
    {
        if(permisiuni(w,size,i)==maxim)
            printf("%d ",i);
    }
    printf("\n\n");
}
void func2(int w[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        if(permisiuni(w,size,i)>=risc)
            printf("%d ",i);
    }
    printf("\n");
}
int main(int argc,char **argv)
{
    if(argc!=2)
    {
        perror("Error arguments");
        exit(-1);
    }
    int size=citire(argv[1]);
    warshall(matrice,size);
    func1(w,size);
    func2(w,size);
    return 0;
}