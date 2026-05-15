#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
 * struct sigaction — describes how to handle a signal
 *   sa_handler — function to call when the signal arrives
 *   sa_mask    — signals to block while the handler is running
 *   sa_flags   — modifiers (0 = defaults)
 *
 * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
 *   registers the handler for signum
 *   preferred over signal() — more portable and predictable behavior
 *   oldact — previous handler is stored here if not NULL (ignored here)
 *
 * int sigemptyset(sigset_t *set);
 *   initializes the signal mask to empty — no signals blocked during handler
 *
 * int pause(void);
 *   suspends the process until any signal arrives
 *   returns after the signal handler runs
 *   used here to keep the process alive while waiting
 */

static void handler(int sig)
{
    printf("receiver: caught signal %d (SIGUSR1)\n", sig);
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);

    printf("receiver PID: %d — waiting for SIGUSR1\n", getpid());

    while (1)
        pause();

    return 0;
}
