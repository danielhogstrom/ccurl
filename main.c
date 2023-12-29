#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
<<<<<<< HEAD
=======

>>>>>>> fd55225 (connect to host and send get request)

int main(int argc, char *argv[]){
	struct  addrinfo hints, *result, *r;		
	struct sockaddr_in *addr_in;
	char addr[INET_ADDRSTRLEN];
	int socket_fd, s;
<<<<<<< HEAD
	char buf[] = "GET / HTTP/1.1\r\nHost: hemnet.se\r\n\r\n";
=======
	char *request;
	char header[100], host[100], protocol[100], url[100];
	char msgbuf[2048];
>>>>>>> fd55225 (connect to host and send get request)

	memset(&hints, 0, sizeof(struct addrinfo));
	memset(addr, '\0', sizeof(addr));
	
	if(argc != 3)
	{
		printf("usage %s <host> <port>", argv[0]);
		exit(EXIT_FAILURE);
	}

	strcpy(protocol, strtok(argv[1], "://"));
	strcpy(host, strtok(NULL, "/"));
	strcpy(url, strtok(NULL, "/"));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
<<<<<<< HEAD
	s = getaddrinfo(argv[1], argv[2], &hints, &result);
=======
	s = getaddrinfo(host, argv[2], &hints, &result);
>>>>>>> fd55225 (connect to host and send get request)
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
<<<<<<< HEAD

=======
				
		printf("connecting to %s\n", host);
>>>>>>> fd55225 (connect to host and send get request)
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

<<<<<<< HEAD
	s = send(socket_fd, buf, strlen(buf), 0);
=======
	asprintf(&request, "GET /%s HTTP/1.1\r\nHost: %s\r\nAccept: */*\r\nConnection: close\r\n\r\n", url, host);
	printf("Sending request %s", request);	

	s = send(socket_fd, request, strlen(request), 0);	
>>>>>>> fd55225 (connect to host and send get request)
	if(s == -1)
	{
		printf("%s", errno);
		exit(EXIT_FAILURE);
<<<<<<< HEAD
	} 
	
	char msgbuf[1024];
	s = recv(socket_fd, msgbuf, 1023, 0);
=======
	}

	s = recv(socket_fd, msgbuf,2047, 0);
>>>>>>> fd55225 (connect to host and send get request)
	if(s == -1)
		printf("%s", errno);
	
	printf("Received %zd bytes; %s\n", s, msgbuf);
<<<<<<< HEAD

=======
	
	close(socket_fd);
	free(request);
>>>>>>> fd55225 (connect to host and send get request)
}
