#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEAMNAMESIZE 100

typedef struct node {
    int index;
    char winner[TEAMNAMESIZE];
    struct node *home;
    struct node *away;
} Node;

Node *newNode(int index, char *winner) {
    Node *aux = malloc(1 * sizeof(Node));
    aux->index = index;
    strcpy(aux->winner, winner);
    aux->home = NULL;
    aux->away = NULL;
    return aux;
}

void addNode(Node *match, int index, char *winner, int parent) {
    if (match != NULL) 
    {
        if (match->index == parent) 
        {
            if (match->home == NULL) 
            {
                match->home = newNode(index, winner);
            } 
            else 
            {
                if (match->away == NULL) 
                {
                    match->away = newNode(index, winner);
                }
            }
        } 
        else 
        {
            addNode(match->home, index, winner, parent);
            addNode(match->away, index, winner, parent);
        }
    }
}

void postorder(Node *match) {
    if (match->home != NULL && match->away != NULL) {
        postorder(match->home);
        postorder(match->away);
        printf("%s vs %s won %s\n", match->home->winner, match->away->winner, match->winner);
    }
}

void printTeamHistory(Node *match, char *team) {
    if (match->home != NULL && match->away != NULL) {
        if (strcmp(match->home->winner, team) == 0) {
            printTeamHistory(match->home, team);
        } else {
            if (strcmp(match->away->winner, team) == 0) {
                printTeamHistory(match->away, team);
            }
        }
        printf("%s vs %s won %s\n", match->home->winner, match->away->winner, match->winner);
    }
}

void searchTeamMatch(Node *match, char *team) {
    if (match != NULL) {
        if (strcmp(match->winner, team) == 0) {
            printTeamHistory(match, team);
        } else {
            searchTeamMatch(match->home, team);
            searchTeamMatch(match->away, team);
        }
    }
}

void countMatches(Node *match, int *count) {
    if (match->home != NULL && match->away != NULL) {
        *count = *count + 1;
        countMatches(match->home, count);
        countMatches(match->away, count);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect arguments\n");
        return -1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    int index, parent;
    char team[TEAMNAMESIZE];
    fscanf(file, "%d %s %d", &index, team, &parent);
    Node *championship = newNode(index, team);
    while (fscanf(file, "%d %s %d", &index, team, &parent) == 3) {
        addNode(championship, index, team, parent);
    }
    printf("Championship match history:\n");
    postorder(championship);
    printf("\nTeamE match history:\n");
    searchTeamMatch(championship, "TeamE");
    int count = 0;
    countMatches(championship, &count);
    printf("\nThere are minimum %d matches\n", count);
    printf("\nWinner match history:\n");
    searchTeamMatch(championship, championship->winner);
    fclose(file);
    return 0;
}
