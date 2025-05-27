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
void prim(int matrice[N][N], int size)
{
	int u[N];
	for (int i = 0; i < size; i++)
	{
		u[i] = 0;
	}
	u[0] = 1;
	int min,mini,minj,val=0;
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
