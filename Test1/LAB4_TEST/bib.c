#include<stdio.h>
#include<stdlib.h>
#include"bib.h"

arbore init(arbore a)
{
	a.size = 0;
	for (int i = 0; i <= MAXSIZE; i++)
	{
		a.nodes[i].cheie = '_';
		a.nodes[i].st = 0;
		a.nodes[i].dr = 0;
	}
	return a;
}

arbore insert(arbore a, char cheie, int prim_fiu, int frate_dr) //dupa exemplu din curs
{
	a.size++;
	a.nodes[a.size].cheie = cheie;
	a.nodes[a.size].st = prim_fiu;
	a.nodes[a.size].dr = frate_dr;
	return a;
}

arbore insert2(arbore a, char cheie, int parinte)// aceasi functie de la ex 5 din labu 3
{
	a.size++;
	a.nodes[a.size].cheie = cheie;
	if (parinte == 0)
	{
		a.nodes[parinte].dr = 0;
		return a;
	}
	else if (a.nodes[parinte].st == 0)
	{
		a.nodes[parinte].st = a.size;
	}
	else
	{
		TNodeRef frate = a.nodes[parinte].st;
		while (a.nodes[frate].dr != 0)
		{
			frate = a.nodes[frate].dr;
		}
		a.nodes[frate].dr = a.size;
	}
	return a;
}

void printArray(arbore a,char *nume_fis) {
	FILE* f = fopen(nume_fis, "w");
	if (f == NULL)
	{
		perror("er des fis");
		exit(-1);
	}
	fprintf(f,"\nIndex:      ");
	for (int i = 0; i <= a.size; i++) {
		fprintf(f,"%5d ", i);
	}
	fprintf(f,"\nKey:        ");
	for (int i = 0; i <= a.size; i++) {
		fprintf(f,"%5c ", a.nodes[i].cheie);
	}
	fprintf(f,"\nST:         ");
	for (int i = 0; i <= a.size; i++) {
		fprintf(f,"%5d ", a.nodes[i].st);
	}
	fprintf(f,"\nDR:         ");
	for (int i = 0; i <= a.size; i++) {
		fprintf(f,"%5d ", a.nodes[i].dr);
	}
	fprintf(f,"\n------------------------------------\n");
	if (fclose(f) != 0)
	{
		perror("er inc fis");
		exit(-1);
	}
}

void preordine(arbore a, TNodeRef noderef)// normal trebuie scris in fisier,dar n am mai facut-o
{
	if (noderef != 0 && noderef <= a.size)
	{
		printf("%c ", a.nodes[noderef].cheie);
		preordine(a, a.nodes[noderef].st);
		preordine(a, a.nodes[noderef].dr);
	}
}
void inordine(arbore a, TNodeRef noderef)// normal trebuie scris in fisier,dar n am mai facut-o
{
	if (noderef != 0 && noderef <= a.size)
	{
		inordine(a, a.nodes[noderef].st);
		printf("%c ", a.nodes[noderef].cheie);
		inordine(a, a.nodes[noderef].dr);
	}
}
void postordine(arbore a, TNodeRef noderef)// normal trebuie scris in fisier,dar n am mai facut-o
{
	if (noderef != 0 && noderef <= a.size)
	{
		postordine(a, a.nodes[noderef].st);
		postordine(a, a.nodes[noderef].dr);
		printf("%c ", a.nodes[noderef].cheie);
	}
}


