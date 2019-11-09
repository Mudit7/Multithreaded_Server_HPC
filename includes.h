#include <bits/stdc++.h>
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
#include<bits/stdc++.h>


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
//void destroy_threadpool(threadpool destroyme);
