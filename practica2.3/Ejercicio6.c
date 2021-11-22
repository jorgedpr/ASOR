#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

void main() {
    int pid = fork();
    if (pid == 0) {
        int sid = setsid();
        chdir("/tmp");
        struct rlimit rlim;
        getrlimit(RLIMIT_NOFILE, &rlim);
        char buf[100];
        getcwd(buf, 100);
        printf("pid: %d ppid: %d gid: %d sid: %d\nMax num archivos abiertos por proceso: %d Dir trabajo actual: %s\n", 
                getpid(), getppid(), getpgid(getpid()), getsid(getpid()), 
                rlim.rlim_max, buf);
    }
    sleep(3);
}
/*Si el padre termina antes que el hijo, el padre se convierte en root.
Si el padre termina después del hijo nada cambia.
 */
