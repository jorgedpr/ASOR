#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){
	if(argc == 2){
		struct stat buf;
		if(stat(argv[1], &buf) == -1) perror("stat");
		else {
			printf("Major: %d\n Minor: %d\n i-node: %ld\n Type: %d\n Last access: %s\n", major(buf.st_dev), minor(buf.st_dev), buf.st_ino, ctime(&buf.st_atime));
		}
	}

	return 0;
}
