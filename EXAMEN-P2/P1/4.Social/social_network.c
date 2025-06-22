#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 50


int matrice[N][N];

int citire(const char* file_name)
{
	FILE *f = fopen(file_name, "r");
	if (f == NULL)
	{
		perror("Error opening file!");
		exit(-1);
	}
	int n = 0;
	if (fscanf(f, "%d", &n) != 1)
	{
		perror("Error reading n!");
		exit(-1);
	}
	int a = 0, b = 0;
	while (fscanf(f, "%d %d", &a, &b) == 2)
	{
		matrice[a % n][b % n] = 1;
		matrice[b % n][a % n] = 1;
	}
	if (fclose(f) != 0)
	{
		perror("Error closing file!");
		exit(-1);
	}
	return n;
}

void DFS_UTIL(int matrice[N][N], int vizitat[N], int size,int *contor,int afiseaza, int start)
{
	vizitat[start] = 1;
	if(afiseaza) printf("%d ", start);
	for (int i = 0; i < size; i++)
	{
		if (matrice[start][i] && vizitat[i] == 0)
		{
			(*contor)++;
			DFS_UTIL(matrice, vizitat, size, contor,afiseaza, i);
		}
	}
}
int componenteConexe(int matrice[N][N], int size,int *max_contor,int ignorat,int afiseaza)
{
	int vizitat[N] = { 0 };
	int count = 0;// nr de grupuri
	int contor = 1;// nr de noduri din fiecare grup
	if (max_contor != NULL)
		*max_contor = 0;
	for (int i = 0; i < size; i++)
	{
		contor = 1;
		if (vizitat[i] == 0 && i!=ignorat)
		{
			if(afiseaza) printf("Grupul %d: ", count);
			count++;
			DFS_UTIL(matrice, vizitat, size, &contor,afiseaza, i);
			if(afiseaza) printf("\n");
			if (max_contor!=NULL && contor > *max_contor)
				*max_contor = contor;
		}
	}
	return count;
}

void func(int matrice[N][N], int aux[N][N],int nod,int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			aux[i][j] = matrice[i][j];
		}
	}
	for (int i = 0; i < size; i++)
	{
		aux[nod][i] = 0;
		aux[i][nod] = 0;
	}
}
void noduriArticulatie(int matrice[N][N], int size)
{
	const int comp_conexe_normal = componenteConexe(matrice, size, NULL,-1,0);
	int aux[N][N] = { 0 };
	printf("Puncte articulatie: ");
	for (int i = 0; i < size; i++)
	{
		func(matrice, aux, i, size);
		int comp_conexe_nod = componenteConexe(aux, size, NULL,i,0);
		if (comp_conexe_nod > comp_conexe_normal)
			printf("%d ", i);
	}
	printf("\n");
}
int main()
{
	int n = citire("in.txt");
	int max_contor = 0;
	int count = componenteConexe(matrice, n, &max_contor,-1,1);

	printf("In total %d grupuri separate\n", count);
	printf("Cel mai mare grup are %d persoane\n", max_contor);
	noduriArticulatie(matrice, n);
	 
	return 0;
}