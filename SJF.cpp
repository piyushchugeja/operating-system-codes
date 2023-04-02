#include <iostream>
using namespace std;

class Process {
    public:
    int pid, at, bt, ct, tat, wt, rt;
    bool done;
};

class SJF {
    private:
    int n, time;
    Process processes[10];
    public:
    SJF() {
        time = 0;
    }
    void inputDetails() {
        cout << "Enter the number of processes: ";
        cin >> n;
        cout << "Enter the arrival time and burst time of each process:\n";
        for (int i = 0; i < n; i++) {
            cin >> processes[i].at >> processes[i].bt;
            processes[i].pid = i + 1;
            processes[i].done = false;
        }
    }
    void sortProcesses() {
        Process temp;
        for (int i = 1; i < n; i++) {
            temp = processes[i];
            int j = i - 1;
            while (j >= 0 && processes[j].bt > temp.bt) {
                processes[j + 1] = processes[j];
                j--;
            }
            processes[j + 1] = temp;
        }
    }
    void schedule() {
        int e = 0, doneCount = 0, found;
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
                time += 1;
                continue;
            }
            processes[e].rt = time - processes[e].at;
            time += processes[e].bt;
            processes[e].ct = time;
            processes[e].tat = processes[e].ct - processes[e].at;
            processes[e].wt = processes[e].tat - processes[e].bt;
            processes[e].done = true;
            doneCount += 1;
            cout << processes[e].pid << "\t" << processes[e].at << "\t" << processes[e].bt << "\t" << processes[e].ct << "\t" << processes[e].tat << "\t" << processes[e].wt << "\t" << processes[e].rt << endl;
        }
    }
};

int main() {
    SJF sjf;
    sjf.inputDetails();
    sjf.sortProcesses();
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    sjf.schedule();
    return 0;
}