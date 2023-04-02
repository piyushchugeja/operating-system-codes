#include <stdio.h>

#define MAX_PROCESS 10

int main() {
    int burst_time[MAX_PROCESS], priority[MAX_PROCESS];
    int i, j, min_priority, n, total_time = 0, turnaround_time, waiting_time, completion_time;
    float average_waiting_time = 0, average_turnaround_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter details of process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    for (i = 0; i < n - 1; i++) {
        min_priority = i;
        for (j = i + 1; j < n; j++) {
            if (priority[j] < priority[min_priority]) {
                min_priority = j;
            }
        }
        if (min_priority != i) {
            int temp = priority[i];
            priority[i] = priority[min_priority];
            priority[min_priority] = temp;

            temp = burst_time[i];
            burst_time[i] = burst_time[min_priority];
            burst_time[min_priority] = temp;
        }
    }

    printf("\nProcess\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        completion_time = total_time + burst_time[i];
        turnaround_time = completion_time;
        waiting_time = total_time;
        total_time = completion_time;

        average_waiting_time += waiting_time;
        average_turnaround_time += turnaround_time;

       printf("P%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", i + 1, burst_time[i], priority[i], completion_time, turnaround_time, waiting_time);
    }
    average_turnaround_time /= n;
    average_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f", average_turnaround_time);
    printf("\nAverage Waiting Time: %.2f", average_waiting_time);

    return 0;
}
