#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define N 20 

int graph[N][N];

int citire(const char* file_name)
{
    FILE* f = fopen(file_name, "r");
    if (f == NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    int n = 0;
    if (fscanf(f, "%d", &n) != 1)
    {
        perror(NULL);
        exit(-1);
    }
    int a, b, c;
    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3)
    {
        graph[a % n][b % n] = c;
        graph[b % n][a % n] = c;
    }
    if (fclose(f) != 0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return n;
}
int minKey(int key[], bool set[],int size)
{
    int minim = INT_MAX, minim_index=-1;
    for (int i = 0; i < size; i++)
    {
        if (set[i] == false && key[i] < minim)
        {
            minim = key[i];
            minim_index = i;
        }
    }
    return minim_index;
}
void display(int parinte[N], int graph[N][N],int size)
{
    printf("muchie  val\n");
    int val = 0;
    for (int i = 1; i < size; i++)
    {
        printf("%d - %d    %d\n", parinte[i], i,graph[parinte[i]][i]);
        val += graph[parinte[i]][i];
    }
    printf("\nMinCost: %d\n",val);
}
void prim(int graph[N][N],int size)
{
    int parinte[N];
    int key[N];
    bool set[N];

    for (int i = 0; i < size; i++)
    {
        key[i] = INT_MAX;
        set[i] = false;
    }

    key[0] = 0;
    parinte[0] = -1;

    for (int i = 0; i < size - 1; i++)
    {
        int u = minKey(key, set,size);
        set[u] = true;
        for (int v = 0; v < size; v++)
        {
            if (graph[u][v] && set[v] == false && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parinte[v] = u;
            }
        }
    }
    display(parinte,graph,size);
}
int main()
{
    int n = citire("in.txt");
    prim(graph,n);
    return 0;
}
