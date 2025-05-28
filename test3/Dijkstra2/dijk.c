#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 50
#define inf 99999

char info[N];
int l;

int matrice[N][N];
int dist[N];
int parinte[N];
int vizitat[N];

int getIndex(char *info, int l, char a)
{
	for (int i = 0; i < l; i++)
	{
		if (a == info[i])
			return i;
	}
	return 0;
}
void init(int matrice[N][N], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrice[i][j] == 0 && i != j)
				matrice[i][j] = inf;
		}
	}
}
int citire(const char* file_name)
{
	FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("err open");
		exit(-1);
	}
	int n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("error reading n");
		exit(-1);
	}
	for (int i = 0; i < n; i++)
	{
		if (fscanf(f, " %c", &info[l++]) != 1)
		{
			perror("err reading char");
			exit(-1);
		}
	}
	char a, b;
	int c;
	while (fscanf(f," %c %c %d", &a, &b, &c) == 3)
	{
		matrice[getIndex(info, l, a) % n][getIndex(info, l, b) % n] = c;
	}
	if (fclose(f) != 0)
	{
		perror("err closing");
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
	printf("\n");
}
void dijkstra(int matrice[N][N], int size,int s)
{
	for (int i = 0; i < size; i++)
	{
		dist[i] = matrice[s][i];
		parinte[i] = s;
		vizitat[i] = 0;
	}
	vizitat[s] = 0;
	for (int pas = 0; pas < size - 1; pas++)
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