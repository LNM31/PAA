#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100
#define V 5

// Structur? pentru o pereche (vecin, greutate)
typedef struct {
    int node;
    int weight;
} Pair;

// Lista de adiacen??
Pair adj[MAX][MAX]; // adj[i] con?ine vecinii nodului i
int adjSize[MAX];   // câ?i vecini are fiecare nod

// Adaug? muchie neorientat?
void addEdge(int u, int v, int w) {
    adj[u][adjSize[u]].node = v;
    adj[u][adjSize[u]++].weight = w;

    adj[v][adjSize[v]].node = u;
    adj[v][adjSize[v]++].weight = w;
}

// Dijkstra simplificat f?r? heap
void dijkstra(int src, int dist[V]) {
    bool visited[V] = { false };

    // Ini?ializeaz? distan?ele
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        // Alege nodul nevizitat cu distan?a minim?
        int min = INT_MAX, u = -1;
        for (int i = 0; i < V; i++)
            if (!visited[i] && dist[i] < min)
                min = dist[i], u = i;

        if (u == -1) break; // Toate nodurile accesibile au fost vizitate
        visited[u] = true;

        // Actualizeaz? vecinii
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i].node;
            int w = adj[u][i].weight;
            if (!visited[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
}

// Test
int main() {
    int dist[V];

    addEdge(0, 1, 4);
    addEdge(0, 2, 8);
    addEdge(1, 4, 6);
    addEdge(2, 3, 2);
    addEdge(3, 4, 10);

    dijkstra(0, dist);

    // Afi?eaz? distan?ele
    for (int i = 0; i < V; i++)
        printf("%d ", dist[i]);
    printf("\n");

    return 0;
}
