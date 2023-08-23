#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#include "common.h"
#include "common_threads.h"

int max;
volatile int count = 0; //shared global variable

void *mythread(void *arg){
    char *letter = arg;
    
}