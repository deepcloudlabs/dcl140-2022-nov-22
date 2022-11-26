#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 8
#define COUNT 1000000 

static pthread_spinlock_t sp_lock;

int state = 0;

void * task(void* arg){
     int i;
     for(i=0;i<COUNT;++i){
        pthread_spin_lock(&sp_lock);
        state++;  
        pthread_spin_unlock(&sp_lock);
     }
}

int main(){
    pthread_t threads[NUM_THREADS];
    int i;
    pthread_spin_init(&sp_lock,0);
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
