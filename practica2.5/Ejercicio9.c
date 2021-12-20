#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

void sigchld_handler(int s) {
	int e = errno;

	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue;

	errno = e;
}

void main(int argc, char* argv[]) {
	struct addrinfo *res, *raux;
	struct addrinfo hints;
	struct sockaddr_storage sa;
	socklen_t sock = sizeof(struct sockaddr_storage);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	int s = getaddrinfo(argv[1], argv[2], &hints, &res);
	int sfd;
	if (s == 0) {

		for (raux = res; raux != NULL; raux = raux->ai_next) {
			sfd = socket(raux->ai_family, raux->ai_socktype,
				raux->ai_protocol);
			if (bind(sfd, (struct sockaddr *) raux->ai_addr, raux->ai_addrlen) == 0)
				break;
			close(sfd);
		}

		freeaddrinfo(res);

		listen(sfd, 10);

		struct sigaction act;
		act.sa_handler = (void *)sigchld_handler;
		sigaction(SIGCHLD, &act, NULL);

		int nread;
		char buf[256];
		int afd;
		for (;;) {
			afd = accept(sfd, (struct sockaddr *) &sa, &sock);
			if (fork() != 0) {
				close(afd);
			}
			else {
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
	}
	else
		perror("Error getaddrinfo()");

}
