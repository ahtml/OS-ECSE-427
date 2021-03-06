/*
Printer Spooler
Header file that defines the functions on job_queue.c 
and defines the structures used: 
Jobs and Job info

Author: Luis Gallet Zambrano 260583750
Last date modified: 04/11/2016
*/

#ifndef JOBS_QUEUE_H_  /* Include guard */

#include "common.h"

#define JOBS_QUEUE_H_

#define MAX_LENGTH 10

struct Job_info{
	int ID;
	int pages;
};

struct Jobs {
  	struct Job_info job_queue[MAX_LENGTH];
  	int queue_length;
  	int job_in, job_out;
  	int repeated_ID;
  	int printers_counter;
  	bool_t new_job;
  	bool_t shutdown_server;
  	bool_t new_printer;
  	sem_t mutex;     
  	sem_t items;       
  	sem_t spaces;      
};

void put_job(struct Jobs *job_ctrl, int item, int pages);
bool_t take_job(struct Jobs *job_ctrl, struct Job_info **job, int *printerID);
int isNewJob(struct Jobs *job_ctrl, int item);

#endif //JOBS_QUEUE