#include "includes.h"

int main(int argc,char *argv[])
{
	int serverport=5000;
	if(argc>2)
		serverport=atoi(argv[2]);
    vector<string> tok;
    string protocol(argv[1]);
    //cout << "Enter Request#filename::";
    //getline(cin, protocol);
    stringstream tokenizer(protocol);
    string temp;
    while (getline(tokenizer, temp, '#'))
    {
        //cout << temp << endl;
        tok.push_back(temp);
    }
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // specifying address for the socket
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverport);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //setting connection
    int connection_status = connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    //checking error in connection
    if (connection_status == -1)
        printf("There was an error making a connection to the server\n\n");
    send(client_socket, protocol.c_str(), sizeof(protocol), 0);
    int file_size = 0;
    recv(client_socket, &file_size, sizeof(file_size), 0);
    tok[1] = "/home/lenovo/Downloads/" + tok[1];
    //cout<<tok[1]<<endl;
    FILE *fp = fopen(tok[1].c_str(), "a+");
    char buffer[4096];
    int n;
    if (file_size > 0)
    {
        while ((n = recv(client_socket, buffer, sizeof(buffer), 0)) > 0 && file_size > 0)
        {

            fwrite(buffer, sizeof(char), n, fp);
            memset(buffer, '\0', sizeof(buffer));
            file_size = file_size - n;
        }
    }
    else
    {
        cout<<"File Not Received\n";
    }
    
    fclose(fp);
    close(client_socket);
    return 0;
}
