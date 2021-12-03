#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("pipe", O_WRONLY);
    write(fd, argv[0], strlen(argv[0]));
    write(fd, "\n", 1);
    close(fd);
    return 0;
}