#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define MAX_SIZE 1000

int sum = 0;
int array[MAX_SIZE];

void *sumArray(void *threadID) {
    int i, tid = *(int*)threadID;
    int chunkSize = sizeof(array) / sizeof(int) / NUM_THREADS;
    int start = tid * chunkSize;
    int end = start + chunkSize;

    for (i = start; i < end; i++) {
        sum += array[i];
    }

    pthread_exit(NULL);
}

int main() {
    int i, size, threadID[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    printf("Kerem adja meg a tomb meretet: ");
    scanf("%d", &size);


    for (i = 0; i < size; i++) {
        array[i] = rand() % 100;
        
    }

    for (i = 0; i < NUM_THREADS; i++) {
        threadID[i] = i;
        pthread_create(&threads[i], NULL, sumArray, (void*)&threadID[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAz elemek osszege: %d\n", sum);

    return 0;
}
