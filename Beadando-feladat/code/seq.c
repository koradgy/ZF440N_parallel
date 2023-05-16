#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

void bubbleSort(int arr[]) 
{
    for (int i = 0; i < N ; i++) 
    {
        for (int j = 0; j < N - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    clock_t start = clock();
    int *arr;
    arr = malloc(N * sizeof(int));
    srand(time(NULL));

    for(int i = 0; i < N; i++)
    {
        arr[i] = rand() % 10000;
       // printf("%d, ", arr[i]);
    }
    printf("\n");
    //bubble
    bubbleSort(arr);


  /*  for(int i = 0; i < N; i++)
    {
        printf("%d, ", arr[i]);
    }
*/
    clock_t end = clock();
    double runtime = (end - start)/ (CLOCKS_PER_SEC / 1000);


    FILE *fp = fopen("times.txt","a");
    fprintf(fp, "Sequential: %.2f ms\n", runtime);
    fflush(fp);
    fclose(fp);

    free(arr);

    return 0;
}