#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"


int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n"); 
        exit(1);
    } else if( rc == 0){
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");     //program : "wc" (word count)
        myargs[1] = strdup("p3.c");   //arguments: file to count
        myargs[2] = NULL;             //marks end of array

        execvp(myargs[0], myargs);    // runs wrod count
        printf("this shouldn't be print out");
    }else{
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}







