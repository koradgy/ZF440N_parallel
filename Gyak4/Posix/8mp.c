#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>
#include <time.h>

void sleepfour(void* _){
    sleep(4);
    printf("4mp work is done!\n");
}

void createnew(void* _){
    sleep(8);
    printf("8mp work is done!\n");
    pthread_t new;
    pthread_create(&new,NULL,sleepfour,NULL);
    pthread_join(new,NULL);
}

int main(int argc, char* argv[]){

    pthread_t foszall;

    pthread_create(&foszall,NULL,createnew,NULL);
    pthread_join(foszall,NULL);

    printf("DONE!\n");
  
    return 0;
}