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

void firstFit(int blocks, int blockSizes[], int processes, int processSizes[]) {
    int allocated[processes], occupied[blocks];
    for (int i=0; i<processes; i++)
        allocated[i] = -1;
    for (int i=0; i<blocks; i++)
        occupied[i] = 0;
    for (int i=0; i<processes; i++) {
        for (int j=0; j<blocks; j++) {
            if (processSizes[i] <= blockSizes[j] && !occupied[j]) {
                allocated[i] = j;
                occupied[j] = 1;
                break;
            }
        }
    }
    printProcesses(processes, allocated, processSizes);
}

void bestFit(int blocks, int blockSizes[], int processes, int processSizes[]) {
    int allocated[processes], occupied[blocks], difference, min, index;
    for (int i=0; i<processes; i++)
        allocated[i] = -1;
    for (int i=0; i<blocks; i++)
        occupied[i] = 0;
    for (int i=0; i<processes; i++) {
        index = -1;
        for (int j=0; j<blocks; j++) {
            if (!occupied[j] && blockSizes[j] >= processSizes[i]) {
                if (index == -1 || blockSizes[j] < blockSizes[index])
                    index = j;
            }
        }
        if (index != -1) {
            allocated[i] = index;
            occupied[index] = 1;
        }
    }
    printProcesses(processes, allocated, processSizes);
}

void worstFit(int blocks, int blockSizes[], int processes, int processSizes[]) {
    int allocated[processes], occupied[blocks], difference, min, index;
    for (int i=0; i<processes; i++)
        allocated[i] = -1;
    for (int i=0; i<blocks; i++)
        occupied[i] = 0;
    for (int i=0; i<processes; i++) {
        index = -1;
        for (int j=0; j<blocks; j++) {
            if (!occupied[j] && blockSizes[j] >= processSizes[i]) {
                if (index == -1 || blockSizes[j] > blockSizes[index])
                    index = j;
            }
        }
        if (index != -1) {
            allocated[i] = index;
            occupied[index] = 1;
        }
    }
    printProcesses(processes, allocated, processSizes);
}

void main() {
    int bNo, pNo, choice;
    printf("Enter the number of blocks: ");
    scanf("%d", &bNo);
    printf("Enter the number of processes: ");
    scanf("%d", &pNo);
    int processes[pNo], blocks[bNo];
    printf("\nEnter the block sizes one by one: ");
    for (int i=0; i<bNo; i++) scanf("%d", &blocks[i]);
    printf("Enter the process sizes one by one: ");
    for (int i=0; i<pNo; i++) scanf("%d", &processes[i]);
    printf("\nChoose allocation policy:\n1. First fit\n2. Best fit\n3. Worst fit\n\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
        firstFit(bNo, blocks, pNo, processes);
    else if (choice == 2)
        bestFit(bNo, blocks, pNo, processes);
    else if (choice == 3) 
        worstFit(bNo, blocks, pNo, processes);
    else 
        printf("\nInvalid choice!");
}