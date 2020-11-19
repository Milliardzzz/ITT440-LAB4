#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr


int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char client_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);


	//Bind
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
	}
	puts("bind done");


	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connection...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

	if(new_socket < 0)
	{
		perror("accept failed");
	}

	puts("Connection accepted");

	//Send and receive
	if(recv(new_socket, client_reply, 2000, 0) < 0){
		puts("Receive failed");
	}
	puts("Reply received\n");
	puts(client_reply);
	char msg[2000] = "This is server";
	send(new_socket, msg, 2000, 0);

	return 0;
}
