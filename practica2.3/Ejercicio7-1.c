#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
    if (argc == 2) {
        system(argv[1]);
        printf("El comando termino de ejecutarse\n");
    }
}
