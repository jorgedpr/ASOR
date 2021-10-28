#include <time.h>
#include <stdio.h>

int main(){
	time_t tiempo = time(NULL);
        char buffer[100];

        strftime(buffer, sizeof(buffer), "%A, %d, %B, %EY, %z", localtime(&tiempo));

        printf(buffer);

        return 0;
}


