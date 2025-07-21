#include <stdio.h>
#include <stdlib.h>

int n, symbols;
int arr[10][10];            // Epsilon closures
int table[10][10][10];      // ε-NFA transitions
int nfaResult[10][10][10];  // Final NFA transitions

// DFA
int dfa[100][10];           // DFA transition table
int dfaStates[100][10];     // DFA states as sets of NFA states
int dfaStateCount = 0;

int stateSetExists(int stateSet[]) {
    for (int i = 0; i < dfaStateCount; i++) {
        int same = 1;
        for (int j = 0; j < n; j++) {
            if (dfaStates[i][j] != stateSet[j]) {
                same = 0;
                break;
            }
        }
        if (same)
            return i; // DFA state index
    }
    return -1;
}

int addStateSet(int stateSet[]) {
    for (int i = 0; i < n; i++)
        dfaStates[dfaStateCount][i] = stateSet[i];
    return dfaStateCount++;
}

void nfaToDfa() {
    int queue[100][10];
    int front = 0, rear = 0;

    int startState[10] = {0};
    startState[0] = 1; // Assuming NFA start state is 0

    rear++;
    for (int i = 0; i < n; i++)
        queue[rear][i] = startState[i];
    addStateSet(startState);

    while (front < rear) {
        front++;
        int *currentSet = queue[front];
        int currentStateNum = stateSetExists(currentSet);

        for (int sym = 0; sym < symbols; sym++) {
            int newSet[10] = {0};
            for (int i = 0; i < n; i++) {
                if (currentSet[i]) {
                    for (int j = 0; j < n; j++) {
                        if (nfaResult[i][sym][j])
                            newSet[j] = 1;
                    }
                }
            }

            int existingState = stateSetExists(newSet);
            int targetStateNum;

            if (existingState != -1) {
                targetStateNum = existingState;
            } else {
                rear++;
                for (int i = 0; i < n; i++)
                    queue[rear][i] = newSet[i];
                targetStateNum = addStateSet(newSet);
            }

            dfa[currentStateNum][sym] = targetStateNum;
        }
    }

    printf("\nDFA TRANSITION TABLE:\n");
    for (int i = 0; i < dfaStateCount; i++) {
        printf("DFA State %d (", i);
        for (int k = 0; k < n; k++)
            if (dfaStates[i][k]) printf("%d", k);
        printf("): ");
        for (int sym = 0; sym < symbols; sym++) {
            printf(" on %d -> %d ", sym, dfa[i][sym]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter no of states: ");
    scanf("%d", &n);

    printf("Enter no. of symbols: ");
    scanf("%d", &symbols);

    int flag;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                arr[i][j] = 1;
            } else {
                printf("Is there an epsilon transition from %d to %d(0/1): ", i, j);
                scanf("%d", &flag);
                arr[i][j] = (flag == 1) ? 1 : 0;
            }
        }
    }

    for (int sym = 0; sym < symbols; sym++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("Transition from %d to %d by symbol %d (0/1) : ", i, j, sym);
                scanf("%d", &table[i][sym][j]);
            }
        }
    }

    // Compute epsilon closures (Floyd-Warshall)
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][k] == 1 && arr[k][j] == 1) {
                    arr[i][j] = 1;
                }
            }
        }
    }

    printf("\nNFA (after removing epsilon transitions):\n");

    // Convert ε-NFA to NFA
    for (int states = 0; states < n; states++) {
        for (int sym = 0; sym < symbols; sym++) {
            int nfaTable[10] = {0};
            for (int i = 0; i < n; i++) {
                if (arr[states][i]) {
                    for (int target = 0; target < n; target++) {
                        if (table[i][sym][target]) {
                            for (int j = 0; j < n; j++) {
                                if (arr[target][j]) {
                                    nfaTable[j] = 1;
                                }
                            }
                        }
                    }
                }
            }
            printf("From %d on symbol %d { ", states, sym);
            for (int i = 0; i < n; i++) {
                if (nfaTable[i]) {
                    printf("%d ", i);
                    nfaResult[states][sym][i] = 1;
                }
            }
            printf("}\n");
        }
    }

    // NFA to DFA Conversion:
    printf("\nNFA to DFA Conversion:\n");
    nfaToDfa();

    return 0;
}

