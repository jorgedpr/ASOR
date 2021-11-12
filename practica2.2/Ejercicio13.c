#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc == 2){
		int fd = open(argv[1], O_TRUNC|O_WRONLY);
		dup2(fd, 1);
		dup2(fd, 2);
		int i, j;
		for(i = 0; i< 5; i++){
			printf("stdout %d...\n", i);
		}
		for(j = 0; j < 5; j++){
			fprintf(stderr, "error %d...\n", j);
		}
	}
	return 0;
}

