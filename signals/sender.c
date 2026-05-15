#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * int kill(pid_t pid, int sig);
 *   sends signal sig to the process with the given pid
 *   despite the name, kill() sends any signal — not just termination signals
 *   SIGUSR1 — user-defined signal 1, free to use for any purpose
 *   returns 0 on success, -1 on error
 */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: ./sender <pid>\n");
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    kill(pid, SIGUSR1);
    printf("sent SIGUSR1 to PID %d\n", pid);

    return 0;
}
