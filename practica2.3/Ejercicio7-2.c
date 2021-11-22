#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[]) {
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
        printf("El comando termino de ejecutarse\n");
    }
}

