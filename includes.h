#include "bits/stdc++.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>



using namespace std;



//macros
#define NO_OF_THREADS 20


//function prototypes
void create_threadpool(int n);
void *handler(void *buf);
void parseRequest(struct clientIdentity clientData);
typedef void (* dispatch_fn)(void*);
void create_threadpool(int n);
void dispatch(dispatch_fn dispatch_to_here,void* arg);
bool fileExists(char *filename);
int getFileSize(char *filename);
void sendFile(char *filename, int fsize, int sockfd);
void parseRequest(clientIdentity clientData);

//void destroy_threadpool(threadpool destroyme);


// structs/classes

typedef struct clientIdentity
{
	int sockId;    // socketDescriptor
	string ip;
	int portNo;
} clientIdentity;


typedef struct clientInfo
 {
 	string r_type;
 	string r_filename;
 }clientInfo;

struct Job
{
	void (*service) (void*);   //to hold address of function
	void *arg;                // to hold the argument of function
};

struct JobQueueData {
	pthread_cond_t q_NonEmpty;	// condidtion vairiables for empty and non-empty for queue
	pthread_cond_t q_Empty;
	pthread_mutex_t qlock;		//lock on the queue
	int qsize;			//size of queue
	queue<Job> q;	
};

struct PoolData {

	int num_threads;	//no. of threads
	pthread_t *threads;	//pointer to threads
	
	int shutdown;
	int dont_accept;
};

typedef struct sockaddr_in sockin_t;		//just a short name
typedef struct sockaddr sock_t;
typedef void (* dispatch_fn)(void*); //Function pointer
