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
void kruskal(int matrice[N][N], int size)
{
	int s[N];
	for (int i = 0; i < size; i++)
	{
		s[i] = i;
	}
	int min, mini, minj, val = 0;
	for (int pas = 0; pas < size - 1; pas++)
	{
		min = inf; mini = -1; minj = -1;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrice[i][j] && s[i] != s[j] && matrice[i][j] < min)
				{
					min = matrice[i][j];
					mini = i;
					minj = j;
				}
			}
		}
		int from = s[minj];
		int to = s[mini];
		for (int i = 0; i < size; i++)
		{
			if (s[i] == from)
			{
				s[i] = to;
			}
		}
		printf("%d - %d   %d\n", mini, minj, matrice[mini][minj]);
		val += matrice[mini][minj];
	}
	printf("\nval: %d\n", val);
}

int main(int argc,char **argv)
{
	if (argc != 2)
	{
		perror("err arg!");
		exit(-1);
	}
	int n = citire(argv[1]);
	kruskal(matrice, n);
	return 0;
}



