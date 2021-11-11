#include <fcntl.h>
#include <sys/stat.h>

int main(){
	umask(0027);
        open("fichero7", O_RDWR|O_CREAT, 0645);

        return 0;
}
