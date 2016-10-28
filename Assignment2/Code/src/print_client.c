#include <time.h>
#include "jobs_queue.h"

int fd;
struct Jobs *jobs_controller;

void setup_shared_memory(){
    fd = shm_open(SHD_REG, O_RDWR, S_IRWXU);
    if(fd == -1){
        printf("shm_open() failed\n");
        exit(1);
    }
}

void attach_shared_memory(){
    jobs_controller = (struct Jobs*)  mmap(NULL, sizeof(struct Jobs), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(jobs_controller == MAP_FAILED){
        printf("mmap() failed\n");
        exit(1);
    }

}

void set_pages(int *pages){
    srand(time(NULL));
    *pages = 1 + (rand() % 10);
}

void detach_shared_memory(){
    int r = shm_unlink(SHD_REG);
    if (r != 0)
        printf("shm_unlink() failed\n");
        exit(1);
}

void handler(int signo){
    int temp;
    
    sem_getvalue(&jobs_controller->mutex, &temp);
    if(temp != 1)
        sem_post(&jobs_controller->mutex);
    
    sem_getvalue(&jobs_controller->items, &temp);
    if(temp != 1)
        sem_post(&jobs_controller->items);
    
    sem_getvalue(&jobs_controller->spaces, &temp);
    if(temp != 1)
        sem_post(&jobs_controller->spaces);
    exit(0);
}

int main(int argc, char *argv[]){
    int pages = 0;
    
    if(signal(SIGINT, handler) == SIG_ERR)
        printf("Signal Handler Failure ..\n");

    if(argc == 2){
        setup_shared_memory();
        puts("memory set up");
        attach_shared_memory();
        puts("memory shared");
        
        set_pages(&pages);

        put_job(&jobs_controller, atoi(argv[1]), pages);

        //detach_shared_memory();
    }
    else if(argc > 2){
        printf("Too many arguments entered.\n");
        exit(0);
    }
    else{
        printf("At least one argument expected.\n");
        exit(0);
    }
}