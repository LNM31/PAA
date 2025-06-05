#pragma once
#include<stdint.h>

#define MAXNODES 100

typedef uint8_t TKey;

typedef struct {
	uint8_t prim_fiu;
	uint8_t frate_dr;
	TKey key;
}TNode;

typedef uint8_t TNodeRef;

typedef struct {
	TNode nodes[MAXNODES + 1]; //initial:TNode nodes[MAXNODES];
	uint8_t size; //tree size = number of nodes in the tree	
}TTree;

TTree InitTree(TTree a);

TTree InsertNode(TTree a, TNodeRef  parent, TKey key);

void printArray(TTree a);

void printNode(TNode node, char* message);

TNodeRef parent(TTree a, TNodeRef noderef);

TNodeRef getRoot(TTree a);// nu a fost declarata

TNodeRef findNodeIndex(TTree a, TNode node); //nu a fost definita

TKey nodeKey(TTree a, TNodeRef noderef);

TNode nodeByRef(TTree a, TNodeRef noderef);

TNodeRef firstChild(TTree a, TNodeRef noderef);

TNodeRef rightSibling(TTree a, TNodeRef noderef);

TTree deleteNode(TTree a, TNodeRef noderef);


void preordine(TTree a, TNodeRef noderef);
void inordine(TTree a, TNodeRef noderef);
void postordine(TTree a, TNodeRef nodref);