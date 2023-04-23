#include <stdio.h>
#include <stdlib.h>
#define FRAME_SIZE 3

_Bool isPagePresent(int page, int frames[]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i] == page) 
            return 1;
    }
    return 0;
}

int getNextOptimal (int pageIndex, int frames[], int numPages, int pages[]) {
    int maxNext = pageIndex, result = -1;
    for (int f = 0; f < FRAME_SIZE; f++) {
        int p;
        for (p = pageIndex; p < numPages; p++) {
            if (frames[f] == pages[p] && p > maxNext) {
                maxNext = p;
                result = f;
                break;
            }
        }
        if (p == numPages) 
            return f;
    }
    return (result == -1) ? 0 : result;
}

int getNextLeast (int pageIndex, int frames[], int numPages, int pages[]) {
    int leastUsed = pageIndex, result = -1;
    for (int f = 0; f < FRAME_SIZE; f++) {
        int p;
        for (p = pageIndex; p >= 0; p--) {
            if (pages[p] == frames[f] && p < leastUsed) {
                leastUsed = p;
                result = f;
                break;
            }
        }
        if (p == 0)
            return f;
    }
    return (result == -1) ? 0 : result;
}

int main() {
    int numPages, next = 0, pageFaults = 0, pageHits = 0, frames[FRAME_SIZE];
    printf("\nEnter the number of page references: ");
    scanf("%d", &numPages);
    int pages[numPages];
    printf("\nEnter the page reference string: ");
    for (int i = 0; i<numPages; i++) 
        scanf("%d", &pages[i]);
    for (int i = 0; i < FRAME_SIZE; i++) frames[i] = -1; 
    // First in first out
    printf("\nFirst in-first out");
    for (int i=0; i<numPages; i++) {
        if (!isPagePresent(pages[i], frames)) {
            pageFaults++;
            frames[next] = pages[i];
            next = (next+1)%FRAME_SIZE;
        }
        else 
            pageHits++;
        printf("\nPage %d, Frames: ", pages[i]);
        for (int j=0; j<FRAME_SIZE; j++) printf("%d ", frames[j]);
    }
    printf("\n\nTotal page faults = %d", pageFaults);
    printf("\nTotal page hits = %d\n", pageHits);

    for (int i = 0; i < FRAME_SIZE; i++) frames[i] = -1; 
    pageFaults = pageHits = 0;
    system("pause");
    // Optimal
    printf("\nOptimal page replacement");
    int occupied = 0;
    for (int i = 0; i < numPages; i++) {
        if (!isPagePresent(pages[i], frames)) {
            pageFaults++;
            if (occupied == FRAME_SIZE) {
                next = getNextOptimal(i, frames, numPages, pages);
                frames[next] = pages[i];
            } else 
                frames[occupied++] = pages[i];
        } else 
            pageHits++;
        printf("\nPage %d, Frames: ", pages[i]);
        for (int j=0; j<FRAME_SIZE; j++) printf("%d ", frames[j]);
    }
    printf("\n\nTotal page faults = %d", pageFaults);
    printf("\nTotal page hits = %d\n", pageHits);
    
    for (int i = 0; i < FRAME_SIZE; i++) frames[i] = -1;
    pageFaults = pageHits = 0;

    system("pause");

    // Least recently used
    printf("\nLRU page replacement");
    occupied = 0;
    for (int i = 0; i < numPages; i++) {
        if (!isPagePresent(pages[i], frames)) {
            pageFaults++;
            if (occupied == FRAME_SIZE) {
                next = getNextLeast(i, frames, numPages, pages);
                frames[next] = pages[i];
            } else 
                frames[occupied++] = pages[i];
        } else 
            pageHits++;
        printf("\nPage %d, Frames: ", pages[i]);
        for (int j=0; j<FRAME_SIZE; j++) printf("%d ", frames[j]);
    }
    printf("\n\nTotal page faults = %d", pageFaults);
    printf("\nTotal page hits = %d", pageHits);
    return 0;
}
