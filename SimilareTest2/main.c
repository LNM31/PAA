#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 30

int matrice[N][N];

void display(int size)
{
	printf("Matrice de adiacenta:\n");
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
int citire(const char *file_name)
{
	FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error fopen");
		exit(-1);
	}
	int n=0; //number of nodes to be returned,initially 0
	int a, b;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n");
		exit(-3);
	}
	while (fscanf(f, "%d %d", &a, &b) == 2)
	{
		matrice[a%n][b%n] = 1;  //% for avoiding buffer overflow
		matrice[b%n][a%n] = 1;
	}
	if (fclose(f) != 0)
	{
		perror("Error fclose");
		exit(-2);
	}
	return n;
}

void BFS(int matrice[N][N], int start)
{
	int vizitat[N] = { 0 };
	int coada[N] = { 0 }, prim = 0, ultim = 0;

	vizitat[start] = 1;
	coada[ultim++] = start;

	while (prim < ultim)
	{
		int curent = coada[prim++];
		printf("%d ", curent);
		for (int i = 0; i < N; i++)
		{
			if (matrice[curent][i] == 1 && vizitat[i] == 0)
			{
				vizitat[i] = 1;
				coada[ultim++] = i;
			}
		}
	}
	printf("\n");
}

void DFS_REALLY(int matrice[N][N],int vizitat[N], int start)
{
	vizitat[start] = 1;
	printf("%d ", start);
	for (int i = 0; i < N; i++)
	{
		if (matrice[start][i] == 1 && vizitat[i] == 0)
		{
			DFS_REALLY(matrice, vizitat, i);
		}
	}
}
void DFS(int matrice[N][N], int start)
{
	int vizitat[N] = { 0 };
	DFS_REALLY(matrice, vizitat, start);
	printf("\n");
}

void ShortestPath(int matrice[N][N], int start, int finish)
{
	int vizitat[N] = { 0 };
	int coada[N], prim = 0, ultim = 0;
	int parinte[N] = { 0 };

	vizitat[start] = 1;
	coada[ultim++] = start;
	parinte[start] = -1;

	while (prim < ultim)
	{
		int curent = coada[prim++];

		for (int i = 0; i < N; i++)
		{
			if (matrice[curent][i] == 1 && vizitat[i] == 0)
			{
				vizitat[i] = 1;
				coada[ultim++] = i;
				parinte[i] = curent;
			}
		}
	}

	int drum[N] = { 0 };
	int size = 0;
	int i = finish;
	drum[size++] = i;
	while (i != start)
	{
		drum[size++] = parinte[i];
		i = parinte[i];
	}
	printf("Drumul cel mai scurt de la %d la %d: ", start, finish);
	for (int i = size-1; i >=0; i--)
	{
		printf("%d ", drum[i]);
	}
	printf("\n");
}

int ComponenteConexe(int matrice[N][N],int size)
{
	int count=0;
	int vizitat[N] = { 0 };
	printf("Parcurgere totala in adancime: ");
	for (int i = 0; i < size; i++)
	{
		if (vizitat[i] == 0)
		{
			count++;
			DFS_REALLY(matrice, vizitat, i);
		}
	}
	return count;
}

void BFSUtil(int matrice[N][N],int vizitat[N], int start)
{
	int coada[N] = { 0 }, prim = 0, ultim = 0;

	vizitat[start] = 1;
	coada[ultim++] = start;

	while (prim < ultim)
	{
		int curent = coada[prim++];
		printf("%d ", curent);
		for (int i = 0; i < N; i++)
		{
			if (matrice[curent][i] == 1 && vizitat[i] == 0)
			{
				vizitat[i] = 1;
				coada[ultim++] = i;
			}
		}
	}
	printf("\n");
}
void BFSTotal(int matrice[N][N], int size)
{
	int vizitat[N] = { 0 };
	printf("Parcurgere totala in cuprindere: \n");
	for (int i = 0; i < size; i++)
	{
		if (vizitat[i] == 0)
		{
			BFSUtil(matrice, vizitat, i);
		}
	}
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		perror("Invalid number of arguments");
		exit(-4);
	}
	const int size = citire(argv[1]);
	display(size);
	
	printf("BFS: ");
	BFS(matrice, 8);

	printf("DFS: ");
	DFS(matrice, 21);

	ShortestPath(matrice, 2, 4);

	BFSTotal(matrice, size);

	printf("\nComponenteConexe: %d\n", ComponenteConexe(matrice,size));
	return 0;
}