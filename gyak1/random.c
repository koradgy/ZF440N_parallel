#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    srand(time(NULL));
    printf("size of your array: \n");
    int size;
    scanf("%d", &size);

    printf("start of interval: \n");
    int start;
    scanf("%d", &start);

    printf("end of interval: \n");
    int end;
    scanf("%d", &end);

    int interval[size];

    for(int i = 0; i < size; i++)
    {
        interval[i] = rand() % (start - end) + start;
    }

    for(int i = 0; i < size; i++)
    {
        printf("%d, ",interval[i]);
    }

    FILE *fp;
    fp = fopen("ranodm.txt");
    for(int i = 0; i < size; i++)
    {
        fprintf(fp,"%d, ",interval[i]);
    }
    fclose(fp);

    return 0;
}