#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// CREW_PREFIX implementáció
void crew_prefix_sum(int* input, int* output, int n) {
    int i, j, t;
    #pragma omp parallel for private(t)
    for (i = 0; i < n; i++) {
        output[i] = input[i];
    }
    for (j = 1; j < n; j <<= 1) {
        #pragma omp parallel for private(i, t)
        for (i = j; i < n; i += (j << 1)) {
            t = output[i];
            output[i] = output[i - j] + t;
            output[i - j] = t;
        }
    }
}

// EREW_PREFIX implementáció
void erew_prefix_sum(int* input, int* output, int n) {
    int i, j, t;
    #pragma omp parallel for private(t)
    for (i = 0; i < n; i++) {
        output[i] = input[i];
    }
    for (j = 1; j < n; j <<= 1) {
        #pragma omp parallel for private(i, t) shared(output)
        for (i = j; i < n; i += (j << 1)) {
            t = output[i];
            output[i] = output[i - j] + t;
        }
    }
}

// OPTIMAL_PREFIX implementáció
void optimal_prefix_sum(int* input, int* output, int n) {
    int i, j, k, t;
    #pragma omp parallel for private(t)
    for (i = 0; i < n; i++) {
        output[i] = input[i];
    }
    for (j = 1; j < n; j <<= 1) {
        #pragma omp parallel for private(i, t) shared(output)
        for (i = j; i < n; i += (j << 1)) {
            t = output[i + j - 1];
            output[i + j - 1] += output[i - 1];
            output[i - 1] = t;
        }
    }
}

int main() {
    int n, i;
    double start, end;
    printf("Array size: \n");
    scanf("%d",&n);

    // Tömb inicializálása véletlenszámokkal
    int* input = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        input[i] = rand() % 100;
    }

    // CREW_PREFIX tesztelése
    int* output_crew = (int*)malloc(n * sizeof(int));
    start = omp_get_wtime();
    crew_prefix_sum(input, output_crew, n);
    end = omp_get_wtime();
    printf("CREW_PREFIX: %f seconds\n", end - start);
    free(output_crew);

    // EREW_PREFIX tesztelése
    int* output_erew = (int*)malloc(n * sizeof(int));
    start = omp_get_wtime();
    erew_prefix_sum(input, output_erew, n);
    end = omp_get_wtime();
    printf("EREW_PREFIX: %f seconds\n", end - start);
    free(output_erew);

    // OPTIMAL_PREFIX tesztelése
    int* output_optimal = (int*)malloc(n * sizeof(int));
    start = omp_get_wtime();
    optimal_prefix_sum(input, output_optimal, n);
    end = omp_get_wtime();
    printf("OPTIMAL_PREFIX: %f seconds\n", end - start);
    free(output_optimal);

    free(input);
    return 0;
}
