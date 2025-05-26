#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 50

int edge[N][3];

int citire(const char* file_name)
{
    FILE* f = fopen(file_name, "r");
    if (f == NULL)
    {
        perror("Error opening file!");
        exit(-1);
    }
    int n = 0; //nr de noduri ,irelevant in acest caz
    if (fscanf(f, "%d", &n) != 1)
    {
        perror(NULL);
        exit(-1);
    }
    int count = 0; //nr_muchii
    int a, b, c;
    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3)
    {
        edge[count][0] = a;
        edge[count][1] = b;
        edge[count++][2] = c;
    }
    if (fclose(f) != 0)
    {
        perror("Error closing file!");
        exit(-1);
    }
    return count;
}

int comparator(const int p1[], const int p2[])
{
    return p1[2] - p2[2];
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) 
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else 
    {
        parent[v] = u;
        rank[u]++;
    }
}

int kruskal(int size, int edge[N][3])
{
    qsort(edge, size, sizeof(edge[0]), comparator);
    int parent[N];
    int rank[N];

    //MakeSet
    for (int i = 0; i < size; i++) 
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int minCost = 0;
    for (int i = 0; i < size; i++) 
    {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        if (v1 != v2) {
            unionSet(v1, v2, parent, rank);
            minCost += edge[i][2];
            printf("%d - %d : %d\n", edge[i][0], edge[i][1], edge[i][2]);
        }
    }

    return minCost;
}

int main()
{
    int n = citire("in.txt");
    printf("\nCost minim: %d\n", kruskal(14, edge));

    return 0;
}