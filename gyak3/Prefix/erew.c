#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void erew_prefix(int *a, int n) {
    int i, j, k;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i = i + 2) {
            j = i + k + 1;
            if (j < n) {
                a[j] += a[i];
            }
        }
        #pragma omp barrier
    }
}

int main() {
    int n = 100;
    int a[n];

    int max_threads = omp_get_max_threads();
    int work[max_threads][n];

    FILE *fp;
    fp = fopen("erew_stats.txt", "w");

    fprintf(fp, "T");
    for (int i = 0; i < max_threads; i++) {
        fprintf(fp, "\t%d", i);
    }
    fprintf(fp, "\n");

    for (int t = 0; t <= n; t++) {
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }

        double start = omp_get_wtime();
        #pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            int chunk_size = n / max_threads;
            int start_index = thread_id * chunk_size;
            int end_index = start_index + chunk_size - 1;

            erew_prefix(&a[start_index], chunk_size);

            for (int i = start_index; i <= end_index; i++) {
                work[thread_id][i] = a[i];
            }
        }
        double end = omp_get_wtime();

        fprintf(fp, "%d", t);
        for (int i = 0; i < max_threads; i++) {
            int useful_work = 0;
            for (int j = 0; j < n; j++) {
                if (work[i][j] != j) {
                    useful_work++;
                }
            }
            if (useful_work > 0) {
                fprintf(fp, "\t#");
            } else {
                fprintf(fp, "\t.");
            }
        }
        fprintf(fp, "\n");

        printf("Time %d complete. Elapsed time: %f seconds.\n", t, end - start);
    }

    fclose(fp);

    return 0;
}
