#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "fifo_hello.h"

/*
 * int mkfifo(const char *path, mode_t mode);
 *   creates a named pipe (FIFO) as a file in the filesystem
 *   unlike a pipe, any two unrelated processes can open it by name
 *   mode sets permissions (subject to umask), e.g. 0644
 *   returns 0 on success, -1 on error
 *
 * mode_t umask(mode_t mask);
 *   per-process mask that subtracts permissions from the mode passed to mkfifo/open/mkdir
 *   e.g. mkfifo(path, 0666) with umask(0022) results in 0644 (0666 & ~0022)
 *   umask(0) means "give me exactly what I asked for, no subtractions"
 *   set it before mkfifo so the FIFO gets the intended permissions
 *
 * pid_t fork(void);
 *   returns -1 on error; on success the call returns TWICE — once in each process:
 *     in the child:  returns 0
 *     in the parent: returns the child's PID, so the parent knows who its child is
 *   the parent can use that PID to wait() on the child or send it signals
 *   (the return value is ignored here, but it is available)
 *
 * int unlink(const char *path);
 *   removes the FIFO file from the filesystem once we are done with it
 *   returns 0 on success, -1 on error
 */

#define FIFO_PATH "/tmp/hello_fifo"

int main(void)
{
    char input[8];
    pid_t pid;

    umask(0);
    mkfifo(FIFO_PATH, 0644);

    printf("parent PID: %d\n", getpid());

    pid = fork();

    if (pid == 0) {
        printf("child  PID: %d\n", getpid());
        fflush(stdout);
        reader(FIFO_PATH);  /* blocks at open() until writer opens — child is suspended here */
    } else {
        printf("check PIDs with ps, then type 'ok' to continue: ");
        fflush(stdout);
        scanf("%7s", input);
        writer(FIFO_PATH);
        wait(NULL);         /* wait for child to finish before cleaning up */
        unlink(FIFO_PATH);
    }

    return 0;
}
