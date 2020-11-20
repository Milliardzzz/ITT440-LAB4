#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>


int main(int argc, char *argv[]){
	int socket_desc;
	struct sockaddr_in server;
	char message[2000], server_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}


	server.sin_addr.s_addr = inet_addr("192.168.0.163"); //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);	//Port is set 8888 to connect to server

	//Connect to remote server
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected \n");

	while(1)
	{
		//Send data message
		printf("Enter message: ");
		fgets(message, 2000, stdin);
		send(socket_desc, message,2000,0);

		//Receive a reply from the server
		if(recv(socket_desc, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
		}

		printf("\nFrom Server: %s", server_reply);
	}

	return 0;
}
