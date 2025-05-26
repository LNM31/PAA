//#include <stdio.h>
//#include <limits.h>
//#include <stdbool.h>
//
//#define MAX 100
//#define V 5
//
//typedef struct {
//    int node;
//    int weight;
//} Pair;
//
//Pair adj[MAX][MAX];
//int adjSize[MAX];
//
//void addEdge(int u, int v, int w) {
//    adj[u][adjSize[u]].node = v;
//    adj[u][adjSize[u]++].weight = w;
//
//    adj[v][adjSize[v]].node = u;
//    adj[v][adjSize[v]++].weight = w;
//}
//
//
//void dijkstra(int src, int dist[V]) {
//    bool visited[V] = { false };
//
//    for (int i = 0; i < V; i++)
//        dist[i] = INT_MAX;
//
//    dist[src] = 0;
//
//    for (int count = 0; count < V - 1; count++)
//    {
//        int min = INT_MAX, u = -1;
//        for (int i = 0; i < V; i++)
//            if (!visited[i] && dist[i] < min)
//                min = dist[i], u = i;
//
//        if (u == -1) break;
//        visited[u] = true;
//
//        for (int i = 0; i < adjSize[u]; i++)
//        {
//            int v = adj[u][i].node;
//            int w = adj[u][i].weight;
//            if (!visited[v] && dist[u] + w < dist[v])
//                dist[v] = dist[u] + w;
//        }
//    }
//}
//
//// Test
//int main() {
//    int dist[V];
//
//    addEdge(0, 1, 4);
//    addEdge(0, 2, 8);
//    addEdge(1, 4, 6);
//    addEdge(2, 3, 2);
//    addEdge(3, 4, 10);
//
//    dijkstra(0, dist);
//
//    // Afi?eaz? distan?ele
//    for (int i = 0; i < V; i++)
//        printf("%d ", dist[i]);
//    printf("\n");
//
//    return 0;
//}
