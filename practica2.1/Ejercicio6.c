#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(){
	if(sysconf(_SC_ARG_MAX)==-1)perror("sysconf");
        else printf("%d\n", sysconf(_SC_ARG_MAX));
        if(sysconf(_SC_CHILD_MAX)==-1)perror("sysconf");
        else printf("%d\n", sysconf(_SC_CHILD_MAX));
        if(sysconf(_SC_OPEN_MAX)==-1)perror("sysconf");
        else printf("%d\n", sysconf(_SC_OPEN_MAX));

        return 1;
}
