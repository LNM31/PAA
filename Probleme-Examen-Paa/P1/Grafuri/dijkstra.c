#include<stdio.h>
#include<stdlib.h>

#define N 30
#define inf 9999

int matrice[N][N];
int dist[N];
int parinte[N];
int vizitat[N];


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
    char a,b;
    int c;
    while(fscanf(f," %c %c %d",&a,&b,&c)==3)
    {
        matrice[a-'A'][b-'A']=c;
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
    for(int i=0;i<size;i++)
        printf("%2c ",'A' + i);
    
    printf("\n");
    for(int i=0;i<size;i++)
        printf("%2d ",dist[i]);

    printf("\n");
    for(int i=0;i<size;i++)
        printf("%2c ",'A' + parinte[i]);

    printf("\n");
}
void dijkstra(int matrice[N][N],int size,int s)
{
    for(int i=0;i<size;i++)
    {
        dist[i]=matrice[s][i];
        parinte[i]=s;
        vizitat[i]=0;
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
            if(vizitat[i]==0 && dist[pmin]+matrice[pmin][i] < dist[i])
            {
                dist[i]=dist[pmin]+matrice[pmin][i];
                parinte[i]=pmin;
            }
        }
    }
    display(matrice,size);
}
void drum(int source,int destination)
{
    int path[N]={0};
    int size=0;
    int i=destination;
    while(i!=source)
    {
        path[size++]=i;
        i=parinte[i];
    }
    printf("%c ",'A' + source);
    for(int i=size-1;i>=0;i--)
        printf("%c ", 'A' + path[i]);
    printf("\n");
}
int main()
{
    int n=citire("in.txt");
    dijkstra(matrice,n,0);
    drum(0,3);
    return 0;
}