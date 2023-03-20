#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_threads = 60;
    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        double thread_start = omp_get_wtime();
        while (omp_get_wtime() - thread_start < 1) {
            // végezzen hasznos számítást
            // itt csak várakozunk, hogy látványosabb legyen a kimenet
            int i, j;
            for (i = 0; i < 1000000; i++) {
                j = i * i;
            }
        }
    }

    double end = omp_get_wtime();
    double elapsed_time = end - start;
    printf("A program futási ideje: %f másodperc\n", elapsed_time);

    return 0;
}
