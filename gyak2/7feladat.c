#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool is_prime(int n) 
{
    if (n < 2) {
        return false;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int prime(int n)
{
    int primes = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            primes += 1;
        }
    }
    return primes;
}


int main()
{
    FILE *fp;
    fp = fopen("file.txt","w");
    for (int n = 1000; n <= 20000; n += 1000) 
    {
        clock_t start = clock();
        int a = prime(n);
        clock_t end = clock();
        double time = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(fp, "%d ,%d ,%.2f\n",n,a,time);
       
    }
    fclose(fp);
    return 0;
}
