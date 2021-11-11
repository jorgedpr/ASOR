#include <fcntl.h>

int main(){

	open("fichero", O_RDWR|O_CREAT, 0645);

        return 0;
}

