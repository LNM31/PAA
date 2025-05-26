#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define inf 99999

int matrice[N][N];
int dist[N]; // dist e D ul din tabelul de la curs
int vizitat[N];
int parinte[N]; //parinte e T ul din tabelul de la curs

void init(int matrice[N][N], int size) // e folosita in functia citire
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

int citire(const char* file_name)
{
	FILE* f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error opening file!");
		exit(-1);
	}
	int n;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n!");
		exit(-1);
	}
	int a, b, c;
	while (fscanf(f,"%d %d %d", &a, &b, &c) == 3)
	{
		matrice[a % n][b % n] = c;  //pentru orientat
		//matrice[b % n][a % n] = c;  //pentru neorientat
	}
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
	init(matrice, n);
	return n;
}

void display(int matrice[N][N], int dist[N], int parinte[N], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2c ", 'A'+i);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", dist[i]);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2c ", 'A'+parinte[i]);
	}
	printf("\n\n");
}

void dijkstra(int matrice[N][N],int size,int s) //s - source node
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
			if (vizitat[i] == 0 && (pmin==-1 || dist[i] < dist[pmin]))
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
	display(matrice, dist, parinte, size);
}

void drum(int source, int destination)
{
	int v[N] = { 0 };
	int count = 0;
	int i = destination;
	while (i != source) //posibil loop infinit
	{
		v[count++] = i;
		i = parinte[i];
	}
	printf("%c ", 'A' + source);
	for (int i = count - 1; i >= 0; i--)
	{
		printf("%c ", 'A' + v[i]);
	}
}

int main()
{
	int n = citire("in.txt");
	dijkstra(matrice, n, 0);
	drum(0, 2);
	return 0;
}