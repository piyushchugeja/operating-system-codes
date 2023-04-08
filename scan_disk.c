#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 8

void scan(int arr[], int head, int direction) {
    int i, j, pos, seek_count = 0, diff;
    int left[SIZE], right[SIZE], seek_seq[SIZE + 1];
    for(i = 0, j = 0, pos = 0; pos < SIZE; pos++) {
        if(arr[pos] < head) {
            left[i++] = arr[pos];
        }
        else if(arr[pos] > head) {
            right[j++] = arr[pos];
        }
    }
    for(i = 0; i < j - 1; i++) {
        for(int k = i + 1; k < j; k++) {
            if(right[i] > right[k]) {
                int temp = right[i];
                right[i] = right[k];
                right[k] = temp;
            }
        }
    }
    for(i = 0; i < j; i++) {
        seek_seq[i] = right[i];
    }
    seek_seq[j] = head;
    for(i = 0; i < j - 1; i++) {
        for(int k = i + 1; k < j; k++) {
            if(left[i] < left[k]) {
                int temp = left[i];
                left[i] = left[k];
                left[k] = temp;
            }
        }
    }
    for(i = j + 1; i < SIZE; i++) {
        seek_seq[i] = left[i - j - 1];
    }

    for(i = 0; i < SIZE; i++) {
        diff = abs(seek_seq[i + 1] - seek_seq[i]);
        seek_count += diff;
    }

    printf("Seek Sequence is:\n");
    for(i = 0; i <= SIZE; i++) {
        printf("%d ", seek_seq[i]);
    }
    printf("\nTotal number of seek operations: %d\n", seek_count);
}

int main() {
    int arr[SIZE] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    int direction = 1; 

    scan(arr, head, direction);

    return 0;
}
