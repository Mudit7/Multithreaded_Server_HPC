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
A multithreaded server that creates a thread pool with N threads. When a new client request arrives, the server should add it to a queue of jobs. The threads should remove one job from the queue and handle the request. If the job queue does not have a jobs available, the thread should “sleep” until a job is ready. The job queue is shared among all threads and thus requires synchronization to protect access to the job queue. The processing to be done on behalf of the client is to take a file required by the client and send it from the server.
#### Functions:
1. void parseRequest(clientIdentity clientData);
2. void create_threadpool(int n);
3. void dispatch(dispatch_fn dispatch_to_here,void* arg);
4. void destroy_threadpool(int option);
