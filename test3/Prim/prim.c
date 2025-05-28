#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 50
#define inf 99999

int matrice[N][N];
int citire(const char* file_name)
{
	FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error opening file!");
		exit(-1);
	}
	int n = 0, a, b, c;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n!");
		exit(-1);
	}
	while (fscanf(f, "%d %d %d", &a, &b, &c) == 3)
	{
		matrice[a % n][b % n] = c;
		matrice[b % n][a % n] = c;
	}
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
	return n;
}
void prim(int matrice[N][N], int size)
{
	int u[N];
	for (int i = 0; i < size; i++)
	{
		u[i] = 0;
	}
	u[0] = 1;
	int min, mini, minj, val = 0;
	for (int pas = 0; pas < size - 1; pas++)
	{
		min = inf; mini = -1; minj = -1;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrice[i][j] && u[i] != u[j] && matrice[i][j] < min)
				{
					min = matrice[i][j];
					mini = i;
					minj = j;
				}
			}
		}
		u[mini] = u[minj] = 1;
		printf("%d - %d   %d\n", mini, minj, matrice[mini][minj]);
		val += matrice[mini][minj];
	}
	printf("\nval: %d\n", val);
}
void bfs(int matrice[N][N], int size, int start)
{
	int vizitat[N] = { 0 };
	int coada[N] = { 0 }, prim = 0, ultim = 0;

	vizitat[start] = 1;
	coada[ultim++] = start;
	while (prim < ultim)
	{
		int curent = coada[prim++];
		printf("%d ", curent);
		for (int i = 0; i < size; i++)
		{
			if (vizitat[i] == 0 && matrice[curent][i] > 0)
			{
				vizitat[i] = 1;
				coada[ultim++] = i;
			}
		}
	}
	printf("\n");
}
void dfs_util(int matrice[N][N], int vizitat[N], int size, int start)
{
	vizitat[start] = 1;
	printf("%d ", start);
	for (int i = 0; i < size; i++)
	{
		if (vizitat[i] == 0 && matrice[start][i] > 0)
			dfs_util(matrice, vizitat, size, i);
	}
}
void dfs(int matrice[N][N], int size, int start)
{
	int vizitat[N] = { 0 };
	dfs_util(matrice, vizitat, size, start);
	printf("\n");
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		perror("err arg!");
		exit(-1);
	}
	int n = citire(argv[1]);
	prim(matrice, n);
	bfs(matrice, n, 0);
	dfs(matrice, n, 0);
	return 0;
}
