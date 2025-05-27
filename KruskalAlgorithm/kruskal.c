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
		perror(NULL);
		exit(-1);
	}
	int count = 0, n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror(NULL);
		exit(-1);
	}
	int a, b, c;
	while (fscanf(f, "%d %d %d", &a, &b, &c) == 3)
	{
		edge[count][0] = a;
		edge[count][1] = b;
		edge[count++][2] = c;
	}
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-1);
	}
	return count;
}
int comparator(const int p1[], const int p2[])
{
	return p1[2] - p2[2];
}
int findParent(int parinte[], int componenta)
{
	if (parinte[componenta] == componenta)
		return componenta;

	return parinte[componenta] = findParent(parinte, parinte[componenta]);
}
void unionSet(int v, int u, int parinte[], int rank[])
{
	u = findParent(parinte, u);
	v = findParent(parinte, v);

	if (rank[u] < rank[v])
		parinte[u] = v;
	else if (rank[u] > rank[v])
		parinte[v] = u;
	else
	{
		parinte[v] = u;
		rank[u]++;
	}
}
void kruskal(int edge[N][3], int size)
{
	qsort(edge, size, sizeof(edge[0]), comparator);
	int parinte[N];
	int rank[N];

	for (int i = 0; i < size; i++)
	{
		parinte[i] = i;
		rank[i] = 0;
	}

	int minCost = 0;
	for (int i = 0; i < size; i++)
	{
		int v1 = findParent(parinte, edge[i][0]);
		int v2 = findParent(parinte, edge[i][1]);
		if (v1 != v2)
		{
			unionSet(v1, v2, parinte, rank);
			printf("%d - %d  %d\n", edge[i][0], edge[i][1], edge[i][2]);
			minCost += edge[i][2];
		}
	}
	printf("\nminCost: %d \n", minCost);
}

int main(int argc,char **argv)
{
	if (argc != 2)
	{
		perror(NULL);
		exit(-1);
	}
	int n = citire(argv[1]);
	kruskal(edge, n);
	return 0;
}



