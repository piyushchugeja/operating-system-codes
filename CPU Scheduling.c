#include <stdio.h>
#include <stdlib.h>

int tat = 0, wt = 0;
struct Process {
    int pid, at, bt, ct, tat, wt;
    _Bool done;
};

void sort(struct Process *p, int n) {
    struct Process temp;
    for (int i = 1; i < n; i++) {
        temp = p[i];
        int j = i - 1;
        while (j >= 0 && p[j].bt > temp.bt) {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = temp;
    }
}

void sjf (struct Process *processes, int n) {
    int e = 0, doneCount = 0, found, time = 0;
    sort(processes, n);
    while (doneCount != n) {
        found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && !processes[i].done) {
                e = i;
                found = 1;
                break;
            }
        }
        if (!found) {
            time++;
            continue;
        }
        time += processes[e].bt;
        processes[e].ct = time;
        processes[e].tat = processes[e].ct - processes[e].at;
        processes[e].wt = processes[e].tat - processes[e].bt;
        processes[e].done = 1;
        doneCount++;
        tat += processes[e].tat;
        wt += processes[e].wt;
    }
}

void roundRobin (struct Process *processes, int n) {
    int quantum, e = 0, doneCount = 0, time = 0, rem[n], found;
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    for (int i = 0; i < n; i++)
        rem[i] = processes[i].bt;
    while (doneCount != n) {
        found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && rem[i] > 0) {
                found = 1;
                if (rem[i] <= quantum) {
                    time += rem[i];
                    rem[i] = 0;
                    processes[i].done = 1;
                } else {
                    rem[i] -= quantum;
                    time += quantum;
                }
                if (!rem[i] && processes[i].done) {
                    processes[i].ct = time;
                    processes[i].tat = processes[i].ct - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                    doneCount++;
                    tat += processes[i].tat;
                    wt += processes[i].wt;
                }
            }
            if (!found)
                time++;
        }
    }
}


int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].done = 0;
    }
    printf("\nSchedule to be used:\n1. SJF\n2. Round Robin\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) sjf(p, n);
    else if (choice == 2) roundRobin(p, n);
    else {
        printf("Invalid choice!");
        exit(0);
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++)
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    printf("\nAverage Turnaround Time: %.2f", (float) tat / n);
    printf("\nAverage Waiting Time: %.2f", (float) wt / n);
    return 0;
}
