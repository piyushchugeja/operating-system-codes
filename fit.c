#include <stdio.h>
#include <stdlib.h>

#define MAX 50
int main()
{
    int memory[MAX], size[MAX], alloc[MAX], i, j, n, m, choice;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);
    printf("Enter the size of each block:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &memory[i]);
        size[i] = memory[i];
    }
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    do {
        printf("\n1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // First Fit
                for (i = 0; i < m; i++) {
                    printf("Enter the size of process %d: ", i+1);
                    scanf("%d", &size[i]);
                    for (j = 0; j < n; j++) {
                        if (size[i] <= memory[j]) {
                            memory[j] -= size[i];
                            alloc[i] = j+1;
                            printf("Process %d allocated to memory block %d\n", i+1, j+1);
                            break;
                        }
                    }
                    if (j == n) {
                        printf("Process %d cannot be allocated memory\n", i+1);
                        alloc[i] = 0;
                    }
                }
                printf("\nMemory blocks:\n");
                for (i = 0; i < n; i++) {
                    printf("%d\t", i+1);
                }

                printf("\nAllocated processes:\n");
                for (i = 0; i < m; i++) {
                    if (alloc[i] != 0) {
                        printf("%d\t", alloc[i]);
                    } else {
                        printf("NA\t");
                    }
                }
                break;
            case 2: // Best Fit
                for (i = 0; i < m; i++) {
                    printf("Enter the size of process %d: ", i+1);
                    scanf("%d", &size[i]);
                    int min_index = -1;
                    for (j = 0; j < n; j++) {
                        if (size[i] <= memory[j]) {
                            if (min_index == -1 || memory[j] < memory[min_index]) {
                                min_index = j;
                            }
                        }
                    }
                    if (min_index != -1) {
                        memory[min_index] -= size[i];
                        alloc[i] = min_index+1;
                        printf("Process %d allocated to memory block %d\n", i+1, min_index+1);
                    } else {
                        printf("Process %d cannot be allocated memory\n", i+1);
                        alloc[i] = 0;
                    }
                }
                printf("\nMemory blocks:\n");
                for (i = 0; i < n; i++) {
                    printf("%d\t", i+1);
                }
                printf("\nAllocated processes:\n");
                for (i = 0; i < m; i++) {
                    if (alloc[i] != 0) {
                        printf("%d\t", alloc[i]);
                    } else {
                        printf("NA\t");
                    }
                }
                break;
            case 3: 
            for (i = 0; i < m; i++) {
            printf("Enter the size of process %d: ", i+1);
            scanf("%d", &size[i]);
                int max_index = -1;
                for (j = 0; j < n; j++) {
                    if (size[i] <= memory[j]) {
                        if (max_index == -1 || memory[j] > memory[max_index]) {
                            max_index = j;
                        }
                    }
                }
                if (max_index != -1) {
                    memory[max_index] -= size[i];
                    alloc[i] = max_index+1;
                    printf("Process %d allocated to memory block %d\n", i+1, max_index+1);
                } else {
                    printf("Process %d cannot be allocated memory\n", i+1);
                    alloc[i] = 0;
                }
            }
            printf("\nMemory blocks:\n");
            for (i = 0; i < n; i++) {
                printf("%d\t", i+1);
            }
            printf("\nAllocated processes:\n");
            for (i = 0; i < m; i++) {
                if (alloc[i] != 0) {
                    printf("%d\t", alloc[i]);
                } else {
                    printf("NA\t");
                }
            }
            break;
        case 4: 
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
            break;
    }

} while (choice != 4);
return 0;
}
