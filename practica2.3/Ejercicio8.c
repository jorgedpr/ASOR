#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int pid = fork();
    if (pid == 0) {
        int sid = setsid();
        chdir("/tmp");
        int fd = open("/tmp/daemon.out", O_WRONLY|O_TRUNC);
        dup2(fd, 1);
        fd = open("/tmp/daemon.err", O_WRONLY|O_TRUNC);
        dup2(fd, 2);
        fd = open("/dev/null", O_WRONLY);
        dup2(fd, 0);
        printf("Hola\n");
        if (argc >= 2) {
            char * newargv[argc - 1];
            int i;
            for (i = 0; i < argc; i++)
                newargv[i] = argv[i + 1];
            char nombre[20] = "/bin/";
            strcat(nombre, argv[1]);
            newargv[0] = nombre;
            execv(nombre, newargv);
            perror("execve");
        }
        else
            printf("Uso: ./%s <comando> [opciones]\n", argv[1]);
        }
	return 0;
}
