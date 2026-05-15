#include <string.h>
#include <unistd.h>
#include "pipe_hello.h"

/*
 * ssize_t write(int fd, const void *buf, size_t count);
 *   returns number of bytes written, -1 on error
 *
 * int close(int fd);
 *   always close the unused end of the pipe — the read end won't see EOF
 *   until all write ends are closed
 */

void parent(int fd[2])
{
    const char *msg = "Hello, World!";

    close(fd[0]);                        /* close unused read end */
    write(fd[1], msg, strlen(msg) + 1);  /* +1 to include '\0' */
    close(fd[1]);
}
