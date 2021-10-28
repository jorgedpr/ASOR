#include <time.h>
#include <stdio.h>

int main(){
	time_t tiempo=time(NULL);
        struct tm infotiempo= *localtime(&tiempo);

        printf("Anio %d\n", infotiempo.tm_year+1900);

        return 0;
}

