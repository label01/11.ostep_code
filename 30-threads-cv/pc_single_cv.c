#include "assert.h"
#include "pthread.h"
#include "semaphore.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "common.h"
#include "common_threads.h"


int max;
int loops;
int *buffer;

int use_ptr = 0;
int fill_ptr = 0;
int num_full = 0;

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


int consumers = 1;
int verbose = 1;

void do_fill(int value){
    /*将给定的value存储到缓冲区的fill_ptr位置，即当前的填充指针位置。*/
    buffer[fill_ptr] = value;
    /*每次填充都往前填充一位， 如果达到最大值，就绕回缓冲区的起始位置*/
    fill_ptr = (fill_ptr + 1) % max;
    num_full++;
}

int do_get(){
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % max;
    num_full--;
    return tmp;
}

void *producer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        Mutex_lock(&m);
        while (num_full == max)
        {
            /* code */
            Cond_wait(&cv, &m);
        }
        do_fill(i);
        Cond_signal(&cv);
        Mutex_unlock(&m);
        
    }

    for (i = 0; i < consumers; i++){
        Mutex_lock(&m);
        while(num_full == max){
            Cond_wait(&cv, &m);
        }
        do_fill(-1);
        Cond_signal(&cv);
        Mutex_unlock(&m);
    }

    return NULL;
}


void *consumer(void *arg){
    int tmp = 0;
    while (tmp != -1)
    {
        /* code */
        while (num_full == 0)
        {
            /* code */
            Cond_wait(&cv, &m);
        }
        tmp = do_get();
        Cond_signal(&cv);
        Mutex_lock(&m);
    }
    return NULL;
    
}


int main(int argc, char *argv[]){
    if (argc != 4)
    {
        /* code */
        fprintf(stderr, "usage: %s <buffersize> <loops> <consumers>\n", argv[0]);
        exit(1);
    }

    max = atoi(argv[1]);
    loops = atoi(argv[2]);
    consumers = atoi(argv[3]);

    buffer = (int *) malloc(max * sizeof(int));
    assert(buffer != NULL);


    int i;
    for ( i = 0; i < max; i++)
    {
        /* code */
        buffer[i] = 0;
    }

    pthread_t pid, cid[consumers];
    Pthread_create(&pid, NULL, producer, NULL);
    for(i = 0; i < consumers; i++)
    {
        Pthread_create(&cid[i], NULL, consumer, (void *)(long long int) i);
    }
    Pthread_join(pid, NULL);
    for ( i = 0; i < consumers; i++)
    {
        /* code */
        Pthread_join(cid[i], NULL);
    }
    
    return 0;
    
}







