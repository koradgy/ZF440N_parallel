#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("values.txt","a");
    int n;
    int *array;
    clock_t start, end;
    double runt;
    srand(time(NULL));
    printf("Size of the array: \n");
    scanf("%d", &n);
    start = clock();
    array = (int*) malloc(n * sizeof(int));

    if(array == NULL)
    {
        printf("HIBA\n");
        return 1;
    }

    for(int i = 0; i < n; i++)
    {
        array[i] = rand() % 5000;
        //printf("%d ",array[i]);
    }

    int even = 0;
    int odd = 0;

    for(int i = 0; i < n; i++)
    {
        if(array[i]% 2 == 0)
            even++;
        else
            odd++;
    }
    end = clock();
    runt = (double)(end - start) / CLOCKS_PER_SEC;
    printf("there are %d even and %d odd numbers in the array.\n", even, odd);
    fprintf(fp,"Program: first, Array size: %d, runtime: %.2fs\n",n, runt);
    fclose(fp);
    return 0;
}