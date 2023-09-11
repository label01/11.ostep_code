#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef struct {
    size_t n;
    int stack[]; //zero-length per c99
} pstack_t;

int main(int argc, char *argv[]){
    int fd, rc;
    struct stat s;
    size_t file_size;
    pstack_t *p;

    fd = open("ps.img", O_RDWR);
    assert(fd > -1);
    rc = fstat(fd, &s);
    assert(rc == 0);

    file_size = (size_t) s.st_size;
    assert(file_size >= sizeof(pstack_t) && file_size % sizeof(int) == 0);

    p = (pstack_t *) mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    assert(p != MAP_FAILED);

    for (int i = 1; i < argc, i++){
        if (strcmp(argv[i], "pop") == 0){
            if (p->n > 0){
                printf("%d\n", p->stack[--p->n]);
            }
            else{
                if(sizeof(pstack_t)+(1+p->n) * sizeof(int) <= file_size)
                {
                    p->stack[p->n++] = atoi(argv[i]);
                }
            }

        }
    }

    (void) close(fd);
    return 0;





}












