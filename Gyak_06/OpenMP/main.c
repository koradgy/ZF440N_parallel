#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>

long long int ompProduct(int* array, int n);
long long int seqProduct(int *array, int n);

int main()
{
    int n;
    printf("Array size: \n");
    scanf("%d",&n);

    int array[n];
    srand(time(0));

    for(int i = 0; i < n; i++)
    {
        array[i] = rand() % 10 + 1;
        printf("%d\n",array[i]);
    }
    double start_time = omp_get_wtime();
    long long int seqP = seqProduct(array, n);
    double end_time = omp_get_wtime();

    printf("Sequential: prod = %lld, rumtime : %.5f\n",seqP, end_time-start_time);

    double start = omp_get_wtime();
    long long int ompP = ompProduct(array, n);
    double end = omp_get_wtime();

    printf("OpenMP: prod = %lld, rumtime : %.5f\n",ompP, end-start);
  

  

    return 0;
}



long long int ompProduct(int* array, int n)
{
    long long int product = 1;

    #pragma omp parallel for reduction(*:product)

    for(int i = 0; i < n; i++)
    {
        product *= array[i];
    }
    return product;
}

long long int seqProduct(int* array, int n)
{
    long long int product = 1;

    for(int i = 0; i < n; i++)
    {
        product *= array[i];
    }
    return product;
}