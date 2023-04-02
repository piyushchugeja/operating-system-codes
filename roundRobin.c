#include <stdio.h>
#include <stdlib.h>

int tat = 0, wt = 0;
struct Process {
    int pid, at, bt, ct, tat, wt, rt;
    _Bool done;
};
void schedule (struct Process *processes, int n) {
    int quantum, e = 0, doneCount = 0, found, time = 0, rem[n];
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for (int i = 0; i < n; i++)
        rem[i] = processes[i].bt;
    while (doneCount != n) {
        if (rem[e] <= quantum && rem[e] > 0) {
            time += rem[e];
            rem[e] = 0;
            found = 1;
        } else if (rem[e] > 0) {
            rem[e] -= quantum;
            time += quantum;
        }
        if (rem[e] == 0 && !processes[e].done) {
            processes[e].ct = time;
            processes[e].tat = processes[e].ct - processes[e].at;
            processes[e].wt = processes[e].tat - processes[e].bt;
            processes[e].rt = processes[e].wt;
            processes[e].done = 1;
            doneCount++;
            printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d", processes[e].pid, processes[e].at, processes[e].bt, processes[e].ct, processes[e].tat, processes[e].wt, processes[e].rt);
            tat += processes[e].tat;
            wt += processes[e].wt;
        }
        if (e == n - 1)
            e = 0;
        else if (processes[e + 1].at <= time)
            e++;
        else
            e = 0;
    }
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].done = 0;
    }
    schedule(p, n);
    printf("\nAverage Turnaround Time: %.2f", (float) tat / n);
    printf("\nAverage Waiting Time: %.2f", (float) wt / n);
    return 0;
}