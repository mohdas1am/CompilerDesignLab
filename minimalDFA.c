#include <stdio.h>

#define MAX 20

int n; // number of states
int trans[MAX][2]; // transitions: 0 for 'a', 1 for 'b'
int final[MAX]; // 1 if final state
int table[MAX][MAX]; // 1 if states are distinguishable
int group[MAX]; // group[i] = group number of state i
int usedGroup[MAX]; // tracks final group for output

int is_final_diff(int a, int b) {
    return (final[a] != final[b]);
}

int main() {
    int i, j, k, f, numFinal;

    // Input
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter transitions (state a_target b_target):\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &f, &trans[i][0], &trans[i][1]);
    }

    printf("Enter number of final states: ");
    scanf("%d", &numFinal);
    printf("Enter final states: ");
    for (i = 0; i < numFinal; i++) {
        scanf("%d", &f);
        final[f] = 1;
    }

    // Step 1: Mark final/non-final distinguishable pairs
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (is_final_diff(i, j))
                table[i][j] = 1;
        }
    }

    // Step 2: Iterative marking
    int changed;
    do {
        changed = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < i; j++) {
                if (table[i][j]) continue;
                for (k = 0; k < 2; k++) {
                    int p = trans[i][k];
                    int q = trans[j][k];
                    if (p == q) continue;
                    int x = (p > q) ? p : q;
                    int y = (p > q) ? q : p;
                    if (table[x][y]) {
                        table[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Create equivalence classes
    int gnum = 0;
    for (i = 0; i < n; i++) group[i] = -1;

    for (i = 0; i < n; i++) {
        if (group[i] == -1) {
            group[i] = gnum;
            for (j = i + 1; j < n; j++) {
                int x = i > j ? i : j;
                int y = i > j ? j : i;
                if (!table[x][y])
                    group[j] = gnum;
            }
            gnum++;
        }
    }

    // Output equivalent classes
    printf("\nEquivalent State Groups (Equivalence Classes):\n");
    for (i = 0; i < gnum; i++) {
        printf("Group %d: { ", i);
        for (j = 0; j < n; j++) {
            if (group[j] == i) printf("%d ", j);
        }
        printf("}\n");
    }

    // Build minimized transition table
    int minTrans[MAX][2] = {0};
    int minFinal[MAX] = {0};

    for (i = 0; i < gnum; i++) {
        for (j = 0; j < n; j++) {
            if (group[j] == i) {
                minTrans[i][0] = group[trans[j][0]];
                minTrans[i][1] = group[trans[j][1]];
                if (final[j]) minFinal[i] = 1;
                break;
            }
        }
    }

    // Output minimized DFA
    printf("\nMinimized DFA:\n");
    printf("State | a | b\n");
    for (i = 0; i < gnum; i++) {
        printf("  %d   | %d | %d\n", i, minTrans[i][0], minTrans[i][1]);
    }

    printf("Final states in minimized DFA: ");
    for (i = 0; i < gnum; i++) {
        if (minFinal[i]) printf("%d ", i);
    }
    printf("\n");

    return 0;
}

