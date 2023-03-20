#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    int *p = (int *)arg;
    printf("Thread %d started\n", *p);

    // Szimuláljunk egy futásidejű hibát
    if (*p == 2) {
        printf("Thread %d encountered a runtime error!\n", *p);
        int *ptr = NULL;
        *ptr = 1;
    }

    printf("Thread %d finished\n", *p);
    pthread_exit(NULL);
}

int main() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        int rc = pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
        if (rc) {
            printf("Error creating thread %d\n", i);
            exit(-1);
        }
    }

    // Várjunk a szálak befejezésére
    for (int i = 0; i < NUM_THREADS; i++) {
        void *status;
        int rc = pthread_join(threads[i], &status);
        if (rc) {
            printf("Error joining thread %d\n", i);
            exit(-1);
        }
        printf("Thread %d joined\n", i);
    }

    printf("All threads finished\n");
    return 0;
}
