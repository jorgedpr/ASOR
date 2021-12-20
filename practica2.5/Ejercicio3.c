#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
	struct addrinfo * result, *rp;
	struct addrinfo hints;
	struct sockaddr_storage sa;
	socklen_t sock = sizeof(sa);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;

	getaddrinfo(argv[1], argv[2], &hints, &result);

	int sfd;

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sfd);
	}

	freeaddrinfo(result);

	strcat(argv[3], "\n");
	sendto(sfd, argv[3], strlen(argv[3]), 0, NULL, sock);
	char buf[200];
	int n = recvfrom(sfd, buf, sizeof(buf), 0, NULL, &sock);
	buf[n] = '\0';
	printf("%s", buf);
}
