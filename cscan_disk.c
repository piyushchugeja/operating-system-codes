#include <stdio.h>
#include <stdlib.h>

int size = 8;

void CSCAN(int arr[], int head) {
    int seek_count = 0;
    int distance, cur_track;
    int left = 0, right = size - 1;
    int visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    printf("Seek Sequence is\n");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] > head) {
            left = i - 1;
            right = i;
            break;
        }
    }
    for (int i = right; i < size; i++) {
        cur_track = arr[i];
        if (!visited[i]) {
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            visited[i] = 1;
            printf("%d\n", cur_track);
        }
    }
    for (int i = left; i >= 0; i--) {
        cur_track = arr[i];
        if (!visited[i]) {
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            visited[i] = 1;
            printf("%d\n", cur_track);
        }
    }

    printf("Total number of seek operations: %d\n", seek_count);
}

int main() {
    int arr[8] = { 176, 79, 34, 60, 92, 11, 41, 114 };
    int head = 50;

    CSCAN(arr, head);

    return 0;
}
