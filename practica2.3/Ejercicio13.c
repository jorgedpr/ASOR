#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

volatile int accion = 0;

void aux(int signal) {
    if(signal == SIGALRM) accion = 2;
    else accion = 1;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        struct sigaction sa;
        sa.sa_handler = (void *) aux;
        sigaction(SIGALRM, &sa, NULL);
        sigaction(SIGUSR1, &sa, NULL);
        alarm(atoi(argv[1]));
        while (accion == 0);
        if (accion == 2) {
            if (unlink(argv[0]) == -1)
                perror("unlink");
        }
        else if (accion == 1)
            printf("No se ha borrado\n");
    }	
    return 0;
}