#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * int shm_open(const char *name, int oflag, mode_t mode);
 *   opens an existing shared memory object by name
 *   O_RDONLY — open for reading only
 *
 * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *   maps the shared memory into this process's address space
 *   PROT_READ  — read only
 *   MAP_SHARED — see the same data the writer put there
 *   the pointer points directly at the shared region — no copying involved
 *   this is why shared memory is the fastest IPC: data is never copied through the kernel
 *
 * int munmap(void *addr, size_t length);
 *   unmaps the shared memory from this process's address space
 *   reader does not call shm_unlink() — that is the writer's responsibility
 */

#define SHM_NAME "/hello_shm"
#define SHM_SIZE 64

int main(void)
{
    int fd;
    void *ptr;

    fd = shm_open(SHM_NAME, O_RDONLY, 0);

    ptr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    printf("reader received: %s\n", (char *)ptr);

    munmap(ptr, SHM_SIZE);

    return 0;
}
