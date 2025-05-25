#include <stdio.h>
#include <stdlib.h>

#define N 14

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

void unionSet(int u, int v, int parent[], int rank[], int n)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

int kruskalAlgo(int n, int edge[N][3])
{
    qsort(edge, n, sizeof(edge[0]), comparator);
    int parent[N];
    int rank[N];

    //MakeSet
    for (int i = 0; i < n; i++) 
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int minCost = 0;
    for (int i = 0; i < n; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];
        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
        }
    }

    return minCost;
}

int main()
{
    int edge[14][3] = { 
    { 0, 1, 4 },
    { 0, 7, 8 },
    { 1, 7, 11 },
    { 1, 2, 8 },
    { 7, 8, 7 },
    { 7, 6, 1 },
    { 2, 8, 2 },
    { 8, 6, 6 },
    { 2, 3, 7 },
    { 2, 5, 4 },
    { 6, 5, 2 },
    { 3, 5, 14 },
    { 3, 4, 9 },
    { 5, 4, 10 }
    };

    printf("%d", kruskalAlgo(14, edge));

    return 0;
}