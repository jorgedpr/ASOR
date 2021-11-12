#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc == 2){
		struct stat buf;
		if(stat(argv[1], &buf) == -1) perror("stat");
		else{
			if(S_ISREG(buf.st_mode)){
				char hard[100];
				char sym[100];
				strcpy(hard, argv[1]);
				strcat(hard, ".hard");
				strcpy(sym, argv[1]);
				strcat(sym, ".sym");
				link(argv[1], hard);
				symlink(argv[1], sym);		
			}
		}
	}

	return 0;
}
