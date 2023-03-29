#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main()
{
    FILE *fp = fopen("values.txt", "a");
    int n;
    clock_t start, end;
    double runt;
    srand(time(NULL));
    printf("Size of the array: \n");
    scanf("%d", &n);

    start = clock();
    float *array = (float*)malloc(n*sizeof(float));

    for(int i = 0; i < n; i++)
    {
        array[i] = (float)rand()/RAND_MAX * 1.5;
    }

    int count = 0;
    for(int i = 0; i < n; i++)
    {
        float a = fabs(array[i]);
        if(a < 1)
        {
            //printf("Absolute value less than 1 :%.2f \n", array[i]);
            count ++;
        }
    }
    printf("numbers in [0,1] interval: %d \n", count);
    end = clock();
    runt = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(fp,"Program: decimal,  Array size: %d, runtime: %.2fs\n",n, runt);
    fclose(fp);

    return 0;
}