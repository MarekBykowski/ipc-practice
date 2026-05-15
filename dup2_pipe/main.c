#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * simulates: ls | wc -l
 *
 * int pipe(int fd[2]);
 *   creates a kernel buffer with two ends: fd[0] read, fd[1] write
 *
 * int dup2(int oldfd, int newfd);
 *   makes newfd point at the same file as oldfd
 *   if newfd is already open, it is closed first
 *   used here to redirect stdout to the pipe write end (ls side)
 *   and stdin to the pipe read end (wc side)
 *   after dup2, the program uses stdout/stdin as normal — unaware of the pipe
 *
 * int execlp(const char *file, const char *arg, ..., NULL);
 *   replaces the current process image with a new program
 *   inherits all open file descriptors (including our redirected stdin/stdout)
 *   never returns on success
 *
 * parent forks twice — one child per command — then waits for both
 * parent must close both pipe ends so wc -l sees EOF when ls finishes
 */

int main(void)
{
    int fd[2];
    pipe(fd);

    /* child 1: ls — stdout redirected to pipe write end */
    if (fork() == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", NULL);
    }

    /* child 2: wc -l — stdin redirected to pipe read end */
    if (fork() == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", "-l", NULL);
    }

    /* parent closes both ends — otherwise wc -l never sees EOF */
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
