#include "includes.h"

// #include "threadpool.h"

//PoolData pool;

//If below functions reqd then move to headers otherwise discard
//Return Port #
u_int16_t get_port_number(struct sockaddr *s)
{
    return (((struct sockaddr_in  *)s)->sin_port);
}

//Return Ip address
void * get_ip_address(sockaddr *s)
{
    return &((sockaddr_in *)s)->sin_addr;
}

void * get_that_input (void *){
    string input;
    while (true){
         printf("Enter Command : ");
         getline(cin,input);
         if(input=="destroy"){
             destroy_threadpool(1);
         }
         else if(input=="destroy -f")
         {
             destroy_threadpool(2);
         }
         else if(input == "create")
         {
             create_threadpool(20); //create a new pool(to be used after destruction pls..)
         }
    }
}

void dispatch_to_here(void *arg)
{
	clientIdentity *tempClientData = (clientIdentity*)arg ; 
    clientIdentity clientData;  
    clientData.sockId = tempClientData->sockId ; 
    clientData.ip = tempClientData->ip ; 
    //clientData.portNo 
    //Parse *p=new Parse();
    parseRequest(clientData);
}


int main(int argc,char* argv[])
{

    pthread_t pool_d_id;

    if (pthread_create(&pool_d_id, NULL, get_that_input, (void *)NULL) < 0)
    {
        perror("\ncould not create thread for input\n");
    }
    if (pthread_create(&pool_d_id, NULL, more_threads_alloc, (void *)NULL) < 0)
    {
        perror("\ncould not create thread for input\n");
    }

    create_threadpool(NO_OF_THREADS);
    

    //listen,accept

    int port=5000;
   
    int sock=-1;
    sockin_t serv_addr;
    pthread_t thread_id;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error in client side\n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int addrlen=sizeof(serv_addr);

    // if(bind(sock,(sock_t*)&serv_addr,sizeof(sock_t)) <0){
    //     cout<<"socket creation failed,try again\n";
    //     return 0;
    // }  
    bind(sock,(sock_t*)&serv_addr,sizeof(sock_t));
    int status=listen(sock,100);

   
    while(true)
    {
        
        int newsockfd=-1;
        struct sockaddr_in client_addr;
        char IP[INET6_ADDRSTRLEN];
        int clientAddLen;
        if((newsockfd = accept(sock,(struct sockaddr*)&client_addr,(socklen_t *)&clientAddLen)) == -1)
            perror("Accept:");
            
		inet_ntop(client_addr.sin_family,get_ip_address((struct sockaddr *)&client_addr),IP, sizeof(IP));

        //form client request object and dispatch!
        struct clientIdentity *clientData = (struct clientIdentity *)malloc(sizeof(struct clientIdentity));
		clientData->sockId = newsockfd;
		string str(IP);
		clientData->ip = "sdgsg";
        clientData->portNo=1234;
		//clientData->portNo

		dispatch(dispatch_to_here, (void *) clientData);

    }

	
    return 0;
}

