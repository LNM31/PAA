#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 50
#define inf 99999

int matrice[N][N];
void display(int matrice[N][N], int size)
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
	}
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
	return n;
}
int getGradIntern(int matrice[N][N], int size, int nod)
{
	int grad = 0;
	for (int i = 0; i < size; i++)
	{
		if (matrice[i][nod] > 0)
			grad++;
	}
	return grad;
}
int getGradExtern(int matrice[N][N], int size, int nod)
{
	int grad = 0;
	for (int i = 0; i < size; i++)
	{
		if (matrice[nod][i] > 0)
			grad++;
	}
	return grad;
}
int func(int matrice[N][N], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (getGradIntern(matrice, size, i) == getGradExtern(matrice, size, i))
			printf("%c ", 'A' + i);
	}
}


int sumaies(int matrice[N][N], int size, int nod)
{
	int suma = 0;
	for (int i = 0; i < size; i++)
	{
		if (matrice[nod][i] > 0)
			suma+=matrice[nod][i];
	}
	return suma;
}
int sumaintra(int matrice[N][N], int size, int nod)
{
	int suma = 0;
	for (int i = 0; i < size; i++)
	{
		if (matrice[i][nod] > 0)
			suma += matrice[i][nod];
	}
	return suma;
}
int func2(int matrice[N][N], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (sumaintra(matrice, size, i) < sumaies(matrice, size, i))
			printf("%c ", 'A' + i);
	}
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		perror("err arg!");
		exit(-1);
	}
	int n = citire(argv[1]);
	display(matrice, n);
	func(matrice, n);
	printf("\n");
	func2(matrice, n);
	return 0;
}



