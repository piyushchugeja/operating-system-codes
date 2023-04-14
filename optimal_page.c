#include <stdio.h>
#include <limits.h>

int main() {
    int incomingStream[] = {4, 1, 2, 4, 5};
    int pageFaults = 0;
    int frames = 3;
    int m, n, s, pages;
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    printf("Incoming\tFrame 1\tFrame 2\tFrame 3\n");
    int temp[frames];
    for (m = 0; m < frames; m++) {
        temp[m] = -1;
    }
    for (m = 0; m < pages; m++) {
        s = 0;
        for (n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++;
            }
        }
        if (s == 0) {
            int index = -1;
            for (n = 0; n < frames; n++) {
                if (temp[n] == -1) {
                    index = n;
                    break;
                }
            }
            if (index == -1) {
                int farthest = -1;
                for (n = 0; n < frames; n++) {
                    int j;
                    for (j = m + 1; j < pages; j++) {
                        if (temp[n] == incomingStream[j]) {
                            if (j > farthest) {
                                farthest = j;
                                index = n;
                            }
                            break;
                        }
                    }
                    if (j == pages && index == -1) {
                        index = n;
                    }
                }
            }
            temp[index] = incomingStream[m];
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
