#include <unistd.h>
#include "pipe_hello.h"

/*
 * int pipe(int fd[2]);
 *   fd[0] - read end
 *   fd[1] - write end
 *   returns 0 on success, -1 on error
 *
 * pid_t fork(void);
 *   returns -1 on error; on success the call returns TWICE — once in each process:
 *     in the child:  returns 0
 *     in the parent: returns the child's PID, so the parent knows who its child is
 *   the parent can use that PID to wait() on the child or send it signals
 *   (the return value is ignored here, but it is available)
 */

int main(void)
{
    int fd[2];

    pipe(fd);

    if (fork() == 0)
        child(fd);
    else
        parent(fd);

    return 0;
}
