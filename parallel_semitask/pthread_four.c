#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>

#define N 100000
#define THREADS 4


int* arr;

void* bubble_sort(void* thread)
{
    long rank = (long) thread;
    int i, j, temp;
    int start = rank * (N / THREADS);
    int end = (rank + 1) * (N / THREADS);
    for (i = start; i < end; i++) 
    {
        for (j = start; j < end - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return NULL;
}


int main()
{
    
    clock_t start = clock();
    arr = malloc (N * sizeof(int));
    srand(time(NULL));

    for(int i =0; i<N; i++)
    {
        arr[i] = rand() % 1000;
    }

  /*  for(int i = 0; i < N; i++)
    {
        printf("%d, ",arr[i]);
    }
    printf("\n");*/

    //bubble sort

    pthread_t* handles;
    handles = malloc (THREADS * sizeof(pthread_t));

    for (long thread = 0; thread < THREADS; thread++) 
    {
        pthread_create(&handles[thread], NULL, bubble_sort, (void*) thread);
    }

    for (long thread = 0; thread < THREADS; thread++) 
    {
        pthread_join(handles[thread], NULL);
    }

   /* for(int i = 0; i < N; i++)
    {
        printf("%d, ",arr[i]);
    }   
    printf("\n");*/

    clock_t end = clock();
    double runtime = (end - start)/(CLOCKS_PER_SEC/1000);
    
    FILE *fp = fopen("times.txt","a");
    fprintf(fp, "Pthread 4 threads: %.2f ms\n", runtime);
    fflush(fp);
    fclose(fp);

    free(handles);
    free(arr);

    return 0;
}