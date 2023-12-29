#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	struct  addrinfo hints, *result, *r;		
	struct sockaddr_in *addr_in;
	char addr[INET_ADDRSTRLEN];
	int socket_fd, s;
	char buf[] = "GET / HTTP/1.1\r\nHost: hemnet.se\r\n\r\n";

	memset(&hints, 0, sizeof(struct addrinfo));
	memset(addr, '\0', sizeof(addr));
	
	if(argc != 3)
	{
		printf("usage %s <host> <port>", argv[0]);
		exit(EXIT_FAILURE);
	}

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	s = getaddrinfo(argv[1], argv[2], &hints, &result);
	if(s != 0)
	{
		printf("Getaddrinfo %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for(r = result; r; r = r->ai_next)
	{
		/*
	        addr_in	= (struct sockaddr_in*)r->ai_addr;
		if(inet_ntop(r->ai_family, &addr_in->sin_addr, addr, sizeof(addr)))
		{
			printf("%s\n", addr);
		}		
		*/			
		socket_fd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		if(socket_fd == -1)
			continue;

		s = connect(socket_fd, r->ai_addr, r->ai_addrlen); 
		if(s != -1)
		{
			break; // Success
		}
		
		close(socket_fd);

	}

	freeaddrinfo(result);
	
	if(r == NULL)
	{
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	s = send(socket_fd, buf, strlen(buf), 0);
	if(s == -1)
	{
		printf("%s", errno);
		exit(EXIT_FAILURE);
	} 
	
	char msgbuf[1024];
	s = recv(socket_fd, msgbuf, 1023, 0);
	if(s == -1)
		printf("%s", errno);
	
	printf("Received %zd bytes; %s\n", s, msgbuf);

}
