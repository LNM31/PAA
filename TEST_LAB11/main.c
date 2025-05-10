#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#define N 20
int matrice[N][N];
//cautare prin cuprindere si gasirea drumului cel mai scurt
void init()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrice[i][j] = 0;
		}
	}
}
void display(int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int citire(const char* file_name)
{
	FILE* f = fopen(file_name, "r");
	int n = 0;
	if (f == NULL)
	{
		perror(NULL);
		exit(-1);
	}
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n");
		exit(-3);
	}
	int x = n, a, b;
	while (x)
	{
		if (fscanf(f, "%d %d", &a, &b) != 2)
		{
			perror("error reading edge");
			exit(-4);
		}
		if (a >= N || b >= N)
		{
			perror("index out of bounds");
			exit(-2);
		}
		matrice[a][b] = 1;
		matrice[b][a] = 1;
		x--;
	}
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-2);
	}
	return n;
}
void BFS(int matrice[N][N], int start)
{
	int vizitat[N] = { 0 };
	int coada[N], prim = 0, ultim = 0;

	vizitat[start] = 1;
	coada[ultim++] = start;

	while (prim < ultim) 
	{
		int current = coada[prim++];
		printf("%d ", current);

		for (int i = 0; i < N; i++) 
		{
			if (matrice[current][i] == 1 && vizitat[i]==0) 
			{
				vizitat[i] = 1;
				coada[ultim++] = i;
			}
		}
	}
	printf("\n");
}
int visited[N] = { 0 };
void DFS_recursiv(int matrice[N][N], int start)
{
	visited[start] = 1;
	printf("%d ", start);
	for (int i = 0; i < N; i++)
	{
		if (matrice[start][i] == 1 && visited[i] == 0)
		{
			DFS_recursiv(matrice, i);
		}
	}
}


// Utility function for DFS traversal
void DFSUtil(int graph[N][N], int start,int visited[N])
{
	// Mark the current node as visited and print it
	visited[start] = 1;
	printf("%d ", start);

	// Visit all the adjacent nodes
	for (int i = 0; i < N; i++)
	{
		if (graph[start][i] == 1 && !visited[i])
		{
			DFSUtil(graph, i, visited);
		}
	}
}
// Function to perform DFS traversal
void DFS(int graph[N][N], int start)
{
	// Initialize visited array
	int visited[N] = { 0 };
	DFSUtil(graph, start, visited);
	printf("\n");
}


int main()
{
	int n;
	init();
	n=citire("in.txt");
	display(12);
	BFS(matrice, 0);
	DFS_recursiv(matrice, 6);
	printf("\n");
	DFS(matrice, 6);
	return 0;
}