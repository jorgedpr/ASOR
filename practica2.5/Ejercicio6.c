#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void main(int argc, char* argv[]) {
	struct addrinfo *result, *rp;
	struct addrinfo hints;
	struct sockaddr_storage sa;
	socklen_t sock = sizeof(struct sockaddr_storage);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	int s = getaddrinfo(argv[1], argv[2], &hints, &result);
	int sfd;
	if (s == 0) {

		for (rp = result; rp != NULL; rp = rp->ai_next) {
			sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
			if (bind(sfd, (struct sockaddr *) rp->ai_addr, rp->ai_addrlen) == 0)
				break;
			close(sfd);
		}

		freeaddrinfo(result);

		listen(sfd, 10);

		int nread;
		char buf[256];
		int afd;
		for (;;) {
			afd = accept(sfd, (struct sockaddr *) &sa, &sock);

			char host[NI_MAXHOST], service[NI_MAXSERV];
			getnameinfo((struct sockaddr *) &sa, sock, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

			printf("Conexion desde %s %s\n", host, service);

			for (;;) {
				nread = recv(afd, buf, sizeof(buf), 0);
				if (nread == 0)
					break;
				else if (nread == -1)
					perror("Error recv()");
				else
					send(afd, buf, nread, 0);
			}
		}
	}
	else
		perror("Error getaddrinfo()");

}
