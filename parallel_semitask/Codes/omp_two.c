#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<omp.h>

#define N 10000

int main()
{
    int* arr;
    clock_t begin = clock();
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
    #pragma omp parallel num_threads(2)
    {
        int start = omp_get_thread_num() * (N / omp_get_num_threads());
        int end = (omp_get_thread_num() + 1) * (N / omp_get_num_threads());

        int temp;
        for(int i = 0; i < N-1; i++)
        {
            for(int j = 0; j < N-i-1; j++)
            {
                if (arr[j] > arr[j+1]) 
                {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }

    /*for(int i = 0; i < N; i++)
    {
        printf("%d, ",arr[i]);
    }
    printf("\n");*/

    clock_t stop = clock();
    double runtime = (stop - begin)/(CLOCKS_PER_SEC/1000);
    FILE *fp = fopen("times.txt","a");
    fprintf(fp, "OMP 2 threads: %.2f ms\n", runtime);
    fflush(fp);
    fclose(fp);

    free(arr);

    return 0;
}