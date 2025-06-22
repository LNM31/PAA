#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 27
typedef struct ar {
	struct ar* litere[N];
	int frec;
}nod;

typedef struct {
	char cuvant[256];
	int frec;
}com;

com completari[50]; //pentru cele mai frecvente completari ale prefixelor
int size = 0;

int compare(const void* p1, const void* p2)
{
	const com* e1 = (const com*)p1;
	const com* e2 = (const com*)p2;
	return e2->frec - e1->frec;
}

void init(nod* ref)
{
	for (int i = 0; i < N; i++)
	{
		ref->litere[i] = NULL;
	}
	ref->frec = 0;
}
nod* creareNod()
{
	nod* nou = (nod*)malloc(sizeof(nod));
	if (nou == NULL)
	{
		perror("Error creating node!");
		exit(-1);
	}
	init(nou);
	return nou;
}

void inserareCuvant(nod* radacina, const char* cuvant)
{
	if (radacina == NULL) return;
	nod* curent = radacina;
	for (int i = 0; i < strlen(cuvant); i++)
	{
		curent->frec++;
		char ch = cuvant[i];
		int index = ch - 'A';
		if (curent->litere[index] == NULL)
		{
			curent->litere[index] = creareNod();
		}
		curent = curent->litere[index];
	}
	curent->litere['[' - 'A'] = curent;
	curent->frec++;
}

void afisareRecursiva(nod* radacina, char* cuvant, int nivel)
{
	if (radacina->litere['[' - 'A'] == radacina)
	{
		cuvant[nivel] = '\0';
		printf("%s\n", cuvant);
		if (size < 50)
		{
			strcpy(completari[size].cuvant, cuvant);
			completari[size++].frec = radacina->frec;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (radacina->litere[i] != NULL)
		{
			cuvant[nivel] = 'A' + i;
			afisareRecursiva(radacina->litere[i], cuvant, nivel + 1);
		}
	}
}
void afisare(nod* radacina)
{
	char buffer[256];
	afisareRecursiva(radacina,buffer,0);
}

void prefix_matching(nod* radacina, const char* prefix)
{
	if (radacina == NULL) return;
	nod* curent = radacina;
	for (int i = 0; i < strlen(prefix); i++)
	{
		char ch = prefix[i];
		int index = ch - 'A';
		if (curent->litere[index] == NULL)
		{
			printf("Nu exista cuvant care incepe cu acest index!");
			return;
		}
		curent = curent->litere[index];
	}
	char buffer[256];
	strcpy(buffer, prefix);
	afisareRecursiva(curent, buffer, strlen(buffer));
}
void autocomplete(nod* radacina, const char* prefix, int top)
{
	prefix_matching(radacina, prefix);

	qsort(completari, size, sizeof(com), compare);
	printf("\nTop %d cele mai frecvente:\n",top);
	for (int i = 0; i < size && i < top; i++)
	{
		printf("%s frec:%d\n", completari[i].cuvant, completari[i].frec);
	}
	size = 0;
	printf("\n");
}

void freeArbore(nod* radacina)
{
	if (radacina == NULL) return;
	for (int i = 0; i < 26; i++) //daca punem si 27 ('[') -> ciclu infinit -> stack overflow -> seg fault -> :(
	{
		if (radacina->litere[i] != NULL && radacina->litere[i] != radacina)
		{
			freeArbore(radacina->litere[i]);
		}
	}
	free(radacina);
}
int main()
{
	nod* arbore = creareNod();

	inserareCuvant(arbore, "TIP");
	inserareCuvant(arbore, "TIPA");
	inserareCuvant(arbore, "TIPAR");
	inserareCuvant(arbore, "TIPIC");
	inserareCuvant(arbore, "TIPOGRAF");
	inserareCuvant(arbore, "TIPS");
	inserareCuvant(arbore, "TIPURI");

	inserareCuvant(arbore, "SUN");
	inserareCuvant(arbore, "SUNA");
	inserareCuvant(arbore, "SUNATI");
	inserareCuvant(arbore, "SUR");
	inserareCuvant(arbore, "SURD");
	inserareCuvant(arbore, "SURA");
	inserareCuvant(arbore, "SURPRIZA");

	//afisare(arbore);

	//prefix_matching(arbore, "SUN");

	autocomplete(arbore, "SU", 3);
	autocomplete(arbore, "TIP", 4);

	freeArbore(arbore);
	return 0;
}