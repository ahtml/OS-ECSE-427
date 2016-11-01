#ifndef _INCLUDE_COMMON_H_
#define _INCLUDE_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// from `man shm_open`
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <signal.h>
#include <sys/types.h> 
#include <semaphore.h>

#define SHD_REG "/memory_shared_region"

typedef enum { false , true } bool_t;

#endif //_INCLUDE_COMMON_H_

