#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 50
#define inf 99999
int matrice[N][N];
char info[N];
int l = 0;

int vizitat[N];
int parinte[N];
int dist[N];

int init(int matrice[N][N], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrice[i][j] == 0 && i != j)
			{
				matrice[i][j] = inf;
			}
		}
	}
}
int getIndex(char* info, int l,char c)
{
	for (int i = 0; i < l; i++)
	{
		if (c == info[i])
			return i;
	}
	return 0;
}
int citire(const char* file_name)
{
	FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror(NULL);
		exit(-1);
	}
	int n = 0, c = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror(NULL);
		exit(-1);
	}
	for (int i = 0; i < n; i++)
	{
		if (fscanf(f, " %c", &info[l++]) != 1)
		{
			perror(NULL);
			exit(-1);
		}
	}
	char a, b;
	while (fscanf(f, " %c %c %d", &a, &b, &c) == 3)
	{
		matrice[getIndex(info, l, a)][getIndex(info, l, b)] = c;
	}
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-1);
	}
	init(matrice, n);
	return n;
}
void display(int matrice[N][N], int parinte[N], int dist[N], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%c ", info[i]);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", dist[i]);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%c ", info[parinte[i]]);
	}
}

void dijkstra(int matrice[N][N], int size, int s)
{
	for (int i = 0; i < size; i++)
	{
		vizitat[i] = 0;
		dist[i] = matrice[s][i];
		parinte[i] = s;
	}
	
	vizitat[s] = 1;
	for (int i = 0; i < size - 1; i++)
	{
		int pmin = -1;
		for (int i = 0; i < size; i++)
		{
			if (vizitat[i] == 0 && (pmin == -1 || dist[i] < dist[pmin]))
			{
				pmin = i;
			}
		}
		vizitat[pmin] = 1;
		for (int i = 0; i < size; i++)
		{
			if (vizitat[i] == 0 && dist[pmin] + matrice[pmin][i] < dist[i])
			{
				dist[i] = dist[pmin] + matrice[pmin][i];
				parinte[i] = pmin;
			}
		}
	}
	display(matrice, parinte, dist, size);
}
int main()
{
	int n=citire("in.txt");
	dijkstra(matrice, n, 0);
	return 0;
}