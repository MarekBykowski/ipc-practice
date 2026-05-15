#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "fifo_hello.h"

/*
 * int open(const char *path, int flags);
 *   opens the FIFO by its filesystem name
 *   O_RDONLY — open for reading only
 *   blocks here until a writer opens the other end (kernel enforces this)
 *   returns a file descriptor on success, -1 on error
 *
 * ssize_t read(int fd, void *buf, size_t count);
 *   copies bytes from the kernel FIFO buffer into buf in your process's memory
 *   returns number of bytes read, 0 on EOF, -1 on error
 *   blocks until data is available or all write ends are closed
 *   consumed bytes are removed from the kernel buffer
 */

void reader(const char *path)
{
    char buf[64];
    int fd = open(path, O_RDONLY);

    read(fd, buf, sizeof(buf));
    printf("reader received: %s\n", buf);
    close(fd);
}
