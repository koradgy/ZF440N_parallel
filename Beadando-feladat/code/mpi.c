#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char** argv)
{

    unsigned int N;
    printf("Size of the array:\n");
    scanf("%u",&N);
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //folyamat sorszáma
    MPI_Comm_size(MPI_COMM_WORLD, &size);// mérete

    printf("%d\n", size);

    int* arr;
    clock_t begin = clock();
    arr = malloc (N * sizeof(int));
    srand(time(NULL));

    if (rank == 0) { //a fő szál feltölti a tömbböt
        for(int i =0; i<N; i++)
        {
            arr[i] = rand() % 10000;
        }
       /* for(int i = 0; i < N; i++)
        {
            printf("%d, ",arr[i]);
        }
        printf("\n");*/
    }

    int* sub_arr = malloc((N/size) * sizeof(int));//foylamat résztömbbjei
    MPI_Scatter(arr, N/size, MPI_INT, sub_arr, N/size, MPI_INT, 0, MPI_COMM_WORLD); //a résztömbök kiosztása

    //bubble sort
    int temp;
    for(int i = 0; i < N/size-1; i++)
    {
        for(int j = 0; j < N/size-i-1; j++)
        {
            if (sub_arr[j] > sub_arr[j+1]) 
            {
                temp = sub_arr[j];
                sub_arr[j] = sub_arr[j+1];
                sub_arr[j+1] = temp;
            }
        }
    }

    MPI_Gather(sub_arr, N / size, MPI_INT, arr, N / size, MPI_INT, 0, MPI_COMM_WORLD); // eredmények összegyűjtése az arr tömbbe

    if(rank == 0)
    { //A fő szál kiírja a rendezett tömbböt és leáll a program.

        /*for(int i = 0; i < N; i++)
        {
            printf("%d, ",arr[i]);
        }
        printf("\n");*/

        clock_t stop = clock();
        double runtime = (stop - begin)/(CLOCKS_PER_SEC/1000);
            FILE *fp = fopen("times.txt","a");
            fprintf(fp, "MPI  threads: %.2f ms\n", runtime);
            fflush(fp);
            fclose(fp);
        free(arr);
    }
    free(sub_arr);

    MPI_Finalize();
    return 0;
}
