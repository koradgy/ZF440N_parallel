#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *fp = fopen("values.txt","a");
    clock_t start, end;
    double runt;
    int *array;
    int n;
    int zeros = 0;

    printf("size of the array: \n");
    scanf("%d",&n);
    start = clock();
    array = (int*)malloc(n * sizeof(int));

    srand(time(0));
    for(int i = 0; i < n; i++)
    {
        array[i] = rand() % 11; 
    }

    for(int i = 0; i < 10; i++)
    {
        if(array[i] == 0)
            zeros++;
    }
    end = clock();
    runt = (double)(end - start) / CLOCKS_PER_SEC;

    printf("there are %d zeros in the array\n",zeros);
    fprintf(fp,"Program: zero, Array size: %d, runtime: %.2fs\n",n, runt);
    fclose(fp);
    return 0;
}