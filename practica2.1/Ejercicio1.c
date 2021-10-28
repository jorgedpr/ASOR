#include <stdio.h>
#include <errno.h>
#include <unistd.h>
int main() {
	if(setuid(0)==-1){
		perror("Error");
	}
	return 1;
}
