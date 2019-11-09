#include "includes.h"
//#include "mystructs.h"
#include "threadpool.h"
#include"parse.h"

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

void dispatch_to_here(void *arg)
{
	struct clientIdentity *tempClientData = (struct clientIdentity*)arg ; 
    struct clientIdentity clientData;  
    clientData.sockId = tempClientData->sockId ; 
    clientData.ip = tempClientData->ip ; 
    //clientData.portNo 
    //Parse *p=new Parse();
    parseRequest(clientData);
}


int main(int argc,char* argv[])
{

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

    if(bind(sock,(sock_t*)&serv_addr,sizeof(sock_t)) <0){
        cout<<"socket creation failed,try again\n";
        return 0;
    }  
    int status=listen(sock,20);


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
		clientData->ip = str;
		//clientData->portNo

		dispatch(dispatch_to_here, (void *) &clientData);

    }

	
    return 0;
}

