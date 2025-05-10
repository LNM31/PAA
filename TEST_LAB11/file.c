#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#define N 20
int matrice[N][N];
//cautare prin cuprindere si gasirea drumului cel mai scurt
void init(int** matrice, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrice[i][j] = 0;
		}
	}
}
void display(int** matrice, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
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
		x--;
	}
	if (fclose(f) != 0)
	{
		perror(NULL);
		exit(-2);
	}
	return n;
}
