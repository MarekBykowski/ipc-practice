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
 *   initializes sa_mask to empty — the set of signals blocked during handler execution
 *   with empty mask: only the handled signal (SIGUSR1) is auto-blocked by the kernel;
 *     any other signal (e.g. SIGUSR2) can interrupt the handler mid-execution
 *   with selective mask (sigaddset): named signals are also blocked and queued
 *     until the handler returns, preventing interleaving between handlers
 *   with full mask (sigfillset): all signals blocked during handler — used rarely,
 *     only when the handler must not be interrupted under any circumstance
 *   sigemptyset is the common default — fine for short, reentrant-safe handlers
 *
 *   note on queuing: the handled signal is auto-blocked so if it arrives again
 *   while the handler runs it is queued and delivered once; a third instance is
 *   dropped — POSIX only guarantees at least one delivery, not all
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
