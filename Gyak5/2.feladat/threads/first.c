#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int size;
    int *arr;
} ThreadArgs;

void *count_even(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int size = args->size;
    int *arr = args->arr;
    int even_count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
    }
    int *result = malloc(sizeof(int));
    *result = even_count;
    return result;
}

void *count_odd(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int size = args->size;
    int *arr = args->arr;
    int odd_count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            odd_count++;
        }
    }
    int *result = malloc(sizeof(int));
    *result = odd_count;
    return result;
}
int main()
{
    FILE *fp = fopen("values.txt", "a");
    clock_t start, end;
    srand(time(NULL));
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    ThreadArgs args;
    args.size = size;
    args.arr = arr;

    int *even_count;
    int *odd_count;
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, count_even, (void *)&args);
    pthread_create(&threads[1], NULL, count_odd, (void *)&args);

    pthread_join(threads[0], (void **)&even_count);
    pthread_join(threads[1], (void **)&odd_count);

    printf("There are %d even numbers and %d odd numbers in the array.\n", *even_count, *odd_count);
     
    end = clock();
    double runt = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(fp, "Program: first, Arraysize: %d, runtime: %.2f",size, runt);
    fclose(fp);
    free(arr);
    free(even_count);
    free(odd_count);
    return 0;
}
