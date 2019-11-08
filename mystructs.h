#include "includes.h"

struct clientIdentity
{
	int acceptId;    // socketDescriptor
	string ip;
	int portNo;
	//string requestTime;
};


// struct clientInfo
// {
// 	string r_method;
// 	string r_type;
// 	string r_version;
// 	string r_firstline;
// 	string r_filename;
// 	string r_time;
// 	string r_servetime;
// 	int r_acceptid;
// 	string r_ip;
// 	u_int16_t r_portno;
// 	int r_filesize;
// 	bool status_file;
// 	string r_ctype;
// 	bool rootcheck;
// 	int status_code;

// };

typedef struct Job
{
	void (*service) (void*);   //to hold address of function
	void *arg;                // to hold the argument of function
}job;

typedef struct JobQueueData {
	pthread_cond_t q_NonEmpty;	// condidtion vairiables for empty and non-empty for queue
	pthread_cond_t q_Empty;
	pthread_mutex_t qlock;		//lock on the queue
	int qsize;			//size of queue
	queue<Job> q;	
}JobQueueData;

typedef struct PoolData {

	int num_threads;	//no. of threads
	pthread_t *threads;	//pointer to threads
	
	int shutdown;
	int dont_accept;
} PoolData;

typedef struct sockaddr_in sockin_t;		//just a short name
typedef struct sockaddr sock_t;