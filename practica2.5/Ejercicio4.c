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
    hints.ai_socktype = SOCK_DGRAM;
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

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sfd, &readfds);
        FD_SET(0, &readfds);

        int nread;
        char buf[256];
        for (;;) {
            select(sfd+1, &readfds, NULL, NULL, NULL);

            if (FD_ISSET(sfd, &readfds)) {
                nread = recvfrom(sfd, buf, 256, 0, (struct sockaddr *) &sa, &sock);
                if (nread == 0)
                    break;
                else if (nread == -1)
                    perror("Error recvfrom()");
                else {
                    buf[nread] = '\0';
                    if (strcmp(buf, "q\n") == 0) {
                        close(sfd);
                        break;
                    }
                    else if (strcmp(buf, "t\n") == 0) {
                        time_t t = time(NULL);
                        struct tm * lt = localtime(&t);
                        char msg[80];
                        int n = strftime(msg, sizeof(msg), "%r", lt);
                        sendto(sfd, msg, n, 0, (struct sockaddr *) &sa, sock);
                    }
                    else if (strcmp(buf, "d\n") == 0) {
                        time_t t = time(NULL);
                        struct tm * lt = localtime(&t);
                        char msg[80];
                        int n = strftime(msg, sizeof(msg), "%F", lt);
                        sendto(sfd, msg, n, 0, (struct sockaddr *) &sa, sock);
                    }
                    else {
                        char msg[80];
                        int n = snprintf(msg, sizeof(msg), "Comando no existente %s", buf);
                        sendto(sfd, msg, n, 0, (struct sockaddr *) &sa, sock);
                    }
                }
                FD_SET(0, &readfds);
            }
            else if (FD_ISSET(0, &readfds)) {
                nread = read(0, buf, sizeof(buf));
                if (nread == 0)
                    break;
                else if (nread == -1)
                    perror("Error recvfrom()");
                else {
                    buf[nread] = '\0';
                    if (strcmp(buf, "q\n") == 0)
                        break;
                    else if (strcmp(buf, "t\n") == 0) {
                        time_t t = time(NULL);
                        struct tm * lt = localtime(&t);
                        char msg[80];
                        int n = strftime(msg, sizeof(msg), "%r", lt);
                        write(0, msg, strlen(msg));
                    }
                    else if (strcmp(buf, "d\n") == 0) {
                        time_t t = time(NULL);
                        struct tm * lt = localtime(&t);
                        char msg[80];
                        int n = strftime(msg, sizeof(msg), "%F", lt);
                        write(0, msg, strlen(msg));
                    }
                    else {
                        char msg[80];
                        int n = snprintf(msg, sizeof(msg), "Comando no existente %s", buf);
                        write(0, msg, strlen(msg));
                    }
                }
                FD_SET(sfd, &readfds);
            }
        }
    }
    else
        perror("Error getaddrinfo()");
}