#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_RULES 10
#define MAX_LEN 10
char productions[MAX_RULES][MAX_LEN], first[MAX_RULES][MAX_LEN], follow[MAX_RULES][MAX_LEN];
int num_productions;
int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z'); }
void findFirst(char symbol, char result[]) {
    if (!isNonTerminal(symbol)) {
        strncat(result, &symbol, 1);
        return;    }
    for (int i = 0; i < num_productions; i++) {
        if (productions[i][0] == symbol) {
            if (!isNonTerminal(productions[i][3])) {
                strncat(result, &productions[i][3], 1);
            } else {
                findFirst(productions[i][3], result);
            }        }    }  }
void findFollow(char symbol, char result[]) {
    if (productions[0][0] == symbol) {
        strcat(result, "$");    }
    for (int i = 0; i < num_productions; i++) {
        for (int j = 3; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == symbol) {
                if (productions[i][j + 1] != '\0') {
                    char firstNext[MAX_LEN] = "";
                    findFirst(productions[i][j + 1], firstNext);
                    strcat(result, firstNext);
                } else {
                    char followLHS[MAX_LEN] = "";
                    findFollow(productions[i][0], followLHS);
                    strcat(result, followLHS);    }    }   }  }  }

void removeDuplicates(char *set) {
    int i, j, k;
    int len = strlen(set);
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len;) {
            if (set[i] == set[j]) {
                for (k = j; k < len; k++) {
                    set[k] = set[k + 1];
                }
                len--;
            } else {
                j++;     }     }  }  }
int main() {
 printf("Enter the number of productions: ");
    scanf("%d", &num_productions);
    printf("Enter the grammar rules (Format: A->Bc, S->aB, etc.):\n");
    for (int i = 0; i < num_productions; i++) {
        scanf("%s", productions[i]);
    }
    printf("\nFIRST Sets:\n");
    for (int i = 0; i < num_productions; i++) {
        char result[MAX_LEN] = "";
        findFirst(productions[i][0], result);
        removeDuplicates(result);
        printf("FIRST(%c) = { %s }\n", productions[i][0], result);
    }
    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < num_productions; i++) {
        char result[MAX_LEN] = "";
        findFollow(productions[i][0], result);
        removeDuplicates(result);
        printf("FOLLOW(%c) = { %s }\n", productions[i][0], result);
    }
    return 0;
}
