#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

void main(int argc, char* argv[]){
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	socklen_t peer_addr_len = sizeof(struct sockaddr_storage);

	if(argc==2){
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = 0;
		hints.ai_protocol = 0;

		int s = getaddrinfo(NULL, argv[1], &hints, &result);
		if (s==0){
			for (rp = result; rp !=NULL; rp = rp->ai_next){
				char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
				getnameinfo((struct sockaddr*) rp->ai_addr, peer_addr_len, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST);
				printf("%s %d %d\n", hbuf, rp->ai_family, rp->ai_socktype);
			}
			freeaddrinfo(result);
		}
		else perror("Error getaddrinfo()");
	}
}
