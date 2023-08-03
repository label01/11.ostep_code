#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "common.h"

int main(int argc, char *argv[])
{
    /* code */
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address pointed to by p: %p\n", getpid(), p);
    *p = 0;

    while (1)
    {
        /* code */
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;
}

