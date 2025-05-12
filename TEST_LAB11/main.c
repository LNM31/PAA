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

void DFS_REALLY(int matrice[N][N],int visited[], int start)
{
	visited[start] = 1;
	printf("%d ", start);
	for (int i = 0; i < N; i++)
	{
		if (matrice[start][i] == 1 && visited[i] == 0)
		{
			DFS_REALLY(matrice,visited, i);
		}
	}
}
void DFS(int matrice[N][N], int start)
{
	int visited[N] = { 0 };
	DFS_REALLY(matrice,visited,start);
	printf("\n");
}


void ShortestPath(int matrice[N][N], int start,int finish) //with BFS
{
	int vizitat[N] = { 0 };
	int parinte[N] = { 0 };
	int coada[N], prim = 0, ultim = 0;
	int size = 0;  //size of parents

	vizitat[start] = 1;
	parinte[start] = -1;
	coada[ultim++] = start;

	while (prim < ultim)
	{
		int current = coada[prim++];

		for (int i = 0; i < N; i++)
		{
			if (matrice[current][i] == 1 && vizitat[i] == 0)
			{
				vizitat[i] = 1;
				parinte[i] = current;
				size = i + 1;
				coada[ultim++] = i;
			}
		}
	}

	int drum[N] = { 0 };
	int i = finish;// se incepe de la sfarsit ca sa aflam drumul

	size = 0;//size of drum
	drum[size++] = i;

	while (i != start)
	{
		i = parinte[i];
		drum[size++] = i;
	}

	for (int j = size - 1; j >= 0; j--)
	{
		printf("%d ", drum[j]);
	}
	printf("\n");
}

int NrComponenteConexe(int matrice[N][N])
{
	int vizitat[N] = { 0 };
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrice[i][j] == 1 && vizitat[j] == 0)
			{
				count++;
				DFS_REALLY(matrice, vizitat, i);
			}
		}
	}
	return count;
}
int main()
{
	int n;
	init();
	n=citire("in.txt");
	printf("Matrice de adiacenta: \n");
	display(12);
	printf("BFS: ");
	BFS(matrice, 4);
	printf("DFS: ");
	DFS(matrice, 4);
	printf("Cel mai scurt drum: ");
	ShortestPath(matrice,0,11);
	printf("Numar componente conexe: %d\n",NrComponenteConexe(matrice));
	return 0;
}