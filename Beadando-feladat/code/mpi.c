#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

void merge(int* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned int N;
    clock_t begin = clock();

    srand(time(NULL));

    int* arr = NULL;
    int* sub_arr = NULL;
    int* sorted_arr = NULL;

    if (rank == 0) {
        printf("size of the array:\n");
        scanf("%u", &N);

        arr = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            arr[i] = rand() % 10000;
        }
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sub_arr = malloc((N / size) * sizeof(int));
    MPI_Scatter(arr, N / size, MPI_INT, sub_arr, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Bubble sort
    int temp;
    for (int i = 0; i < N / size - 1; i++) {
        for (int j = 0; j < N / size - i - 1; j++) {
            if (sub_arr[j] > sub_arr[j + 1]) {
                temp = sub_arr[j];
                sub_arr[j] = sub_arr[j + 1];
                sub_arr[j + 1] = temp;
            }
        }
    }

    // Összefésülés
    sorted_arr = malloc(N * sizeof(int));
    MPI_Gather(sub_arr, N / size, MPI_INT, sorted_arr, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) 
    {
        // Teljes tömb rendezése
    mergeSort(sorted_arr, 0, N - 1);

    clock_t stop = clock();
    double runtime = (stop - begin) / (CLOCKS_PER_SEC / 1000);
    FILE* fp = fopen("times.txt", "a");
    fprintf(fp, "MPI %d threads: %.2f ms\n", size, runtime);
    fflush(fp);
    fclose(fp);

    free(arr);
}

free(sub_arr);
free(sorted_arr);

MPI_Finalize();
return 0;
}
