#include<stdio.h>
#include<stdint.h>
#include"biblio.h"


TTree InitTree(TTree a) {
	for (int i = 0; i <= MAXNODES; i++) { //initial: i<MAXNODES
		a.nodes[i].prim_fiu = 0;
		a.nodes[i].frate_dr = 0;
		a.nodes[i].key = 0;
	}
	a.size = 0;
	return a;
}

TTree InsertNode(TTree a, TNodeRef  parent, TKey key) {
	a.size++;
	a.nodes[a.size].key = key;
	if (parent == 0)
	{
		a.nodes[a.size].frate_dr = 0;
		return a;
	}
	if (a.nodes[parent].prim_fiu == 0)
	{
		a.nodes[parent].prim_fiu = a.size;
	}
	else
	{
		TNodeRef frate = a.nodes[parent].prim_fiu;
		while (a.nodes[frate].frate_dr != 0)
		{
			frate = a.nodes[frate].frate_dr;
		}
		a.nodes[frate].frate_dr = a.size;
	}
	return a;
}

void printArray(TTree a) {
	printf("\nIndex:      ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}
	printf("\nKey:        ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}
	printf("\nPrim_fiu:   ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].prim_fiu);
	}
	printf("\nFrate_dr:   ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].frate_dr);
	}
	printf("\n------------------------------------\n");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, Prim_fiu: %d Frate_dr: %d\n", message, node.key, node.prim_fiu, node.frate_dr);
}

TNodeRef parent(TTree a, TNodeRef noderef) {
	if (noderef <= 0 || noderef > a.size)
		return 0;
	for (int i = 1; i <= a.size; i++)
	{
		TNodeRef copil = a.nodes[i].prim_fiu;
		while (copil != 0)
		{
			if (copil == noderef) return i;
			copil = a.nodes[copil].frate_dr;
		}
	}
	return 0;
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1) return 0;
	return 1;
}

TNodeRef findNodeIndex(TTree a, TNode node) {
	for (uint8_t i = 1; i <= a.size; i++) { // initial: uint8_t i = 0
		if (a.nodes[i].key == node.key && a.nodes[i].prim_fiu == node.prim_fiu && a.nodes[i].frate_dr == node.frate_dr) return i;
	}
	return 0;
}

TNodeRef firstChild(TTree a, TNodeRef index) {
	if (!index || index > a.size) return 0;
	return a.nodes[index].prim_fiu;
}

TKey nodeKey(TTree a, TNodeRef noderef) {
	if (noderef > a.size) return 0;
	return a.nodes[noderef].key;
}

TNode nodeByRef(TTree a, TNodeRef noderef) {
	return a.nodes[noderef];
}

TNodeRef rightSibling(TTree a, TNodeRef noderef) {
	if (!noderef || noderef > a.size) return 0;
	return a.nodes[noderef].frate_dr;
}
/*
TTree deleteNode(TTree a, TNodeRef noderef){
	a.nodes[noderef].key =0;
	a.nodes[noderef].parent = 0;

	for(TNodeRef i = noderef; i<=a.size; i++){// cred ca i=noderef+1
		if(a.nodes[i].parent == noderef){
			a.nodes[i].key =0;
			a.nodes[i].parent =0;
		}
	}

	for(TNodeRef i = noderef; i<=a.size; ){
		if(a.nodes[i].parent ==0 && a.nodes[i].key == 0){
			for(TNodeRef j = i+1; j<=a.size; j++){
				if(a.nodes[j].parent > i) a.nodes[j].parent--;
				a.nodes[j-1] = a.nodes[j];

			}
			a.size--;
		}
		if(a.nodes[i].parent !=0 && a.nodes[i].key !=0) i++;
	}
	printArray(a);

return a;
}
*/
void preordine(TTree a, TNodeRef noderef) //rad->st->restu din dreapta
{
	if (noderef != 0 && noderef <= a.size)
	{
		printf("%d ", a.nodes[noderef].key);
		TNodeRef copil = firstChild(a, noderef);
		preordine(a, copil);
		while ((copil = rightSibling(a, copil)))
		{
			preordine(a, copil);
		}

	}
}

void inordine(TTree a, TNodeRef noderef) //st->rad->dr
{
	if (noderef != 0 && noderef <= a.size)
	{
		TNodeRef copil = firstChild(a, noderef);
		inordine(a, copil);
		printf("%d ", a.nodes[noderef].key);
		while ((copil = rightSibling(a, copil)))
		{
			inordine(a, copil);
		}
	}
}
void postordine(TTree a, TNodeRef noderef)
{
	if (noderef != 0 && noderef <= a.size)
	{
		TNodeRef copil = firstChild(a, noderef);
		postordine(a, copil);
		while ((copil = rightSibling(a, copil)))
		{
			postordine(a, copil);
		}
		printf("%d ", a.nodes[noderef].key);
	}
}




/* alta varianta de preordine
void preordine(TTree a,TNodeRef noderef) //rad->st->dr
{
	if(noderef!=0 && noderef <=a.size)
	{
		printf("%d ",a.nodes[noderef].key);
		preordine(a,firstChild(a,noderef));
		preordine(a,rightSibling(a,noderef));
	}
}
*/

/* alta varianta postordine,trebuia sa iasa inordine si o iesit postordine,nush cum
void postordine(TTree a, TNodeRef noderef)
{
	if(noderef!=0 && noderef <=a.size)
	{
		postordine(a,firstChild(a,noderef));
		printf("%d ",a.nodes[noderef].key);
		postordine(a,rightSibling(a,noderef));
	}
}
*/