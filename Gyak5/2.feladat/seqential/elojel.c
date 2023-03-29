#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *fp = fopen("values.txt","a");
    clock_t start, end;
    double runt;
    int n;
    int *array;
    srand(time(NULL));
    printf("Size of the array: \n");
    scanf("%d", &n);

    start = clock();
    array = (int*) malloc(n * sizeof(int));
    int min = -1000;
    int max = 1000;
    for(int i = 0; i < n; i++)
    {
        array[i] = rand() % (max - min)+ min;
        //printf("%d ",array[i]);
    }

    int plus = 0;
    int minus = 0;

    for(int i = 0; i < n; i++)
    {
        if(array[i] >= 0)
            plus++;
        else
            minus++;
    }
    end = clock();
    runt = (double)(end - start) / CLOCKS_PER_SEC;
    printf("there are %d positive and %d negative numbers in the array.\n", plus, minus);

    fprintf(fp,"Program: elojel, Array size: %d, runtime: %.2fs\n",n, runt);
    fclose(fp);
    return 0;
}