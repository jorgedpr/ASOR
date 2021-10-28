
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

int main(){
	struct timeval ini;
        struct timeval fin;

        if(gettimeofday(&ini, NULL)==-1) perror("gettimeofday");

        int i=0;
        while(i<1000000) i+=1;

        if(gettimeofday(&fin, NULL)==-1) perror("gettimeofday");

        printf("Tiempo: %d\n", fin.tv_usec - ini.tv_usec);

        return 0;
}
   