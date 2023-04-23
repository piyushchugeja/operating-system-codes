#include <stdio.h>
#include <stdlib.h>

int getNextSafeIndex(int n, int m, int work[], int finish[], int need[][m]) {
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            int j;
            for (j = 0; j < m; j++)
                if (need[i][j] > work[j])
                    break;
            if (j == m)
                return i;
        }
    }
    return -1;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int available[m], work[m], finish[n], max[n][m], allocation[n][m], need[n][m], safeSequence[n], index;
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }
    printf("Enter the maximum resources for each process: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) 
            scanf("%d", &max[i][j]);
        finish[i] = 0;
    }
    printf("Enter the allocated resources for each process: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
            work[j] -= allocation[i][j];
        }
    }
    printf("The safe sequence is: ");
    for (int i = 0; i < n; i++) {
        index = getNextSafeIndex(n, m, work, finish, need);
        if (index == -1) {
            printf("The system is not in a safe state.");
            return 0;
        }
        safeSequence[i] = index;
        finish[index] = 1;
        for (int j = 0; j < m; j++)
            work[j] += allocation[index][j];
        printf("P%d ", index);
    }
    return 0;
}