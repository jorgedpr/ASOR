#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(){

	if(pathconf("/", _PC_LINK_MAX)==-1)perror("pathconf");
        else printf("%d\n", pathconf("/", _PC_LINK_MAX));
        if(pathconf("/", _PC_PATH_MAX)==-1)perror("pathconf");
        else printf("%d\n", pathconf("/", _PC_PATH_MAX));
        if(pathconf("/", _PC_NAME_MAX)==-1)perror("pathconf");
        else printf("%d\n", pathconf("/", _PC_NAME_MAX));

        return 1;

}

