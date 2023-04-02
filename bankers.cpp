#include <iostream>
using namespace std;

class Bankers {
    private:
    int n, m;
    int available[6], allocation[10][6], max[10][6], need[10][6], work[6], finish[10];
    
    public:
    void inputDetails() {
        cout << "Enter the number of processes: ";
        cin >> n;
        cout << "Enter the number of resources: ";
        cin >> m;
        cout << "Enter the total available resources: ";
        for (int i = 0; i < m; i++) {
            cin >> available[i];
            work[i] = available[i];
        }
        cout << "Enter the allocation matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> allocation[i][j];
                work[j] -= allocation[i][j];
            }
        }
        cout << "Enter the max matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> max[i][j];
                need[i][j] = max[i][j] - allocation[i][j];
            }
            finish[i] = 0;
        }
    }

    int getNextSafeIndex() {
        int i, j, k, flag;
        for (i = 0; i < n; i++) {
            flag = 1;
            if (!finish[i]) {
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) 
                    return i;
            }
        }
        return -1;
    }

    void bankersAlgorithm() {
        int i, j, k, allNotDone, safeSequence[10], index = 0;
        cout << "Need matrix:\n";
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                cout << need[i][j] << " ";
            cout << endl;
        }
        while (1) {
            allNotDone = 0;
            cout << "Work: ";
            for (i = 0; i < m; i++)
                cout << work[i] << " ";
            k = getNextSafeIndex();
            if (k == -1) {
                cout << "No safe sequence exists! System is in deadlock state." << endl;
                return;
            }
            cout << "\nP" << k << " is safe to execute." << endl;
            safeSequence[index++] = k;
            finish[k] = 1;
            for (j = 0; j < m; j++) 
                work[j] += allocation[k][j];
            for (i = 0; i < n; i++) {
                if (!finish[i]) {
                    allNotDone = 1;
                    break;
                }
            }
            if (!allNotDone) {
                cout << "Safe sequence: ";
                for (i = 0; i < n; i++)
                    cout << "P" << safeSequence[i] << " ";
                cout << endl;
                return;
            }
        }
    }
};

int main() {
    Bankers b;
    b.inputDetails();
    b.bankersAlgorithm();
    return 0;
}