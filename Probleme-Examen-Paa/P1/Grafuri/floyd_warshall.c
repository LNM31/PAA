#include<stdio.h>
#include<stdlib.h>

#define N 30
#define inf 9999

int matrice[N][N];

int fw[N][N];
int traseu[N][N];

int w[N][N];

void init(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
            if(matrice[i][j]==0 && i!=j)
                matrice[i][j]=inf;
    }
}
int citire(const char *file_name)
{
    FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror(NULL);
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
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-1);
	}
    init(matrice,n);
    return n;

}
void display(int matrice[N][N],int size)
{
    printf("\n");
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(matrice[i][j]==inf)
                printf("inf ");
            else
                printf("%3d ",matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void floyd_warshall(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            fw[i][j]=matrice[i][j];
        }
    }
    for(int k=0;k<size;k++)
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(fw[i][k]+fw[k][j]<fw[i][j])
                {
                    fw[i][j]=fw[i][k]+fw[k][j];
                    traseu[i][j]=k;
                }
}
void warshall(int matrice[N][N],int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(matrice[i][j] && matrice[i][j]!=inf)
                w[i][j]=1;
        }
    }
    for(int k=0;k<size;k++)
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(w[i][j]==0)
                {
                    w[i][j]=w[i][k] && w[k][j];
                }

}
void drum(int i,int j)
{
    int k=traseu[i][j];
    if(k==0)
        return;
    drum(i,k);
    printf("%d ",k);
    drum(k,j);
}
int main()
{
    int n=citire("in2.txt");
    display(matrice,n);
    floyd_warshall(matrice,n);
    drum(0,2);
    display(fw,n);

    warshall(matrice,n);
    display(matrice,n);
    display(w,n);
    return 0;
}