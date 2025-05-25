#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define N 9 
int graph[N][N] = {
    {0,4,0,0,0,0,0,8,0},
    {4,0,8,0,0,0,0,11,0},
    {0,8,0,7,0,4,0,0,2},
    {0,0,7,0,9,14,0,0,0},
    {0,0,0,9,0,10,0,0,0},
    {0,0,4,14,10,0,2,0,0},
    {0,0,0,0,0,2,0,1,6},
    {8,11,0,0,0,0,1,0,7},
    {0,0,2,0,0,0,6,7,0},
};
int minKey(int key[], bool set[])
{
    int minim = INT_MAX, minim_index;
    for (int i = 0; i < N; i++)
    {
        if (set[i] == false && key[i] < minim)
        {
            minim = key[i];
            minim_index = i;
        }
    }
    return minim_index;
}
void display(int parinte[N], int graph[N][N])
{
    printf("muchie  val\n");
    for (int i = 1; i < N; i++)
    {
        printf("%d - %d    %d\n", parinte[i], i,graph[parinte[i]][i]);
    }
    printf("\n");
}
void prim(int graph[N][N])
{
    int parinte[N];
    int key[N];
    bool set[N];

    for (int i = 0; i < N; i++)
    {
        key[i] = INT_MAX;
        set[i] = false;
    }

    key[0] = 0;
    parinte[0] = -1;

    for (int i = 0; i < N - 1; i++)
    {
        int u = minKey(key, set);
        set[u] = true;
        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] && set[v] == false && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parinte[v] = u;
            }
        }
    }
    display(parinte,graph);
}
int main()
{
    prim(graph);
    return 0;
}