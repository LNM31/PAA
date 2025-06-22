#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N 50
int matrice[N][N];
int w[N][N];
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
    printf("\n");
}
int citire(const char* file_name)
{
    FILE* f = fopen(file_name, "r");
    if (f == NULL)
    {
        perror("Erreur");
        exit(1);
    }
    int n = 0;
    if (fscanf(f, "%d", &n) != 1) {
        perror("Error reading n!");
        exit(-1);
    }
    int a, b;
    while (fscanf(f, "%d %d", &a, &b) == 2) {
        matrice[a % n][b % n] = 1;
    }
    if (fclose(f) != 0)
    {
        perror("Erreur");
        exit(1);
    }
    return n;
}
void warshall(int matrice[N][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrice[i][j])
                w[i][j] = 1;
        }
    }
    for (int k = 0; k < size; k++)
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (w[i][j] == 0)
                    w[i][j] = w[i][k] && w[k][j];
}
void f1(int w[N][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("furnizorul %d este afectat de: ",i);
        for (int j = 0; j < size; j++)
        {
            if (w[i][j])
                printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}
void vulnerabil(int w[N][N], int size)
{
    int maxim = 0, maxi = 0;
    for (int i = 0; i < size; i++)
    {
        int aux = 0;
        for (int j = 0; j < size; j++)
        {
            if (w[i][j])
                aux++;
        }
        if (aux > maxim)
        {
            maxim = aux;
            maxi = i;
        }
    }
    printf("Cel mai vulnerabil furnizor este %d cu %d dependente\n",maxi,maxim);
}
int main()
{
    int n = citire("in.txt");
    warshall(matrice, n);
    
    f1(w, n);
    vulnerabil(w, n);
    display(w, n);
    return 0;
}