#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[]){
        if(argc == 2){
                DIR *d;
		struct dirent *dir;
		d = opendir(argv[1]);
		unsigned short size = 0;
		
  		if (d) {
   			while ((dir = readdir(d)) != NULL) {
      				if(dir->d_type == DT_REG){
					if(access(dir->d_name, X_OK) != -1){
						char* name = dir->d_name;
						strcat(name, "*");
	                                        printf("%s\n", name);
                                	}
					else{
						printf("%s\n", dir->d_name);
						size+=dir->d_reclen;
					}
				}
				if(dir->d_type == DT_DIR){
					char* name = dir->d_name;
                                        strcat(name, "/");
                                        printf("%s\n", name);
				}
				if(dir->d_type == DT_LNK){
					char* name = dir->d_name;
                                        strcat(name, "->");
                                        printf("%s\n", name);
						
				}
			}
		size = size;
		printf("%u\n", size);
    		closedir(d);
		}
	}
        return 0;
}

