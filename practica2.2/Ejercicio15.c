#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc == 2){
		int fd = open(argv[1], O_TRUNC|O_WRONLY);
		if(lockf(fd, F_TEST, 0)==0){
			printf("Unlocked or locked by this process.\n");
			lockf(fd, F_LOCK, 0);
			time_t seconds;
			struct tm *timeStruct;
			seconds = time(NULL);
			timeStruct = localtime(&seconds);
			printf("Current time : %d:%d:%d\n", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
			sleep(3);
			lockf(fd, F_ULOCK, 0);
		}
	}
	return 0;
}
