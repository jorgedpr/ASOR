#include <string.h>
#include <stdio.h>
int main(){
	for(int i=0;i<134;i++){
		if(printf(strerror(i))<0) perror("Error");
	}
	return 1;
}
