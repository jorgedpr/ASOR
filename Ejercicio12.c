#include <time.h>
#include <stdio.h>
#include <errno.h>

int main(){
	time_t hora;

        if(time(&hora)==-1) perror("time");
        else printf("Segundos desde el Epoch: %ld\n", hora);

        return 0;
}
