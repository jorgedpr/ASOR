#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
int main(){
	struct utsname unameData;

	if(uname(&unameData)<0) perror("uname");
	printf("%s\n", unameData.sysname);
	printf("%s\n", unameData.nodename);
	printf("%s\n", unameData.release);
	printf("%s\n", unameData.version);
	printf("%s\n", unameData.machine);

	#ifdef _GNU_SOURCE
		printf("%s\n", unameData.domainname);
	#endif

	return 1;
}
