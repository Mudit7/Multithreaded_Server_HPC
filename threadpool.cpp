#include "includes.h"
#include "mystructs.h"

struct JobQueueData jobq;
struct PoolData pool;
void create_threadpool(int n)
{

    jobq.qsize=0;
    pool.num_threads=n;
    
    pthread_mutex_init(&jobq.qlock,NULL);
    pthread_cond_init(&jobq.q_Empty,NULL);
    pthread_cond_init(&jobq.q_NonEmpty,NULL);

	pool.threads = (pthread_t*) malloc (sizeof(pthread_t)*n);
    for(int i=0;i<n;i++)
    {
        pthread_t p;
        pool.threads[i]=p;
        void *buf;
        //create threads
        pthread_create(&p,NULL,handler,(void*)buf);

    }
    

}


//****************************************************************************************************

void dispatch(dispatch_fn dispatch_to_here,void* arg)
{
	

	//struct Job *work = (struct Job *)malloc(sizeof(struct Job));
	//make a work queue element.  
	struct Job work;	
	//if(work == NULL) {
		//fprintf(stderr, "Out of memory creating a work struct!\n");
		//return;
	//}

	
	work.service = dispatch_to_here;
	work.arg = arg;

	pthread_mutex_lock(&jobq.qlock);

	// it will helpful when the destroy function is already called and Just incase someone is trying to queue more function
	if(pool.dont_accept) { 
		//free(work); 
		return;
	}

	
    
    //pthread_cond_signal(&(pool->q_NonEmpty));
   
	
    if(jobq.q.empty()) 
	{
        jobq.q.push(work);
		pthread_cond_signal(&jobq.q_NonEmpty); 
	}
    else{
        jobq.q.push(work);
    }
	jobq.qsize++;	
    
	pthread_mutex_unlock(&jobq.qlock);  //unlock the queue.

}
//****************************************************************************************************


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
