#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

void bubbleSort(int arr[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int arr[], int left[], int right[], int left_size, int right_size) {
    int* temp_arr = malloc((left_size + right_size) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            temp_arr[k++] = left[i++];
        } else {
            temp_arr[k++] = right[j++];
        }
    }

    while (i < left_size) {
        temp_arr[k++] = left[i++];
    }

    while (j < right_size) {
        temp_arr[k++] = right[j++];
    }

    for (int t = 0; t < k; t++) {
        arr[t] = temp_arr[t];
    }

    free(temp_arr);
}


int main() {
    unsigned int N;
    printf("Size of the array:\n");
    scanf("%u", &N);

    int threads;
    printf("Number of threads:\n");
    scanf("%u", &threads);

    int* arr;
    clock_t begin = clock();
    arr = malloc(N * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000;
    }

    #pragma omp parallel num_threads(threads)
    {
        int start = omp_get_thread_num() * (N / omp_get_num_threads());
        int end = (omp_get_thread_num() + 1) * (N / omp_get_num_threads());

        bubbleSort(arr + start, end - start);
    }

    int* temp_arr = malloc(N * sizeof(int));

    for (int size = 1; size < N; size *= 2) {
        #pragma omp parallel for num_threads(threads)
        for (int i = 0; i < N; i += 2 * size) {
            int left_size = size;
            int right_size = (i + size * 2 <= N) ? size : (N - i - size);

            int* left = arr + i;
            int* right = arr + i + size;

            merge(temp_arr + i, left, right, left_size, right_size);
        }

        #pragma omp parallel for num_threads(threads)
        for (int i = 0; i < N; i++) {
            arr[i] = temp_arr[i];
        }
    }


    /*for (int i = 0; i < N; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");*/

    clock_t stop = clock();
    double runtime = (stop - begin) / (CLOCKS_PER_SEC / 1000);
    FILE* fp = fopen("times.txt", "a");
    fprintf(fp, "OMP %d threads: %.2f ms\n", threads, runtime);
    fflush(fp);
    fclose(fp);

    free(arr);
    free(temp_arr);
    return 0;
}
