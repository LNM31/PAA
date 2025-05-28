#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 50
#define inf 99999

int matrice[N][N];
int dist[N];
int parinte[N];
int vizitat[N];

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
		perror("err desc");
		exit(-1);
	}
	int n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("err read n");
		exit(-1);
	}
	int a, b, c;
	while (fscanf(f, "%d %d %d", &a, &b, &c) == 3)
	{
		matrice[a % n][b % n] = c;
		//matrice[b % n][a % n] = c;

	}
	if (fclose(f) != 0)
	{
		perror("err inc");
		exit(-1);
	}
	init(matrice, n);
	return n;
}
void display(int matrice[N][N], int parinte[N], int dist[N], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2c ", 'A' + i);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", dist[i]);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2c ", 'A' + parinte[i]);
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
int drum(int s, int d)
{
	int drum[N];
	int count = 0;
	int i = d;
	while (i != s)
	{
		drum[count++] = i;
		i = parinte[i];
	}
	drum[count++] = s;
	for (int i = count - 1; i >= 0; i--)
	{
		printf("%c ", 'A' + drum[i]);
	}
}
int main(int argc,char **argv)
{
	if (argc != 2)
	{
		perror("err argc");
		exit(-1);
	}
	int n = citire(argv[1]);
	dijkstra(matrice, n, 0);
	drum(0, 2);
	return 0;
}