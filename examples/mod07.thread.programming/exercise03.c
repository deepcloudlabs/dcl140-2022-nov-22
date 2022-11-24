#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4096
#define COUNT 1000000 

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int state = 0;

void * task(void* arg){
     int i;
     for(i=0;i<COUNT;++i){
        pthread_mutex_lock(&mutex);
        state++;  
        pthread_mutex_unlock(&mutex);
     }
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
    fprintf(stderr,"Threads are all exited!\n");
    fprintf(stderr,"state: %d.\n",state);
    return 0;
}
