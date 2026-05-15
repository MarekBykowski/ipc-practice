#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "fifo_hello.h"

/*
 * int open(const char *path, int flags);
 *   opens the FIFO by its filesystem name — this is what distinguishes a FIFO
 *   from a pipe: any process can reach it by path, not just parent/child pairs
 *   O_WRONLY — open for writing only
 *   blocks here until a reader opens the other end (kernel enforces this)
 *   returns a file descriptor on success, -1 on error
 *
 * ssize_t write(int fd, const void *buf, size_t count);
 *   copies bytes from buf in your process's memory into the kernel FIFO buffer
 *   returns number of bytes written, -1 on error
 */

void writer(const char *path)
{
    const char *msg = "Hello, World!";
    int fd = open(path, O_WRONLY);

    write(fd, msg, strlen(msg) + 1);  /* +1 to include '\0' */
    close(fd);
}
