#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

/*void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}
void mergeSort(int arr[], int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;
    int *left = malloc(mid * sizeof(int));
    int *right = malloc((n - mid) * sizeof(int));

    memcpy(left, arr, mid * sizeof(int));
    memcpy(right, arr + mid, (n - mid) * sizeof(int));

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(left, mid);
        }

        #pragma omp section
        {
            mergeSort(right, n - mid);
        }
    }

    merge(arr, left, mid, right, n - mid);

    free(left);
    free(right);
}*/

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() 
{
    printf("size of the array:\n");
    int n;
    scanf("%d", &n);

    printf("number of threads:\n");
    int threads;
    scanf("%d",&threads);

    clock_t start = clock();
    int* arr = malloc (n * sizeof(int));
    srand(time(0));

  //  printf("Eredeti tömb:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
      //  printf("%d ", arr[i]);
    }
    //printf("\n");

    #pragma omp parallel num_threads(threads)
    {
        for (int i = 0; i < n-1; i++) 
        {
            for (int j = 0; j < n-i-1; j++) 
            {
                if (arr[j] > arr[j+1]) 
                {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
    // Összefésülés
    int step = 1;

    while (step < n) {
        for (int i = 0; i < n; i += 2 * step) {
            int start = i;
            int mid = i + step;
            int end = i + 2 * step;

            if (mid >= n) {
                continue;
            }

            if (end > n) {
                end = n;
            }

            int merged_size = end - start;
            int merged_array[merged_size];

            int left = start;
            int right = mid;
            int k = 0;

            while (left < mid && right < end) {
                if (arr[left] <= arr[right]) {
                    merged_array[k++] = arr[left++];
                } else {
                    merged_array[k++] = arr[right++];
                }
            }

            while (left < mid) {
                merged_array[k++] = arr[left++];
            }

            while (right < end) {
                merged_array[k++] = arr[right++];
            }

            for (int j = 0; j < merged_size; ++j) {
                arr[start + j] = merged_array[j];
            }
        }

        step *= 2;
    }


   /* printf("Rendezett tömb:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");*/


    clock_t stop = clock();
    double runtime = (stop - start)/(CLOCKS_PER_SEC/1000);
    FILE *fp = fopen("times.txt","a");
    fprintf(fp, "OMP threads: %d runtime : %.2f ms\n", threads, runtime);
    fflush(fp);
    fclose(fp);
    free(arr);

    return 0;
}
