#include <signal.h>
#include <stdio.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigprocmask(SIG_SETMASK, &set, NULL);
    sleep(3);
    sigset_t pending;
    sigpending(&pending);
    if (sigismember(&pending, SIGINT))
        printf("OK SIGINT\n");
    if (sigismember(&pending, SIGTSTP))
        printf("OK SIGSTP\n");
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("Fin programa\n");
    return 0;
}
