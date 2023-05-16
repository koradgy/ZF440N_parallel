#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>

// Struktúra a szálparaméterek tárolásához
typedef struct {
    int start_index;
    int end_index;
    int* array;
} ThreadArgs;

// Segédfüggvény a két szám cserecseréjéhez
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

unsigned int ARRAY_SIZE ;
unsigned int NUM_THREADS ;

// Szálkezelő függvény a bubblesort algoritmus végrehajtásához
void* bubbleSort(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int start = args->start_index;
    int end = args->end_index;
    int* array = args->array;

    for (int i = start; i < end - 1; ++i) {
        for (int j = 0; j < end - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }

    pthread_exit(NULL);
}

int main() 
{
    printf("size of the array: \n");
    scanf("%u", &ARRAY_SIZE);
    printf("number of threads:\n");
    scanf("%u", &NUM_THREADS);

    int iter = 0;
    do
    {
    

    int array[ARRAY_SIZE];
    clock_t begin = clock();
    srand(time(NULL));

    // Tömb elemek generálása véletlen számokkal
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 100;
    }

    // Szálak inicializálása és indítása
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];

    int chunk_size = ARRAY_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i].start_index = i * chunk_size;
        thread_args[i].end_index = (i + 1) * chunk_size;
        thread_args[i].array = array;

        pthread_create(&threads[i], NULL, bubbleSort, (void*)&thread_args[i]);
    }

    // Szálak befejezésének várása
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Összefésülés
    int step = 1;

    while (step < ARRAY_SIZE) {
        for (int i = 0; i < ARRAY_SIZE; i += 2 * step) {
            int start = i;
            int mid = i + step;
            int end = i + 2 * step;

            if (mid >= ARRAY_SIZE) {
                continue;
            }

            if (end > ARRAY_SIZE) {
                end = ARRAY_SIZE;
            }

            int merged_size = end - start;
            int merged_array[merged_size];

            int left = start;
            int right = mid;
            int k = 0;

            while (left < mid && right < end) {
                if (array[left] <= array[right]) {
                    merged_array[k++] = array[left++];
                } else {
                    merged_array[k++] = array[right++];
                }
            }

            while (left < mid) {
                merged_array[k++] = array[left++];
            }

            while (right < end) {
                merged_array[k++] = array[right++];
            }

            for (int j = 0; j < merged_size; ++j) {
                array[start + j] = merged_array[j];
            }
        }

        step *= 2;
    }

    // Rendezett tömb kiíratása
   /* printf("Rendezett tömb: ");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");*/

        clock_t stop = clock();
        double runtime = (stop - begin)/(CLOCKS_PER_SEC/1000);
        FILE *fp = fopen("times.txt","a");
        fprintf(fp, "pthread: threads: %d runtime: %.2f ms\n",NUM_THREADS, runtime);
        fflush(fp);
        fclose(fp);
        NUM_THREADS += 2;
        iter++;
     } while (iter != 100);

    return 0;
}
