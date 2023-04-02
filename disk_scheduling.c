#include <stdio.h>
#include <math.h>
int initialPosition, numberOfSeeks, cylinders[10], totalHeadMovements = 0, totalSeekTime = 0;

struct Cylinder {
    int cylinder, distance;
    _Bool visited;
};

void FCFS (struct Cylinder *cylinders, int seekTime) {
    int difference;
    for (int i = 0; i < numberOfSeeks; i++) {
        difference = abs(initialPosition-cylinders[i].cylinder);
        totalHeadMovements += difference;
        cylinders[i].distance = difference;
        initialPosition = cylinders[i].cylinder;
    }
    totalSeekTime = totalHeadMovements * seekTime;
}

void SSTF (struct Cylinder *cylinders, int seekTime) {
    int difference;
    while (1) {
        int min = 9999, index;
        for (int i = 0; i < numberOfSeeks; i++) {
            if (cylinders[i].visited) continue;
            difference = abs(initialPosition-cylinders[i].cylinder);
            if (difference < min) {
                min = difference;
                index = i;
            }
        }
        if (min == 9999) break;
        cylinders[index].visited = 1;
        cylinders[index].distance = min;
        totalHeadMovements += min;
        initialPosition = cylinders[index].cylinder;
    }
}

int main() {
    int seekTime, choice;
    struct Cylinder cylinders[10];
	printf("Enter the number of cylinders to visit: ");
	scanf("%d", &numberOfSeeks);
	printf("Enter the cylinders one by one: ");
	for (int i = 0; i < numberOfSeeks; i++) {
        scanf("%d", &cylinders[i].cylinder);
        cylinders[i].visited = 0;
    }
	printf("Enter the initial head position: ");
	scanf("%d", &initialPosition);
	printf("Enter the seek time per movement (ms): ");
	scanf("%d", &seekTime);
    printf("Choose the disk scheduling algorithm:\n1. FCFS\n2. SSTF\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) FCFS(cylinders, seekTime);
    else if (choice == 2) SSTF(cylinders, seekTime);
    else {
        printf("Invalid choice!\n");
        return 0;
    }
	printf("\nTotal head movements: %d", totalHeadMovements);
	printf("\nTotal seek time: %d ms\n", totalSeekTime);
}
