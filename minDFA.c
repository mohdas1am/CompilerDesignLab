#include <stdio.h>

#define MAX 20

int n;                        // Number of states
int symbols;                  // Number of symbols
int transition[MAX][MAX];     // DFA transition table
int final[MAX];               // 1 if state is accepting, else 0

int distinguishable[MAX][MAX];

void markDistinguishablePairs() {
    // Step 1: Mark pairs where one is final and the other is not
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((final[i] && !final[j]) || (!final[i] && final[j])) {
                distinguishable[i][j] = 1;
            }
        }
    }

    // Step 2: Iteratively mark distinguishable pairs
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (!distinguishable[i][j]) {
                    for (int sym = 0; sym < symbols; sym++) {
                        int ti = transition[i][sym];
                        int tj = transition[j][sym];

                        if (ti == tj) continue;

                        int a = ti > tj ? ti : tj;
                        int b = ti > tj ? tj : ti;

                        if (distinguishable[a][b]) {
                            distinguishable[i][j] = 1;
                            changed = 1;
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);
}

void printEquivalentStates() {
    printf("\nEquivalent States (Can be Merged):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (!distinguishable[i][j]) {
                printf("State %d and State %d are equivalent.\n", i, j);
            }
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &symbols);

    printf("\nEnter DFA transition table:\n");
    for (int i = 0; i < n; i++) {
        for (int sym = 0; sym < symbols; sym++) {
            printf("From state %d on symbol %d go to: ", i, sym);
            scanf("%d", &transition[i][sym]);
        }
    }

    printf("\nEnter final (accepting) states (0 or 1 for each state):\n");
    for (int i = 0; i < n; i++) {
        printf("Is state %d accepting? (1/0): ", i);
        scanf("%d", &final[i]);
    }

    // Initialize table
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            distinguishable[i][j] = 0;

    markDistinguishablePairs();
    printEquivalentStates();

    return 0;
}

