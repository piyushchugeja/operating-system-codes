#include<stdio.h>

int main() {
    int n, i;
    float avgWaitTime = 0, avgTurnaroundTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burstTime[n], waitTime[n], turnaroundTime[n];
    printf("Enter burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i+1);
        scanf("%d", &burstTime[i]);
    }
    waitTime[0] = 0;  
    for(i = 1; i < n; i++) {
        waitTime[i] = waitTime[i-1] + burstTime[i-1];
    }
    for(i = 0; i < n; i++) {
        turnaroundTime[i] = waitTime[i] + burstTime[i];
        avgWaitTime += waitTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }
    avgWaitTime /= n;
    avgTurnaroundTime /= n;
    printf("Process\tBurst\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i+1, burstTime[i], waitTime[i], turnaroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    return 0;
}
