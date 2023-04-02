#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 3

int mutex = 1, full = 0, empty = BUFFER_SIZE, x = 0;

void producer();
void consumer();
void wait(int*);
void signal(int*);

int main() {
    int choice;
    printf("\n1. Producer\n2. Consumer\n3. Exit");
    while (1) {
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;
        if (choice == 1) {
            if (mutex && empty)
                producer();
            else
                printf("\nBuffer is full!");
        }
        else if (choice == 2) {
            if (mutex && full)
                consumer();
            else
                printf("\nBuffer is empty!");
        }
    }
    return 0;
}

void wait (int *var) {
    *var-=1;
}

void signal (int *var) {
    *var+=1;
}

void producer() {
    wait(&mutex);
    signal(&full);
    wait(&empty);
    x++;
    printf("\nProducer produces the item %d", x);
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    wait(&full);
    signal(&empty);
    printf("\nConsumer consumes item %d", x);
    x--;
    signal(&mutex);
}