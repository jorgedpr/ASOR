#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();

	if(pid == 0){ //proceso hijo
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execlp(argv[3], argv[3], argv[4], NULL);
	}
	else { //proceso padre
		close(pipefd[1]);
		dup2(pipefd[0], 1);
		close(pipefd[1]);
		execlp(argv[1], argv[1], argv[2], NULL);
	}
	return 0;
}
