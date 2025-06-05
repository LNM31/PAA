#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
typedef struct {
	char cheie;
	int st;
	int dr;
}nod;

typedef int TNodeRef;

typedef struct {
	nod nodes[MAXSIZE+1];
	int size;
}arbore;

arbore init(arbore a);

arbore insert(arbore a, char cheie, int prim_fiu, int frate_dr);// daca avem implementarea cheie,prim fiu,frate dr

arbore insert2(arbore a, char cheie, int parinte);// daca avem implementarea cheie,parinte

void printArray(arbore a,char *nume_fis);

void preordine(arbore a,TNodeRef noderef);

void inordine(arbore a, TNodeRef noderef);

void postordine(arbore a, TNodeRef noderef);