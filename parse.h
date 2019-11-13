#include "mystructs.h"
bool fileExists(char *filename)
{
	struct stat check;
	if (stat(filename, &check) != -1)
		return true;
	return false;
}

int getFileSize(char *filename)
{
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	rewind(fp);
	fclose(fp);
	return fsize;
}

void sendFile(char *filename, int fsize, int sockfd)
{
	FILE *fp = fopen(filename, "rb");
	char buff[4096];
	int n;
	while ((n = fread(buff, sizeof(char), 4096, fp)) > 0 && fsize > 0)
	{
		send(sockfd, buff, n, 0);
		memset(buff, 0, 4096);
		fsize = fsize - n;
	}
	fclose(fp);
}

void parseRequest(struct clientIdentity clientData)
{
	int recvbytes = 0;
	char buffer[4096];
	string request(buffer);
	vector<string> tok;
	string temp;

	if ((recvbytes = (recv(clientData.sockId, buffer, sizeof(buffer), 0))) == -1)
		perror("Receive:");
	cout << recvbytes << buffer << "\n";
	buffer[recvbytes] = '\0';

	char *chars_array = strtok(buffer, "#");
	while (chars_array)
	{
		tok.push_back(chars_array);
		chars_array = strtok(NULL, "#");
	}

	clientInfo reqData;
	reqData.r_type = tok[0]; //Any other info abt request can be added here
	reqData.r_filename = tok[1];

	//Check Request Type
	int fsize;
	char file[reqData.r_filename.size() + 1];
	strcpy(file, reqData.r_filename.c_str());
	if (reqData.r_type == "GET" && fileExists(file))
	{
		fsize = getFileSize(file); //send file size
		send(clientData.sockId, &fsize, sizeof(fsize), 0);

		sendFile(file, fsize, clientData.sockId); // send file
		close(clientData.sockId);				  //close client socket
	}
	else if (reqData.r_type == "GET" && !fileExists(file))
	{
		fsize = -1;
		// send (clientData.sockId,&fsize,sizeof(fsize),0);
		close(clientData.sockId); //close client socket
	}
	else
	{
		//request type mismatch
	}
}
