#include<stdio.h>
#include<stdlib.h>
#define N 64
//reprezentam un arbore binar complet printr un vector
int arbore[2*N] = {-1,1,1,8,1,3,6,8,1,2,3,4,5,6,7,8 };
int size = 15; //nr_noduri arbore
int radacina = 1;

char etapa[10][20] = { "finala","semifinala","sferturi","optimi","saisprezecimi" };

void preordine(int arbore[],int noderef)
{
	if (noderef > size || noderef <=0)
		return;

	printf("%d ", arbore[noderef]);
	preordine(arbore, 2 * noderef);
	preordine(arbore, 2 * noderef + 1);
}

void each_round(int arbore[], int noderef,int nivel)
{
	if (noderef > size || noderef <=0)
		return;

	printf("nodul %d a ajuns in %s\n", arbore[noderef],etapa[nivel]);
	each_round(arbore, 2 * noderef, nivel + 1);
	each_round(arbore, 2 * noderef + 1, nivel + 1);
}

int frate(int arbore[], int noderef)
{
	if (noderef > size || noderef <= 0)
		return 0;

	if (noderef % 2 == 0)
		return arbore[noderef + 1];
	else return arbore[noderef - 1];
}
void path(int arbore[], int noderef,int node_x,int nivel)
{
	if (noderef > size || noderef <= 0)
		return;
	if (arbore[noderef] == node_x)
	{
		if (noderef == radacina)
			printf("nodul %d a ajuns in %s\n", node_x, etapa[nivel]);
		else
			printf("nodul %d a ajuns in %s cu nodul %d\n", node_x, etapa[nivel], frate(arbore,noderef));
	}
	path(arbore, 2 * noderef,node_x,nivel+1);
	path(arbore, 2 * noderef + 1,node_x,nivel+1);
}
int minim_meciuri_jucate(int size)
{
	return (size - 1)/2;
}
void road_to_final(int arbore[])
{
	printf("Road To Final:\n");
	path(arbore, radacina, arbore[radacina], 0);
}
int main()
{
	//preordine(arbore, radacina);
	each_round(arbore, radacina, 0);

	printf("\n");
	path(arbore, radacina, 8, 0);

	printf("\n");
	printf("minim meciuri jucate:%d\n", minim_meciuri_jucate(size));

	printf("\n");
	road_to_final(arbore);

	return 0;
}