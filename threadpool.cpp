#include "includes.h"
std::chrono::time_point<std::chrono::system_clock> stop,start;
 
struct JobQueueData jobq;
struct PoolData pool;
void create_threadpool(int n)
{

    //jobq.qsize=0;
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
    pool.destroy=0;
}

void destroy_threadpool(int option)
{
    if(pool.destroy==1)
    {
        cout<<"Already Destroyed\n";
        return;
    }
    cout<<"About to destroy the Pool\nUse \"create\" command to create a new pool\n";
    pthread_mutex_lock(&(jobq.qlock));
    if(option==1)
    {
        //wait till job queue is empty
        if(!jobq.q.empty())
        {
            //wait on condition variable

            pthread_cond_wait(&jobq.q_Empty,&(jobq.qlock));

        }
    }
    pool.destroy=1;
    delete pool.threads;
    pool.num_threads=0;
    pool.threads=NULL;
    cout<<"Destroyed successfully\n";
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

	
    if(jobq.q.empty()) 
	{
        jobq.q.push(work);
		pthread_cond_signal(&jobq.q_NonEmpty); 
	}
    else{
        jobq.q.push(work);
    }
	//jobq.qsize++;	
    
	pthread_mutex_unlock(&jobq.qlock);  //unlock the queue.

}
//****************************************************************************************************


void *handler(void *buf)
{
    /*
        1. check job queue if empty then sleep, else take it
    
    */
   while(1) {	
       
        //if thread is to be destroyed
        if(pool.destroy)
        {
            pthread_exit(0);
            return NULL;
        }


		pthread_mutex_lock(&(jobq.qlock)); 
     
        if(jobq.q.empty())
        {
            //wait on condition variable
          
            pthread_cond_wait(&jobq.q_NonEmpty,&(jobq.qlock));
        }
        //wait if threadpool is being destroyed

        Job job=jobq.q.front();
        jobq.q.pop();
		
        pthread_mutex_unlock(&(jobq.qlock));
        //function call
        (job.service)(job.arg);
		stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count()<<endl;
		//fstream new_file;
		//new_file.open("newfile.txt", ios::out);	
		//cout << stop;
		//new_file.close();
   }
}

void *more_threads_alloc(void *)
{
    //check if qsize > num_threads*factor,then reallocate the pool threads
    while(1)
    {
        //check if more threads are required
        if(jobq.q.size()> pool.num_threads*FACTOR)
        {
            cout<<"Adding more threads to the pool\n";
            int oldt=pool.num_threads;
            int newt=pool.num_threads*FACTOR;
			//system bottleneck
			if(newt>100) return NULL;
			cout<< "Old count"<< oldt<<endl;
			cout<< "New count"<< newt<<endl;
			pool.num_threads=pool.num_threads*FACTOR;
            pool.threads = (pthread_t*) realloc (pool.threads,sizeof(pthread_t)*newt);
            //now create new threads
            for(int i=oldt;i<newt;i++)
            {
                pthread_t p;
                pool.threads[i]=p;
                void *buf;
                //create threads
                pthread_create(&pool.threads[i],NULL,handler,(void*)buf);
                
            }
        }
        sleep(0.5); //check periodically in every 2 sec
    }
    
}
