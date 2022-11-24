#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4096
// 4096 * 8M = 4 * 8G = 32G
void * task(void* arg){
   fprintf(stderr,"Thread %li is working now...\n",(unsigned long int)pthread_self());
   sleep(rand()%30 + 30);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int i;
    srand(time(NULL));
    for (i=0;i<NUM_THREADS;++i){
        pthread_create(&threads[i],NULL,task,NULL);   
    }
    fprintf(stderr,"Threads are all created!\n");
    fprintf(stderr,"pid: %d !\n",getpid());
    
    for (i=0;i<NUM_THREADS;++i){
        pthread_join(threads[i],NULL);   
    }
    fprintf(stderr,"Threads are all existed!\n");
    return 0;
}
