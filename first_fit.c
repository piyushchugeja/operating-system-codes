#include <stdio.h>
#include <stdlib.h>

void printProcesses(int processes, int allocated[], int processSizes[]) {
    printf("\nProcess\tSize\tBlock number");
    for (int i = 0; i < processes; i++) {
        printf("\n%d\t%d\t", i+1, processSizes[i]);
        if (allocated[i] != -1)
            printf("%d", allocated[i]+1);
        else
            printf("Not allocated");
    }
}

int main() {
    int pNo, bNo, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &pNo);
    printf("Enter the number of blocks: ");
    scanf("%d", &bNo);
    int processes[pNo], allocated[pNo], blocks[bNo], occupied[bNo];
    printf("\nEnter process sizes one by one: ");
    for (int i=0; i<pNo; i++) {
        scanf("%d", &processes[i]);
        allocated[i] = -1;
    }
    printf("\nEnter block sizes one by one: ");
    for (int i=0; i<bNo; i++) {
        scanf("%d", &blocks[i]);
        occupied[i] = 0;
    }
    // First fit
    for (int i = 0; i<pNo; i++) {
        for (int j = 0; j<bNo; j++) {
            if (blocks[j] >= processes[i] && occupied[j] == 0) {
                occupied[j] = 1;
                allocated[i] = j;
                break;
            }
        }
    }
    printProcesses(pNo, allocated, processes);
}