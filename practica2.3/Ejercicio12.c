#include <signal.h>
#include <stdio.h>

volatile int nint = 0;
volatile int ntstp = 0;

void aux(int signal) {
    signal == SIGINT ? nint++ : ntstp++;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = (void *) aux;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    while (nint+ntstp < 10);
    return 0;
}