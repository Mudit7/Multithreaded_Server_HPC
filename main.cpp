#include "includes.h"
#include "mystructs.h"



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
        if((newsockfd = accept(sock,(struct sockaddr*)&serv_addr,(socklen_t *)&addrlen)) == -1)
            perror("Accept:");


        //form client request object and dispatch!
        

    }


    return 0;
}

