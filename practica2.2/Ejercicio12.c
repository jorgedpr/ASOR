#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc == 2){
		int fd = open(argv[1], O_TRUNC|O_WRONLY);
		dup2(fd, 1);
		printf("Ejercicio11.\n", fd);
	}
	return 0;
}

