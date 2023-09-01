#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

#ifdef linux
#include "semaphore.h"
#elif __APPLE__
#include "zemaphore.h"
#endif
