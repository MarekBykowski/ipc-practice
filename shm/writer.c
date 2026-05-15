#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * int shm_open(const char *name, int oflag, mode_t mode);
 *   creates or opens a POSIX shared memory object by name (e.g. "/hello_shm")
 *   the name appears under /dev/shm on Linux
 *   O_CREAT | O_RDWR — create if not exists, open for reading and writing
 *   returns a file descriptor, just like open()
 *
 * int ftruncate(int fd, off_t length);
 *   sets the size of the shared memory object in bytes
 *   must be called before mmap() — object starts at size 0
 *
 * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *   maps the shared memory object into this process's address space
 *   returns a pointer you can read/write directly — no read()/write() needed
 *   NULL  — let kernel choose the address
 *   PROT_READ | PROT_WRITE — allow both reads and writes
 *   MAP_SHARED — changes are visible to other processes mapping the same object
 *
 * int munmap(void *addr, size_t length);
 *   unmaps the shared memory from this process's address space
 *
 * int shm_unlink(const char *name);
 *   removes the shared memory object from the filesystem
 *   writer is responsible for cleanup
 */

#define SHM_NAME "/hello_shm"
#define SHM_SIZE 64

int main(void)
{
    char input[8];
    int fd;
    void *ptr;

    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
    ftruncate(fd, SHM_SIZE);

    ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    const char *msg = "Hello from writer!";
    memcpy(ptr, msg, strlen(msg) + 1);
    printf("written: %s\n", msg);
    printf("run reader now, then type 'ok' to clean up: ");
    fflush(stdout);
    scanf("%7s", input);

    munmap(ptr, SHM_SIZE);
    shm_unlink(SHM_NAME);

    return 0;
}
