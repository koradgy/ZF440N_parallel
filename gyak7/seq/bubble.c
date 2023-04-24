#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define N 10000

int main()
{
    int* arr;
    clock_t start = clock();
    arr = malloc (N * sizeof(int));
    srand(time(NULL));

    for(int i =0; i<N; i++)
    {
        arr[i] = rand() % 10000;
    }

  /*  for(int i = 0; i < N; i++)
    {
        printf("%d, ",arr[i]);
    }
    printf("\n");*/

    //bubble sort

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

    /*for(int i = 0; i < N; i++)
    {
        printf("%d, ",arr[i]);
    }
    printf("\n");*/

    clock_t end = clock();
    double time = (end - start)/(CLOCKS_PER_SEC/1000);
    printf("runtime : %.2f ms\n",time);

    free(arr);

    return 0;
}