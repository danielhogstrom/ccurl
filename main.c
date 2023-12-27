#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	struct  addrinfo hints, *result, *r;		
	struct sockaddr_in *addr_in;
	char addr[INET_ADDRSTRLEN];

	memset(&hints, 0, sizeof(struct addrinfo));
	memset(addr, '\0', sizeof(addr));
	
	if(argc != 2)
	{
		printf("usage %s <service>", argv[0]);
		exit(EXIT_FAILURE);
	}

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	int s = getaddrinfo(argv[1], NULL, &hints, &result);
	if(s != 0)
	{
		printf("Getaddrinfo %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for(r = result; r; r = r->ai_next)
	{
	        addr_in	= (struct sockaddr_in*)r->ai_addr;
		if(inet_ntop(r->ai_family, &addr_in->sin_addr, addr, sizeof(addr)))
		{
			printf("%s\n", addr);
		}
	}

	freeaddrinfo(result);
}
