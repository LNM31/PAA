#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 30
#define inf 99999

int matrice[N][N];

int citire(const char* file_name)
{
	FILE *f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror(NULL);
		exit(-1);
	}
	int n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror(NULL);
		exit(-1);
	}
	int a, b, c;
	while (fscanf(f,"%d %d %d", &a, &b, &c) == 3)
	{
		matrice[a % n][b % n] = c;
		matrice[b % n][a % n] = c;
	}
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-1);
	}
	return n;
}

int minKey(int cheie[N], int vizitat[N], int size)
{
	int minim = inf, min_index = 0;
	for (int i = 0; i < size; i++)
	{
		if (vizitat[i] == 0 && cheie[i] < minim)
		{
			minim = cheie[i];
			min_index = i;
		}
	}
	return min_index;
}

void display(int matrice[N][N],int parinte[N], int size)
{
	int val = 0;
	printf("muchie  val\n");
	for (int i = 1; i < size; i++)
	{
		printf("%d - %d   %d\n", parinte[i], i, matrice[parinte[i]][i]);
		val += matrice[parinte[i]][i];
	}
	printf("\nval: %d\n", val);
}

void prim(int matrice[N][N], int size)
{
	int cheie[N];
	int parinte[N];
	int vizitat[N];

	for (int i = 0; i < size; i++)
	{
		cheie[i] = inf;
		vizitat[i] = 0;
	}

	cheie[0] = 0;
	parinte[0] = -1;

	for (int i = 0; i < size - 1; i++)
	{
		int u = minKey(cheie, vizitat, size);
		vizitat[u] = 1;
		for (int v = 0; v < size; v++)
		{
			if (matrice[u][v] && vizitat[v] == 0 && matrice[u][v] < cheie[v])
			{
				cheie[v] = matrice[u][v];
				parinte[v] = u;
			}
		}
	}
	display(matrice, parinte, size);
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		perror("Error number of arguments");
		exit(-1);
	}
	int n = citire(argv[1]);
	prim(matrice, n);
	return 0;
}
