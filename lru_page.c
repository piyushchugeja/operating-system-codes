#include <stdio.h>

int main() {
    int incomingStream[] = {4, 1, 2, 4, 5};
    int pageFaults = 0;
    int frames = 3;
    int m, n, s, pages;
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    printf("Incoming\tFrame 1\tFrame 2\tFrame 3\n");
    int temp[frames];
    int lru[frames];
    for (m = 0; m < frames; m++) {
        temp[m] = -1;
        lru[m] = 0;
    }
    for (m = 0; m < pages; m++) {
        s = 0;
        for (n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++;
                lru[n] = 0;
            } else if (temp[n] != -1) {
                lru[n]++;
            }
        }
        if (s == 0) {
            int index = 0;
            int max_lru = lru[0];
            for (n = 1; n < frames; n++) {
                if (lru[n] > max_lru) {
                    max_lru = lru[n];
                    index = n;
                }
            }
            temp[index] = incomingStream[m];
            lru[index] = 0;
            pageFaults++;
        }
        printf("%d\t\t", incomingStream[m]);
        for (n = 0; n < frames; n++) {
            if (temp[n] != -1) {
                printf("%d\t\t", temp[n]);
            } else {
                printf("-\t\t");
            }
        }
        printf("\n");
    }
    printf("Total Page Faults:\t%d\n", pageFaults);
    return 0;
}
