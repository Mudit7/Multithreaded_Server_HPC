#include "includes.h"
#include "mystructs.h"


JobQueueData jobq;

void create_threadpool(int n)
{

    jobq.qsize=0;
    
    pthread_mutex_init(&jobq.qlock,NULL);
    pthread_cond_init(&jobq.q_Empty,NULL);
    pthread_cond_init(&jobq.q_NonEmpty,NULL);


    for(int i=0;i<n;i++)
    {
        pthread_t p;
        void *buf;
        //create threads
        pthread_create(&p,NULL,handler,(void*)buf);

    }
    

}

void *handler(void *buf)
{
    /*
        1. check job queue if empty then sleep, else take it
    
    */
   while(1) {	
		pthread_mutex_lock(&(jobq.qlock)); 
        if(jobq.q.empty())
        {
            //wait on condition variable
            pthread_cond_wait(&jobq.q_NonEmpty,&(jobq.qlock));
        }
        Job job=jobq.q.front();
        jobq.q.pop();

         

        pthread_mutex_unlock(&(jobq.qlock));
        //function call
        (job.service)(job.arg);

   }


}