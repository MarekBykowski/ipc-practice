#include <stdio.h>
#include <unistd.h>
#include "pipe_hello.h"

/*
 * ssize_t read(int fd, void *buf, size_t count);
 *   copies bytes from the kernel pipe buffer into buf in your process's memory
 *   returns number of bytes read, 0 on EOF, -1 on error
 *   blocks until data is available or all write ends are closed
 *   consumed bytes are removed from the kernel buffer
 */

void child(int fd[2])
{
    char buf[64];

    close(fd[1]);                      /* close unused write end */
    read(fd[0], buf, sizeof(buf));
    printf("child received: %s\n", buf);
    close(fd[0]);
}
