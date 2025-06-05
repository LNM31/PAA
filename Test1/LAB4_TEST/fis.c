#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bib.h"
void citire1(arbore* a, char* nume_fis)
{
	FILE* f = fopen(nume_fis, "r");
	if (f == NULL)
	{
		perror("er des fis");
		exit(-1);
	}
	char b;
	int c, d;
	while (fscanf(f, " %c %d %d", &b, &c, &d) == 3)
	{
		*a = insert(*a, b, c, d);
	}
	if (fclose(f) != 0)
	{
		perror("er inc fis");
		exit(-1);
	}
}
void citire2(arbore* a, char* nume_fis)
{
	FILE* f = fopen(nume_fis, "r");
	if (f == NULL)
	{
		perror("er des fis");
		exit(-1);
	}
	char b;
	int c;
	while (fscanf(f, " %c %d", &b, &c) == 2)
	{
		*a = insert2(*a, b, c);
	}
	if (fclose(f) != 0)
	{
		perror("er inc fis");
		exit(-1);
	}
}
int main(int argc,char **argv)
{
	arbore a = {0};
	a = init(a);
	//citire1(&a,argv[1]);
	citire2(&a, argv[1]);
	printArray(a, argv[2]);
	printf("preordine: ");
	preordine(a,1);
	printf("\ninordine: ");
	inordine(a, 1);
	printf("\npostordine: ");
	postordine(a, 1);
	return 0;
}
/*  citire1 cheie,prim fiu,frate dreapta
A 2 0
B 5 3
C 8 4
D 9 0
E 0 6
F 0 7
G 0 0
H 0 0
I 0 10
J 0 0
*/