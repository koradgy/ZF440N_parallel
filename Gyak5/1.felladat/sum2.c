#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define MAX_SIZE 1000

int sum = 0;
int array[MAX_SIZE];

void *sumArray(void *threadID) {
    int tid = *(int *)threadID;
    int start = tid * (MAX_SIZE / NUM_THREADS);
    int end = start + (MAX_SIZE / NUM_THREADS);
    int local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += array[i];
    }

    printf("Thread %d: sum = %d\n", tid, local_sum);

    sum += local_sum;
    pthread_exit(NULL);
}

int main() {
    int array_size, lower_limit, upper_limit;
    printf("Enter array size: ");
    scanf("%d", &array_size);

    printf("Enter lower limit: ");
    scanf("%d", &lower_limit);

    printf("Enter upper limit: ");
    scanf("%d", &upper_limit);

    for (int i = 0; i < array_size; i++) {
        array[i] = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
    }

    pthread_t threads[NUM_THREADS];
    int threadIDs[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadIDs[i] = i;
        pthread_create(&threads[i], NULL, sumArray, (void *)&threadIDs[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum = %d\n", sum);

    return 0;
}
