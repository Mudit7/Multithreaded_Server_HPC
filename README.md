# Multithreaded_Server_HPC
#### Team Members : 
1. 2019201013 Sangam
2. 2019201028 Divyani Indurkhya
3. 2019201063 Mudit Malpani
4. 2019201065 Nisarg
### Motivation :
1. Learn how to use the pthreads library to manage threads
2. Understand how to create a multi-threaded server along with understanding basic thread synchronization
3. Gain practice with client software that can issue multiple requests over a socket.
### Abstract :
A multithreaded file server that creates a thread pool with N threads. When a new client request arrives, the server should add it to a queue of jobs. The threads should remove one job from the queue and handle the request. If the job queue does not have any jobs available, the threads should “sleep” until a job queue is empty. The job queue is shared among all threads and thus requires synchronization. the server accepts the file requests sent by the client and sends it using TCP datagram.
#### Functions:
1. void parseRequest(clientIdentity clientData);
2. void create_threadpool(int n);
3. void dispatch(dispatch_fn dispatch_to_here,void* arg);
4. void destroy_threadpool(int option);
#### additional functionalities 
1. Threadpool destroy

    user input terminates running threads and destroys the threadpool. 

2. Dynamic threadpool 

    pool size inceases by a factor k and becomes k times it's initial size. with an upper bound to no. of threads set to 50

#### setting up the enviroenment

1. clone the repository 
2. run automake
3. server is ready to recive requests. 
