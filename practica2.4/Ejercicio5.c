#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>

int main(int argc, char* argv[]) {
    int fd1 = open("pipe", O_RDONLY | O_NONBLOCK);
    mkfifo("pipe2", 0777);
    int fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);
    char buf[256];

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd1, &readfds); 
    FD_SET(fd2, &readfds);

    while(1) {

        select(fd2+1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(fd1, &readfds)) {
            int os = read(fd1, buf, 256);
            buf[os] = '\0';
            if (os == 0) {
                close(fd1);
                fd1 = open("pipe", O_RDONLY | O_NONBLOCK);
            }
            else printf("Datos leidos de pipe: %s", buf);
            FD_SET(fd2, &readfds);
        }
        if (FD_ISSET(fd2, &readfds)) {
            int os = read(fd2, buf, 256);
            buf[os] = '\0';
            if (os == 0) {
                close(fd2);
                fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);
            }
            else printf("Datos leidos de pipe2: %s", buf);
            FD_SET(fd1, &readfds);
        }
    }
    return 0;
}