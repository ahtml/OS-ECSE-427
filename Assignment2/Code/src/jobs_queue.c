#include "jobs_queue.h"


void put_job(struct Jobs *job_ctrl, int item, int pages) {
    puts("Client: at put_job()");
  	sem_wait(&job_ctrl->spaces);
 	sem_wait(&job_ctrl->mutex);

 	//Check if the incoming job is already in the buffer waiting for a printer
    job_ctrl->repeated_ID = isNewJob(job_ctrl, item);
    if(job_ctrl->repeated_ID != -1){
        printf("Client %d is already in the job queue at position %d\n", item, job_ctrl->repeated_ID);
 		sem_post(&job_ctrl->mutex);
 		sem_post(&job_ctrl->spaces);
        return;
    }
  	
  	puts("Client: adding job..");

    job_ctrl->job_queue[job_ctrl->job_in].ID = item;
    job_ctrl->job_queue[job_ctrl->job_in].pages = pages;
    printf("Client: job %d added\n", job_ctrl->job_queue[job_ctrl->job_in].ID);
    
    job_ctrl->job_in = (job_ctrl->job_in + 1) % job_ctrl->queue_length;
    printf("Client: index of job_in: %d\n", job_ctrl->job_in);

   	sem_post(&job_ctrl->mutex);

  	sem_post(&job_ctrl->items);

}

int take_job(struct Jobs *job_ctrl, struct Job_info **job) {
    puts("Server: from take_job()");

    sem_wait(&job_ctrl->items);

    if(job_ctrl->shutdown_server){
    	return 0;
    }
  	sem_wait(&job_ctrl->mutex);

  	memcpy(*job, &job_ctrl->job_queue[job_ctrl->job_out], sizeof(struct Job_info));

  	printf("Server: Job ID: %d job pages: %d\n",(*job)->ID, (*job)->pages);

  	job_ctrl->job_queue[job_ctrl->job_out].ID = 0;
  	job_ctrl->job_queue[job_ctrl->job_out].pages = 0;

  	//Calculate next index in the job buffer that will be served next
  	job_ctrl->job_out = (job_ctrl->job_out + 1) % job_ctrl->queue_length;
  	printf("Server: index of job_out: %d\n", job_ctrl->job_out);


  	sem_post(&job_ctrl->mutex);
  	sem_post(&job_ctrl->spaces);

    puts("Server: finished processing job..");

   	return 1;
}

/*
This function checks if an incoming job has the same ID as another one that it is already
waiting in the buffer. 
It returns the index of the job in the buffer with the same ID or -1 when no equal ID is found.
If a job with the same ID was already served in the past, the job is accepted.
*/
int isNewJob(struct Jobs *job_ctrl, int item){
	for(int i = job_ctrl->job_out; i < MAX_LENGTH; i++){
		printf("job_ctrl->job_queue[%d].ID = %d\n", i, job_ctrl->job_queue[i].ID);
		if(job_ctrl->job_queue[i].ID == item){
			return i;
		}
	}

	return -1;
}

void reset_job_queue(struct Jobs *job_ctrl){
	for(int i = 0; i < MAX_LENGTH; i++){
		job_ctrl->job_queue[i].ID = 0;
		job_ctrl->job_queue[i].pages = 0;
	}
}

//int isProcessingFinished(){
	
//}
