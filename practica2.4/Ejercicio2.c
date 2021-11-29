#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int p_h[2];
	int h_p[2];
	pipe(p_h);
	pipe(h_p);
	pid_t pid = fork();

	if(pid == 0){ //proceso hijo
		char buf[1] = " ";
		int i;
		for(i = 0; i < 10; i++){
			read(p_h[0], buf, 1);
			write(1, buf, 1);
			sleep(1);
			write(h_p[1], "l", 1);
		}
		write(h_p[1], "q", 1);
		close(h_p[0]);
		close(h_p[1]);
		close(p_h[0]);
		close(p_h[1]);
	}
	else{
		char buf[1] = " ";
		while(strcmp(buf, "q") != 0){
 	                read(0, buf, 1);
			write(p_h[1], buf, 1);
			read(h_p[0], buf, 1);
		}
		close(h_p[0]);
		close(h_p[1]);
        	close(p_h[0]);
        	close(p_h[1]);

	}
	return 0;
}

